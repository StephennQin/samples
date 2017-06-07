// CSP_sign_verify.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "fun.h"


BYTE *pbKeyBlob;    //������Կblob������ָ��

bool CSP_sign(BYTE *pbSignature, DWORD *pdwSigLen)
{
	//����hProv
	HCRYPTPROV hProv = NULL;
	DWORD dwErr = 0;
	
	if (!CryptAcquireContext(
		&hProv, 
		_T("3fa0f121-8140-4782-b5b4-6d19d4b353e3"),
		_T("FEITIAN ePassNG RSA Cryptographic Service Provider"),
		PROV_RSA_FULL,
		0))
	{
		printf("CryptAcquireContext failed:%X\n", GetLastError());
		return false;
	}
	BYTE  pbCertContainerName[10][40] = {0};  //��������
	DWORD  dwCertContainerNameLen = 40;     //�������Ƴ���
	DWORD  dwCertNumber = 0;  //������Ŀ
#if 0
	if(CryptGetProvParam(
		hProv, PP_ENUMCONTAINERS,
		pbCertContainerName[dwCertNumber],
		&dwCertContainerNameLen,
		CRYPT_FIRST))
	{
		if (dwCertContainerNameLen != 0)
			dwCertNumber ++;
		//ö���������������һ������Ϊ0
		//"3fa0f121-8140-4782-b5b4-6d19d4b353e3"
		//"698D363C-1FF8-4AAE-872B-D7C428777B07"
		while(CryptGetProvParam(
			hProv, PP_ENUMCONTAINERS,
			pbCertContainerName[dwCertNumber],
			&dwCertContainerNameLen, 0))
		{
			if(dwCertContainerNameLen != 0)
				dwCertNumber++;
		}
	}
#endif 
	//����pin CryptSetProvParam����ʲô����¶��᷵��FALSE?(ֻ����getlasterrorΪ0���ˣ�
#if 1
	BYTE *pbData = (BYTE*)"123456";
	CryptSetProvParam(
		hProv, PP_SIGNATURE_PIN, (BYTE*)pbData, 0);
	if(GetLastError() == 0)
		puts("��֤Pin��ɹ�");
	else
	{
		puts("��֤Pin��ʧ��");
		return false;
	}
#endif
	//��ô���pin�뻺�棬��ÿ�ζ�Ҫ����pin
	//698D363C-1FF8-4AAE-872B-D7C428777B07
	//3fa0f121-8140-4782-b5b4-6d19d4b353e3
	//������ɢ����
	HCRYPTHASH hHash = NULL;
	if (!CryptCreateHash(
		hProv, 
		CALG_SHA1,
		NULL,
		0,
		&hHash))
	{
		puts("CryptCreateHash error");
		return false;
	}
	//��������ժҪ
	char text[256] = {0};
	puts("input data:");
	scanf("%s", text);
	DWORD len = strlen(text);
	if (!CryptHashData(
		hHash,
		(const BYTE*)text,
		len, 0))
	{
		puts("CryptHashData error");
		CryptDestroyHash(hHash);
		return false;
	}

	printByte((BYTE*)text, len);
	//����ǩ��
	
	if(!CryptSignHash( 
		hHash, 
		AT_SIGNATURE,
		NULL,
		0,
		pbSignature, 
		pdwSigLen
		))
	{
		//NTE_NO_KEY
		printf("CryptSignHash failed:%x\n",GetLastError());
		return false;
	}
	//print signature data
	printByte(pbSignature, *pdwSigLen);

	if(hHash)
		CryptDestroyHash(hHash);
	return true;
}

