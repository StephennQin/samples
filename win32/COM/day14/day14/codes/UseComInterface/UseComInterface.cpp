// UseComInterface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../COMInterface/math.h"
typedef IMath*(*INSTANCE)();
IMath* GetMath()
{
	//����dll
	HMODULE hDll=LoadLibrary("ComInterface.dll");
	//��ȡ���������ĺ�����ַ
	INSTANCE Instance=(INSTANCE)
		GetProcAddress(hDll,"CreateInstance");
	//���øú���
	IMath *piMath=Instance();
	return piMath;
}
int main(int argc, char* argv[])
{
	IMath *piMath=GetMath();
	int nAdd=0;//���������
	piMath->Add(100,100,&nAdd);
	//�ӿ�ʹ�ú�
	piMath->Release();
	printf("nAdd=%d\n",nAdd);
	getchar();
	return 0;
}

