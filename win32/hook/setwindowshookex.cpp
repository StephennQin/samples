// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
/*
DLL_PROCESS_ATTACH:��һ��dll�ļ���ӳ�䵽���̿ռ�ʱ��ϵͳ���ø�dll��DllMain����
DLL_PROCESS_DETACH:��DLL���ӽ��̵ĵ�ַ�ռ���ӳ��ʱ��ϵͳ����������dllmain,�������terminateprocess���򲻻ᱻ����
DLL_THREAD_ATTACH:�����̴���һ�߳�ʱ��ϵͳ�鿴��ǰӳ�䵽���̵�ַ�ռ��е�����DLL�ļ�ӳ��ÿ�δ����̶߳��ǻ���õ�
DLL_THREAD_DETACH:����̵߳�����exitthread�������̣߳��̺߳�������ʱ��ϵͳҲ���Զ�����exitthread����ϵͳ�鿴��ǰӳ�䵽���̿ռ�
�е�����DLL�ļ�ӳ�񣬵���DllMain������֪ͨ���е�DLLȥִ���̼߳����������������TerminateThread��ϵͳ�������DllMain��
*/
#include "stdafx.h"
#include <tchar.h>


HHOOK hHook = NULL;

LRESULT CALLBACK KeyboardProc(          int code,
							  WPARAM wParam,
							  LPARAM lParam
							  )
{
	MessageBox(NULL, _T("key down or key up"), NULL, MB_OK|MB_SYSTEMMODAL);
	return CallNextHookEx(hHook,code,wParam,lParam); 
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hHook =
		SetWindowsHookEx(          WH_KEYBOARD,
			KeyboardProc,
			hModule,
			0
			);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		UnhookWindowsHookEx(hHook);
		break;
	}
	return TRUE;
}

