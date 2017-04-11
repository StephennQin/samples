#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case ID_NEW:
		if(HIWORD(wParam)==0)
		MessageBox(hWnd,"�½������","infor",MB_OK);
		else if(HIWORD(wParam)==1)
		MessageBox(hWnd,"CTRL+M�����","infor",MB_OK);
		break;
	case ID_SET:
		MessageBox(hWnd,"CTRL+Y�����","infor",MB_OK);
		break;
	}
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
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
	wce.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);//ע������
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,CW_USEDEFAULT,
							CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,
							g_hInstance,NULL);
	return hWnd;
}
//��ʾ����
void Display(HWND hWnd)
{
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
}
//��Ϣѭ��
void Message()
{
	HACCEL hAccel = LoadAccelerators(g_hInstance,
			MAKEINTRESOURCE(IDR_ACCELERATOR1));
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		if(!TranslateAccelerator(nMsg.hwnd,hAccel,&nMsg))
		{
		TranslateMessage(&nMsg);//���ﴦ����ַ���Ϣ
		//��post��,��������ɷ�WM_KEYDOWN��Ϣ
		DispatchMessage(&nMsg);
		}
	}
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInstance=hInstance;
	Register("Main",WndProc);
	char szTitle[256] = {0};
	LoadString(g_hInstance,IDS_WND,szTitle,256);
	HWND hWnd=CreateMain("Main",szTitle);
	Display(hWnd);
	Message();
	return 0;
}



