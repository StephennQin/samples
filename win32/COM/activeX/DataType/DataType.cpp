// DataType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlbase.h>
#include <comdef.h>
//COM���ַ�������
void TestBSTR()
{
	//�����ַ���
	BSTR bstrText=SysAllocString(L"hello");
	//ʹ��...
	
	//�ͷ��ַ���
	SysFreeString(bstrText);
	//��װ���ʹ��
	CComBSTR bstrText2("hello");
	printf("�ַ�������:%d\n",bstrText2.Length());
	_bstr_t bstrText3("hello");
	printf("�ַ�������:%d\n",bstrText3.length());
}
//�ɱ�����
void VariantTest()
{
	//ʹ�ÿɱ����ͱ�ʾ����100
	VARIANT varInt;
	varInt.vt=VT_I4;
	varInt.lVal=100;
	//ʹ�ÿɱ����ͱ�ʾָ��һ������ֵ��ָ��
	long nValue=125;
	VARIANT varIntPtr;
	varIntPtr.vt=VT_BYREF|VT_I4;
	varIntPtr.plVal=&nValue;
	//��װ���ʹ��
	CComVariant varInt2(100);
	_variant_t varInt3((long)100);
}
int main(int argc, char* argv[])
{
//	printf("Hello World!\n");
	TestBSTR();
	return 0;
}

