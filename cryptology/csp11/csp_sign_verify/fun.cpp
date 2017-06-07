#include "stdafx.h"
#include "fun.h"
#include <string>
using namespace std;


PCCERT_CONTEXT
ImportCert(wchar_t *name, TCHAR *use)
{
	PCCERT_CONTEXT pCert =NULL;

	do 
	{
		HCERTSTORE hSysStore = NULL;
		if (!(hSysStore = CertOpenSystemStore(NULL, _T("MY"))))
		{
			puts("cert open error");
			break;
		}

		//�ҵ����ʵ�֤�������
		do 
		{
			pCert = CertEnumCertificatesInStore(hSysStore, pCert);
			if (pCert)
			{
 				union
 				{
 					BYTE byteBuf[1024];
 					CRYPT_KEY_PROV_INFO kpi;
 				};
 				memset(byteBuf, 0, 1024);
 				DWORD dwLen = 1024;
 				if(!CertGetCertificateContextProperty(pCert, CERT_KEY_PROV_INFO_PROP_ID, byteBuf, &dwLen))
 					continue;
 				if(wcscmp(kpi.pwszProvName, name) != 0)
 					continue;
				//puts("find a certificate");
				////ѡ����ʵ�֤��
				//TCHAR szNameString[1024] = {0};
				//if(CertGetNameString(pCert, CERT_NAME_ATTR_TYPE, 0, NULL, (LPWSTR)&szNameString, 1024))//������ȥ���Զ��Լ�������
				//{
				//	char buff[128] = {0};
				//	WideCharToMultiByte(CP_ACP, 0, szNameString, -1, buff, 128, 0, 0);
				//	//printf("%s\n", buff);
				//	if (strcmp(buff, name) != 0)
				//	{
				//		continue;
				//	}
				//}
				//ѡ���ʺϵ�֤�����ͣ�����ʹ�õ�Ӧ����ǩ��֤��
				wstring strUsage;
				DWORD dwKeyUsage = 0;
				if (CertGetIntendedKeyUsage(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING, 
					pCert->pCertInfo,
					(BYTE*)&dwKeyUsage,
					sizeof(dwKeyUsage)))
				{
					BOOL bSig = CERT_DIGITAL_SIGNATURE_KEY_USAGE & dwKeyUsage;
					BOOL bEnc = CERT_DATA_ENCIPHERMENT_KEY_USAGE & dwKeyUsage;
					if (bSig)
						strUsage = _T("ǩ��");
					if (bEnc)
						strUsage += _T("����");
				}
				if (strUsage == use)
				{
					if (strUsage == _T("����"))
						puts("this is a encrypt certificate");
					if (strUsage == _T("ǩ��"))
						puts("this is a sign certificate");
					break;
				}
			}
		} while (pCert);
		if (hSysStore)
			CertCloseStore(hSysStore, 0);
		break;
	} while (true);

//�ƺ���
	return pCert;
}

void
printByte(BYTE *pbData, DWORD dwLen)
{
	printf("total:%d bytes\n", dwLen);
	for (int i = 0; i<dwLen; i++)
	{
		printf("%02X ", pbData[i]);
		if ((i+1)%10 == 0)
			putchar('\n');
	}
	putchar('\n');
}