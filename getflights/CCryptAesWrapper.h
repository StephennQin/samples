

#pragma once

#include <string>  
using namespace std;

#include "ByteBuf.h"

class CCryptAesWrapper
{
public:
	CCryptAesWrapper(void){};
	~CCryptAesWrapper(void){};

public:
	static std::string ECB_AESEncryptStr(const std::string & sKey, const char *plainText);  
	static std::string ECB_AESDecryptStr(const std::string & sKey, const char *cipherText);    

	static void CBC_AESEncryptStr(const std::string & sKey, const std::string & sIV, const std::string & strTxt, std::string & strDstCipherTxt);    
	static std::string CBC_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText, bool bHexStr=true); 
	static void CBC_AESDecryptStr2(const std::string & sKey, const std::string & sIV, const std::string & cipherText, std::string & strOut, bool bInputHexStr=true);
	static bool CBC_AESDecryptBufToBuf(const std::string & sKey, const std::string & sIV, const BYTE* pBuf, size_t iBufBytesLen, CByteBuf * pBytebuf);

	static std::string CBC_CTS_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText);     
	static std::string CBC_CTS_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);    

	static std::string CFB_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText);     
	static std::string CFB_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);

	static std::string OFB_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText); 
	static std::string OFB_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);     

	static std::string CTR_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText);
	static std::string CTR_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);   

	static BOOL gzip_decompress (const void* pInDate, size_t nSize, std::string& raw_data);

	//inָ����ַ���Ҫ��\0��β
	static void Base64Encode(const char *in, bool bHexStr, std::string & strResult);
	static void Base64Encode(const BYTE *pBuf, int iElementNum, bool bHexStr, bool bInsertLineBreaks, std::string & strResult);
	static void Base64Encode(const std::string & strSrc, bool bHexStr, bool bInsertLineBreaks, std::string & strResult);
	//inָ����ַ���Ҫ��\0��β
	static void Base64Decode(const char *in,  std::string & strResult);
	static void Base64Decode(const std::string & strSrc,  std::string & strResult);
	//base64����һ��buf��buf������iBufBytesLenָ��,
	static bool Base64DecodeBufToBuf(const BYTE *in,  size_t iBufBytesLen, CByteBuf * pBytebuf);
	//inָ����ַ���Ҫ��\0��β
	static void DecodeHexString(const char *in, std::string & strResult);
	//DecodeHexStrToBinBuf���ܣ�
	//��16���Ƶ��ַ���ת�ɶ����ƴ�
	//��16���ƴ��е�ÿ�����ַ�ת��һ���ֽڣ��ֱ�ռ�����ֽڵĸߵ�4λ.���16�����ִ����Ȳ���2�ı���������ַ��ᱻ������
	//���16���ƴ��ĳ��ȣ�����\0����2�ı�������ת����Ķ����ƴ�������ת��ǰ��һ�룬
	//���16���ƴ��ĳ��ȣ�����\0������2�ı�������ת����Ķ����ƴ�������ת��ǰ��һ�룬16���ƴ����һ���ַ���������ת��
	static void DecodeHexStrToBinBuf(const std::string & strHexSrc, std::string & strBinDst);
	static void DecodeHexStrToBinBuf(const BYTE* pHexBuf, int iElmentNum, std::string & strBinDst);
	//EncodeBinBufToHexStr���ܣ�
	//���ֽ�buf�е���ֵת����16�����ַ��͵�buf��ÿ���ֽڵĸߵ�4λ�ֱ�ת��һ��16�����ַ��������һ���ֽ���
	//ʮ���Ƶ�0��9ת��16���Ƶ�0X30~0X39,ʮ���Ƶ�10��15ת��16���Ƶ�0X41��0X46
	//ת������ִ����������ֽ����鳤�ȵ�2��
	static void EncodeBinBufToHexStr(const BYTE* pBuf, int iElementNum, std::string & strHex);
	static void EncodeBinBufToHexStr(const std::string & strBinBuf, std::string & strHex);

	//��ѹ\0��β���ַ���
	static void GunzipString(std::string & strComproessed, std::string & strOut);
	//��ѹһ��buf��buf������iBufBytesLenָ��
	static bool GunzipBuf(const BYTE* pBuf, int iBufBytesLen, std::string & strOut);
	//��ѹһ��buf��buf������iBufBytesLenָ��,
	static bool GunzipBufToBuf(const BYTE* pBuf, size_t iBufBytesLen, CByteBuf * pBytebuf);
};

