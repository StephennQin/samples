// COMObject.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ImpMath.h"
#include "math_i.c"
//ATL����Ҫ��ȫ�ֱ�����������ATL�����Ϣ
CComModule _Module;
//���ID�����ʵ�����ӳ���ϵ
BEGIN_OBJECT_MAP(objectMap)
  OBJECT_ENTRY(CLSID_Math,CImpMath)
END_OBJECT_MAP()

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    //��dll��һ�������ص�Ӧ�ó���Ľ��̿ռ�ʱ
	if (ul_reason_for_call==DLL_PROCESS_ATTACH)
	{
		//�����ID��������ӳ���ϵ���浽_Module��
		_Module.Init(objectMap,(HINSTANCE)hModule);
	}
	return TRUE;
}
/*
//�������󣬷��ؽӿڵĺ���
IMath* CreateInstance()
{
	//CImpMath��һ�������࣬���ܴ�������
	  IMath *piMath=new CImpMath;
	piMath->AddRef();
	return piMath;
}
*/
//����������ATL���ṩ��CComObject��
IMath* MyCreateInstance()
{
	CComObject<CImpMath> *pObject;
	//�������󣬶���ĵ�ַ����pObjectָ�������
	CComObject<CImpMath>::CreateInstance(&pObject);
	pObject->AddRef();
	return pObject;
}
//ͨ�õĴ��룬�κ�����Ĵ���������ʹ�ø÷�ʽ����
IUnknown* MyCreateInstanceEx(CLSID clsid)
{
   //1 ����ָ��������೧���󣬲����ظ��೧�Ľӿ�
	IClassFactory *pFactory;
    _Module.GetClassObject(clsid,IID_IClassFactory,
		(LPVOID*)&pFactory);
	//2 ʹ���೧����������󣬷���IUnknown�ӿ�
	IUnknown *piUnknown;
    pFactory->CreateInstance(NULL,IID_IUnknown,
		(LPVOID*)&piUnknown);
	return piUnknown;

} 
