#include "stdafx.h"
#include <stdio.h>
#define UNICODE
#include <windows.h>
void T_char()
{
	TCHAR *pszText = __TEXT("hello");
#ifdef UNICODE
	wprintf(L"%s\n",pszText);
#else
	printf("����%s\n",pszText);
#endif
}/*
//��׼��������롢����������������������ڴ��
//��׼�������׼��������𣺱�׼����û�л�����
BOOL WriteConsole(//�˺�����wprintf֧�ֵĺã���ô�����UNICODE
  HANDLE hConsoleOutput,           // handle to screen buffer
  CONST VOID *lpBuffer,            // write buffer
  DWORD nNumberOfCharsToWrite,     // number of characters to write
  LPDWORD lpNumberOfCharsWritten,  // number of characters written
  LPVOID lpReserved                // reserved����
);
HANDLE GetStdHandle(
  DWORD nStdHandle   // input, output, or error device
  //STD_INPUT_HANDLE STD_OUTPUT_HANDLE STD_ERROR_HANDLE
);
*/

/*
void T_char()
{
#ifdef WIDECHAR //���ļ��ھ���������Դ�ԣ�������������Դ��
	wchar_t *pszText=L"hello";
	wprintf(L"%s\n",pszText);
#else
	char* pszText = "hello";
	printf("��:%s\n",pszText);
#endif
}*/
void C_char()
{
	char* pszText="hello char";
	printf("%s\n",pszText);
}
void W_char()
{
	wchar_t* pwszText=L"hello wchar";
	int nlen = wcslen(pwszText);
	wprintf(L"%s %d\n",pwszText,nlen);//11 len��Ķ����ַ��ĸ���
}
void PrintfUnicode()
{
	HANDLE hStd=GetStdHandle(STD_OUTPUT_HANDLE);
	for(WORD nHigh=100;nHigh<200;nHigh++)
	{
		for(WORD nLow=100;nLow<200;nLow++)
		{
			wchar_t wChar=nHigh*256+nLow;
		//	wprintf(L"%s",&wChar);
			WriteConsole(hStd,&wChar,1,NULL,NULL);
		}
		printf("\n");
	}
}
int main(int argc, char* argv[])
{
//	C_char();
//	W_char();
//	T_char();
	PrintfUnicode();
	return 0;
}
