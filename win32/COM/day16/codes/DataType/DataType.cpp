// DataType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>//Win32ƽ̨
#include <atlbase.h>//ATL��
#include <comdef.h>//C++��
void TestBSTR()
{
    // 1 �����ַ���
	BSTR bstr=SysAllocString(L"Hello");
	// 2 ���ýӿں���...��ʹ���ַ���

	// 3 ʹ����ɺ��ͷ�
	SysFreeString(bstr);
	CComBSTR bstr2("Hello");
	bstr2.Length();
	_bstr_t bstr3("Hello");
	bstr3.length();

}
void TestVariant()
{
    //ʹ��VARIANT��ʾ����(long)100
	VARIANT varInt={0};
	varInt.lVal=100;
	varInt.vt=VT_I4;
    //ʹ��VARIANT��ʾָ��һ��long�͵�ָ��
	VARIANT varIntPtr={0};
	long nValue=0;
	varIntPtr.plVal=&nValue;
	varIntPtr.vt=VT_BYREF|VT_I4;
	//ʹ�ö�Ӧ�ķ�װ��
	CComVariant varInt2(100);
	_variant_t varInt3((long)100);


}
void TestSafeArray()
{
	//1 ���������ά��Ϣ
	SAFEARRAYBOUND bound[2];
	bound[0].cElements=10;
	bound[0].lLbound=0;
	bound[1].cElements=10;
	bound[1].lLbound=0;
	//2 ������ȫ����
	SAFEARRAY *pArray=SafeArrayCreate(VT_I4,2,bound);
	//3 ��ֵ
	for (long i=0;i<10;i++)
	{
		for (long j=0;j<10;j++)
		{
			long nValue=i*10+j;
			long nIndices[2]={i,j};//Ԫ�ص�λ��
			SafeArrayPutElement(pArray,nIndices,&nValue);
		}
	}
	//4 ȡֵ
	for (i=0;i<10;i++)
	{
		for (long j=0;j<10;j++)
		{
			long nValue=0;//ʹ�øñ��������������ȡ����ֵ
            long nIndices[2]={i,j};
			SafeArrayGetElement(pArray,nIndices,&nValue);
			printf("%02d  ",nValue);
		}
		printf("\n");
	}
	//5 �ͷ�
	SafeArrayDestroy(pArray);


}
int main(int argc, char* argv[])
{
	TestBSTR();
	TestSafeArray();
	printf("Hello World!\n");
	return 0;
}

