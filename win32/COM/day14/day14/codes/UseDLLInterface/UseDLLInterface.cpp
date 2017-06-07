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
    
	//ʹ��IMath�ӿڲ�ѯ�õ�IMath2
	IMath2 *pMath2=NULL;
	HRESULT nRet=
     pMath->QueryInterface(IID_IMath2,(LPVOID*)&pMath2);
	if(FAILED(nRet))return -1;
	//ʹ��IMath2�ӿ�ǰ
    pMath2->AddRef();
	int nMul=pMath2->Mul(100,100);
	//ʹ��IMath2�ӿں�
	pMath2->Release();
	//ʹ�ýӿں�
	pMath->Release();
	printf("nAdd=%d\n",nAdd);
	printf("nMul=%d\n",nMul);
    //ɾ������
	//delete pMath;
	getchar();
	return 0;
}