bool 
CSP_verify(BYTE *pbSignature, DWORD *pdwSigLen)
{
	//�ȵ���֤��
 	PCCERT_CONTEXT pCert = NULL;
#if 1
	if(!(pCert = ImportCert(L"FEITIAN ePassNG RSA Cryptographic Service Provider", _T("ǩ��"))))
	{
		puts("importCert failed");
		return false;
	}
#endif
#if 0
	//��֤�鵼����
	FILE *fp = NULL;
	fp = fopen("cert.cer", "wb");
	int num = fwrite(pCert->pbCertEncoded, 1, pCert->cbCertEncoded, fp);
	printf("%d\n", num);
	fclose(fp);
#endif
#if 0
	BYTE bBuf[2048] = {0};
	FILE *fp2 = NULL;
	fp2 = fopen("cert.cer", "rb");
	int num2 =fread(bBuf, 1, 2048, fp2);
	printf("%d\n", num2);
	fclose(fp2);
	pCert =
	CertCreateCertificateContext(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING, bBuf, num2); 

	union
	{
		BYTE byteBuf[1024];
		CRYPT_KEY_PROV_INFO kpi;
	};
	memset(byteBuf, 0, 1024);
	DWORD dwLen = 1024;
	//����֤��Ӧ��û�����⡣���ǲ���ʹ�����µĺ�����
	if(!CertGetCertificateContextProperty(pCert, CERT_KEY_PROV_INFO_PROP_ID, byteBuf, &dwLen))
	{
		puts("can't Get CertificateContext Property");
		return false;
	}
	if(wcscmp(kpi.pwszProvName, L"FEITIAN ePassNG RSA Cryptographic Service Provider") != 0)
		;
#endif


	//������ʱ��һ��CSP
	HCRYPTPROV hProv = NULL;
	if (!CryptAcquireContext(
		&hProv, 
		_T("CSP_sing_verify"),
		NULL,
		PROV_RSA_FULL,
		0))
	{
		if(CryptAcquireContext(
			&hProv, 
			_T("CSP_sing_verify"),
			NULL, 
			PROV_RSA_FULL, 
			CRYPT_NEWKEYSET)) 
		{
			printf("A new key container has been created.\n");
		}
		else
		{
			printf("Could not create a new key container.\n");
			return false;
		}

	}

	HCRYPTHASH hHash = NULL;
	if (!CryptCreateHash(
		hProv, 
		CALG_SHA1,
		NULL,
		0,
		&hHash))
	{
		puts("CryptCreateHash error");
		return false;
	}
	//��������ժҪ
	char text[256] = {0};
	puts("input data:");
	scanf("%s", text);
	DWORD len = strlen(text);
	if (!CryptHashData(
		hHash,
		(const BYTE*)text,
		len, 0))
	{
		puts("CryptHashData error");
		CryptDestroyHash(hHash);
		return false;
	}
	
	HCRYPTKEY hPubKey = NULL;

	if(!CryptImportPublicKeyInfo(hProv, pCert->dwCertEncodingType, &pCert->pCertInfo->SubjectPublicKeyInfo, &hPubKey))      
	{      
		printf("CryptImportPublicKeyInfo error:%x.\n",GetLastError());  
		return false;  
	}  
		
	if(!CryptVerifySignature(hHash, pbSignature, *pdwSigLen, 
		hPubKey, NULL, 0))
	{
		//NTE_BAD_SIGNATURE
		printf("CryptVerifySignature failed.%x\n",GetLastError());
		return false;
	}
	
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BYTE pbSignature[1024] = {0};
	DWORD dwSigLen = 1024;

#if 0
	if(!CSP_sign(pbSignature, &dwSigLen))
	{
		puts("CSP_sign failed");
		return -1;
	}else
	{
		//CSP�Ƚ����⣬ǩ���������ֽ���ͬ��Ҫ������
		BYTE bTemp = 0;
		for (int i =0; i <dwSigLen/2; i++)
		{
			bTemp = pbSignature[i];
			pbSignature[i] = pbSignature[dwSigLen-1-i];
			pbSignature[dwSigLen-1-i] = bTemp;
		}
		//��ǩ������д�뱾���ļ��У������ļ�/log/signature.log��

		FILE *fp = NULL;
		fp = fopen("./log/signature.log", "w");
		int numwritten = fwrite(pbSignature, sizeof(BYTE), dwSigLen, fp);
		printf("written %d bytes\n", numwritten);

		//����Կд�������ļ���
 		PCCERT_CONTEXT pCert = NULL;
 		pCert = ImportCert("test20151202003", _T("ǩ��"));

		CERT_PUBLIC_KEY_INFO PubKey = pCert->pCertInfo->SubjectPublicKeyInfo;
		CRYPT_BIT_BLOB PublicKey = PubKey.PublicKey;
		BYTE* pbData = PublicKey.pbData;
		DWORD cbData = PublicKey.cbData;
		DWORD cUnuseBits = PublicKey.cUnusedBits;

		fp = NULL;
		fp = fopen("./log/publickey.log", "w");
		numwritten = fwrite(pbData, sizeof(BYTE), cbData - cUnuseBits, fp);
		printf("written %d bytes\n", numwritten);
		fclose(fp);
	}
#elif 1
	if(!CSP_sign(pbSignature, &dwSigLen))
	{
		puts("CSP_sin failed");
		return -1;
	}else
	{
		puts("CSP_sin success");
		if (!CSP_verify(pbSignature, &dwSigLen))
		{
			puts("CSP_verify failed");
		}
		else
			puts("CSP_verify success");
			
	}
#endif
	/////////////////////////////////////
	system("pause");
	return 0;
}