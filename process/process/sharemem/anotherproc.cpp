// AnotherProc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ShellExecute(NULL, _T("open"), _T("MemMapFile.exe"), 0, _T("F:\\test_free\\MemMapFile\\Debug"), SW_SHOW);

	DWORD nRet = 0;
	HANDLE handleFile;
	char *pStr = NULL;
	//�򿪹����ļ�
	handleFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, 
		false, _T("wanghao"));
	if(handleFile == NULL)
	{
		puts("OpenFileMapping failed");
		nRet = -1;
		goto EXIT_POINT;
	}
	//��ȡ�����ļ���ַ������ȡ����
	pStr = (char *)MapViewOfFile(handleFile,
		FILE_MAP_ALL_ACCESS, 0, 0, 1024);
	puts(pStr);
	//////////////////////////////////////////////////////////////////////////
EXIT_POINT:
	if (pStr)
		UnmapViewOfFile(pStr);
	if (handleFile)
		CloseHandle(handleFile);
	getchar();
	return nRet;
}

