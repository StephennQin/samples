// COMInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ImpMath.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
//��������ĺ���
IMath *CreateInstance()
{
	IMath* piMath=new CImpMath;
    piMath->AddRef();
	return piMath;
} 

