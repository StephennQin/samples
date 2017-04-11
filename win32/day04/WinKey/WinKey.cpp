#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
HANDLE g_hOutput = 0;
void OnPaint(HWND hWnd)
{
	char szText[]="WM_PAINT\n";
	WriteConsole(g_hOutput,szText,strlen(szText),
				NULL,NULL);
	PAINTSTRUCT ps={0};
	HDC hdc=BeginPaint(hWnd,&ps);
	TextOut(hdc,100,100,"hello",strlen("hello"));
	EndPaint(hWnd,&ps);
	//�����ľ�������WM_PAINT��Ϣ�Ĵ�����ȥ��
}
void OnKeyDown(HWND hWnd,WPARAM wParam)
{
	char szText[256] = {0};
	sprintf(szText,"WM_KEYDOWN:%08X\n",wParam);
	WriteConsole(g_hOutput,szText,strlen(szText),
		NULL,NULL);
}
void OnKeyUp(HWND hWnd,WPARAM wParam)
{
	char szText[256] = {0};
	sprintf(szText,"WM_KEYUP:%08X\n",wParam);
	WriteConsole(g_hOutput,szText,strlen(szText),
		NULL,NULL);
}
void OnChar(HWND hWnd,WPARAM wParam)
{
	char szText[256] = {0};
	sprintf(szText,"WM_CHAR:%08X\n",wParam);
	WriteConsole(g_hOutput,szText,strlen(szText),NULL,NULL);
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CHAR:
		OnChar(hWnd,wParam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(hWnd,wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(hWnd,wParam);
		break;
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd,NULL,TRUE);//����PAINT��Ϣ���־����������
		//������������ᷢ��paint��Ϣ
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
BOOL Register(LPSTR lpClassName,WNDPROC WndProc)
{
	WNDCLASSEX wce={0};
	wce.cbSize=sizeof(wce);
	wce.cbClsExtra=0;
	wce.cbWndExtra=0;
	wce.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wce.hCursor=NULL;
	wce.hIcon=NULL;
	wce.hIconSm=NULL;
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=WndProc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName=NULL;
	wce.style=CS_HREDRAW|CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);//ע������
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,
							WS_OVERLAPPEDWINDOW,
							100,100,500,500,NULL,NULL,
							g_hInstance,NULL);
	return hWnd;
}
//��ʾ����
void Display(HWND hWnd)
{
	ShowWindow(hWnd,SW_SHOW);
	//UpdateWindow(hWnd);
}
//��Ϣѭ��
void Message()
{
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	AllocConsole();
	g_hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



