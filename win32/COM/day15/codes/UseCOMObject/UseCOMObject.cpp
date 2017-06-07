// UseCOMObject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../COMObject/math.h"
#include "../COMObject/math_i.c"

typedef IMath*(*INSTANCE)();
typedef IUnknown*(*INSTANCEEX)(CLSID);
IMath *GetMath()
{
   HMODULE hDll=LoadLibrary("COMObject.dll");
   INSTANCE Instance=(INSTANCE)
	   GetProcAddress(hDll,"MyCreateInstance");
   IMath *pMath=Instance();
   return pMath;

}
IUnknown * GetInterface()
{
  HMODULE hDll=LoadLibrary("COMObject.dll");
  INSTANCEEX Instance=(INSTANCEEX)
	  GetProcAddress(hDll,"MyCreateInstanceEx");
  IUnknown *piUnknown=Instance(CLSID_Math);
  return piUnknown;
}
int main(int argc, char* argv[])
{
	//IMath *piMath=GetMath();
    IUnknown *piUnknown=GetInterface();
    IMath *piMath=NULL;
    piUnknown->QueryInterface(IID_IMath,(LPVOID*)&piMath); 
	//�ͷ�IUnknown�ӿ�
	piUnknown->Release();
	//ʹ��IMath �ӿ�
	int nAdd=0;//���������
	piMath->Add(100,100,&nAdd);
	//�ͷ�IMath�ӿ�
	piMath->Release();
	//������
	printf("nAdd=%d\n",nAdd);
	getchar();
	return 0;
}

