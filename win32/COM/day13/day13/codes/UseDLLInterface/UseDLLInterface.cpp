// UseDLLInterface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../DLLInterface/math.h"
//���庯��ָ������
typedef IMath*(*INSTANCE)();
IMath* GetMath()
{
	//1 ����dll
	HMODULE hDll=LoadLibrary("DLLInterface.dll");
	//2 ��ȡ���������ĺ�����ַ
	INSTANCE Instance=(INSTANCE)
		GetProcAddress(hDll,"CreateInstance");
	//3 ���õ�������
	IMath *pMath=Instance();
	return pMath;
} 
int main(int argc, char* argv[])
{
	IMath *pMath=GetMath();
    //ʹ�ýӿ�ǰ
	pMath->AddRef();
	int nAdd=pMath->Add(100,100);
	//���ʹ�øýӿ�...

	//ʹ�ýӿں�
	pMath->Release();
	printf("nAdd=%d\n",nAdd);
    //ɾ������
	//delete pMath;
	getchar();
	return 0;
}

