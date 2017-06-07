#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"

void Env()
{
	char *pszEnv = (char*)GetEnvironmentStrings();
	char *pszText = pszEnv;
	while(pszText[0])
	{
		printf("%s\n",pszText);
		pszText = pszText + strlen(pszText)+1;
	}
	FreeEnvironmentStrings(pszEnv);
}
void Variable()
{
	SetEnvironmentVariable("wh","good");
	char szVar[256] = {0};
	GetEnvironmentVariable("wh",szVar,256);
	printf("%s\n",szVar);
}
void ProcInfo()
{
	DWORD nID = GetCurrentProcessId();
	//ֻ�������-1�ľ������ʹ�ã������Ķ�������
	HANDLE hProc = GetCurrentProcess();
	printf("ID=%d,hProc=%d\n",nID,hProc);
}
void Proc()
{
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};
	CreateProcess("c:/windows/system32/calc.exe","",
		NULL,NULL,FALSE,0,
		NULL,NULL,&si,&pi);
	printf("ID=%d,���=%d\n",pi.dwProcessId,
		pi.hProcess);
	WaitForSingleObject(pi.hProcess,INFINITE);
	printf("wait over!!!\n");
}
void Kill()
{
	HANDLE hProc=OpenProcess(PROCESS_ALL_ACCESS,FALSE,6756);
	TerminateProcess(hProc,123);
}
int main(int argc, char* argv[])
{
//	Env();
//	Variable();
//	ProcInfo();
//	Proc(); //�൱��vfork+exec()ϵ�к���
//	Kill();
	system("pause");
	return 0;
}
