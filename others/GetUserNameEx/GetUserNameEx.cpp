// GetUserNameEx.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define SECURITY_WIN32
#include <Security.h>
#pragma comment(lib, "Secur32")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szFullName[256] = {0};
	DWORD dwLen = sizeof(szFullName);
	GetUserNameEx(NameSamCompatible, szFullName, &dwLen);
	char szFullName2[256] = {0};
	DWORD dwLen2 = 256;
	WideCharToMultiByte(CP_ACP, 0, szFullName, -1, szFullName2, dwLen2, NULL, NULL);
	if(!-1)
	printf("name: %s\n", szFullName2);
	system("pause");
	return 0;
}

