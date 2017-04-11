#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
void OnCreate(HWND hWnd)
{
	HMENU hSys = GetSystemMenu(hWnd,FALSE);
	for(int i=0;i<6;i++)
		DeleteMenu(hSys,0,MF_BYPOSITION);
	AppendMenu(hSys,MF_SEPARATOR,0,"");
	AppendMenu(hSys,MF_STRING,1001,"�ҵĲ˵���");
}
void OnSysCommand(HWND hWnd,WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 1001:
		MessageBox(hWnd,"�ҵĲ˵�����","infor",MB_OK);
		break;
	}
}/*
void OnRButtonUp(HWND hWnd,LPARAM lParam)
{
	POINT pt={0};
	pt.x=LOWORD(lParam);
	pt.y=HIWORD(lParam);
	ClientToScreen(hWnd,(LPPOINT)&pt);
	HMENU hPopup = CreatePopupMenu();
	AppendMenu(hPopup,MF_STRING,1002,"�½�");
	AppendMenu(hPopup,MF_SEPARATOR,0,"");
	AppendMenu(hPopup,MF_STRING,1003,"�˳�");
	BOOL nRet = TrackPopupMenu(hPopup,//��������
		TPM_CENTERALIGN|TPM_VCENTERALIGN|TPM_RETURNCMD,
		pt.x,pt.y,0,hWnd,NULL);//������ϵ��ͬ
	switch(nRet)
	{
	case 1002:
		MessageBox(hWnd,"û��ͨ����Ϣ���������½�","infor",MB_OK);
		break;
	case 1003:
		MessageBox(hWnd,"û��ͨ����Ϣ��������\"�˳�\"","infor",MB_OK);
		break;
	}
}*/
void OnCommand(HWND hWnd,WPARAM wParam)
{
	char szText[256]={0};
	switch (LOWORD(wParam))
	{
	case 1002:
		sprintf(szText,"�½�");
		break;
	case 1003:
		sprintf(szText,"�˳�");
		break;
	}
	
	MessageBox(hWnd,szText,"infor",MB_OK);
}
void OnContextMenu(HWND hWnd,LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();
	AppendMenu(hPopup,MF_STRING,1002,"�½�");
	AppendMenu(hPopup,MF_SEPARATOR,0,"");
	AppendMenu(hPopup,MF_STRING,1003,"�˳�");
	TrackPopupMenu(hPopup,//��������
		TPM_CENTERALIGN|TPM_VCENTERALIGN,
		LOWORD(lParam),HIWORD(lParam),0,hWnd,NULL);
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CONTEXTMENU://����Ϣ����ӰӦ�Ҽ������������WM_RBUTTONUP�����˵��Ƚ�ҵ���ʹ�ô˺���
		OnContextMenu(hWnd,lParam);
		//MessageBox(hWnd, "�Ҽ������", NULL, MB_OK);
		break;
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
		break;
	case WM_RBUTTONUP:
		//OnRButtonUp(hWnd,lParam);
		break;
	case WM_SYSCOMMAND:
		OnSysCommand(hWnd,wParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
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
							100,100,500,500,NULL,NULL,
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
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



