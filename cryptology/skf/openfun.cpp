#include "stdafx.h"
#include "OpenFun.h"
#include "SKFFun.h"

//SKF To OpenSSL
EVP_PKEY *SKFToOpenSSL(PRSAPUBLICKEYBLOB pSKFKey)
{
	RSA *rsa = RSA_new();
	rsa->n=BN_bin2bn(pSKFKey->Modulus, sizeof(pSKFKey->Modulus), rsa->n);
	rsa->e=BN_bin2bn(pSKFKey->PublicExponent, sizeof(pSKFKey->PublicExponent), rsa->e);
	EVP_PKEY *pubkey = EVP_PKEY_new();

	EVP_PKEY_assign_RSA(pubkey, rsa);
	int len;
	unsigned char *p = NULL;
	//i2d_RSAPublicKey(const RSA *a, unsigned char **out);
	len = i2d_PublicKey(pubkey, &p);
	WriteToLog("e:\\log\\logout\\pubkey.log", p, len);
	printf("writlen = %d\n", len);
	//���ǧ�����ͷţ�Ҫ���ᱨ��ȡλ���쳣��
	//��ȡλ���쳣һ���ԭ������Խ�硢2�������ָ�뱻��ǰ�ͷ�
//	RSA_free(rsa);
	OPENSSL_free(p);

	return pubkey;
}
//OpenSSL To SKF
PRSAPUBLICKEYBLOB OpenSSLToSKF()
{
	EVP_PKEY *pubkey = new EVP_PKEY();
	BYTE *pk = new BYTE[149];
	ReadInLog("../CSP_sign_verify/log/publickey.log", pk , 140);
	d2i_PublicKey(EVP_PKEY_RSA, &pubkey, (const unsigned char **)&pk, 140); 
//////////////////////////////////////////////////////
	RSA *rsa = EVP_PKEY_get1_RSA(pubkey);
	RSAPUBLICKEYBLOB *pSKFKey = new RSAPUBLICKEYBLOB();
	memset(pSKFKey, 0, sizeof(RSAPUBLICKEYBLOB));
	//����1024λ��֤�飬RSA_size(rsa)��ֵΪ128��pSKFKey->BitLenΪ1024
	pSKFKey->BitLen = RSA_size(rsa) * 8;
	unsigned char *buf = new BYTE[RSA_size(rsa)];
	//��OpenSSL�Ĺ�Կ�ṹ��BIGNUM��תΪ�ֽ����飬
	//ע��RSArefPublicKey.Modulus��������ǹ̶����ȵģ����ܻᳬ��RSA_size�����Ҫ����������ಹ0������Ҫͨ��һ��buf����תһ��
	memset(buf, 0, RSA_size(rsa));
	int len = BN_bn2bin(rsa->n, buf);
	memcpy(pSKFKey->Modulus + MAX_RSA_MODULUS_LEN - len, buf, len);
	memset(buf, 0, RSA_size(rsa));
	len = BN_bn2bin(rsa->e, buf);
	memcpy(pSKFKey->PublicExponent + MAX_RSA_EXPONENT_LEN - len, buf, len);

	return pSKFKey;
}

//OpenSSL Verify
int OpenSSL_Verify(EVP_PKEY *pPubKey, 
				   unsigned char *data, int data_cb, 
				   unsigned char* sign, unsigned int sign_cb)
{
	OpenSSL_add_all_algorithms();

	const EVP_MD *md = NULL;
	EVP_MD_CTX md_sign_ctx, md_verify_ctx;
	int nRet = 0, n = 0;
	char szErr[1024];

	//������Կ����ѡ��ժҪ�㷨
	switch (pPubKey->type) {
	case EVP_PKEY_EC:
		md = EVP_ecdsa();
		break;
	default:
		md = EVP_sha1();
		break;
	}

	//ժҪ�����ĳ�ʼ��
	if( !EVP_VerifyInit( &md_verify_ctx, md ) ) {
		n  = ERR_get_error();
		ERR_error_string( n, szErr );

		fprintf( stderr, "OpenSSL_Verify: EVP_VerifyInit failed: \nopenssl return %d, %s\n", n, szErr );

		nRet = -4;
		goto verify_ret;
	}

	//��ǩ�����ժҪ���㣬����ж�����ݣ����Զ�ε���EVP_VerifyUpdate
	if( !EVP_VerifyUpdate(&md_verify_ctx, data, data_cb) ) {
		n  = ERR_get_error();
		ERR_error_string( n, szErr );

		fprintf( stderr, "OpenSSL_Verify: EVP_VerifyUpdate failed: \nopenssl return %d, %s\n", n, szErr );

		nRet = -5;
		goto verify_ret;
	}

	//��֤ǩ��
	int nn = EVP_VerifyFinal(&md_verify_ctx, sign, sign_cb, pPubKey);
	if( 0>= nn) {
		n  = ERR_get_error();
		ERR_error_string( n, szErr );
		fprintf( stderr, "OpenSSL_Verify: EVP_VerifyUpdate failed: \nopenssl return %d, %s\n", n, szErr );
		
		ERR_load_crypto_strings();
		const char *szerr= ERR_func_error_string(n);
		const char **ff = NULL;
		ERR_get_error_line(ff, &n);
		

		fprintf( stderr, "OpenSSL_Verify: EVP_VerifyFinal failed: \nopenssl return %d, %s\n", n, szerr );

		nRet = -6;
		goto verify_ret;
	}

verify_ret:
	if( !EVP_MD_CTX_cleanup(&md_verify_ctx) ) {
		n  = ERR_get_error();
		ERR_error_string( n, szErr );
		fprintf( stderr, "OpenSSL_Verify: EVP_ctx_cleanup failed: \nopenssl return %d, %s\n", n, szErr );
	}

	return nRet;
}