#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
	HCURSOR hRec=LoadCursorFromFile("c:/windows/Cursors/aero_working.ani");
	HCURSOR hBall=LoadCursorFromFile("C:/Windows/Cursors/aero_working_l.ani");
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case ID_NEW:
		MessageBox(hWnd,"�½������","infor",MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd,"�˳������","infor",MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd,"���ڱ����","infor",MB_OK);
		break;
	}
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hWnd,&ps);
	HICON hIcon = LoadIcon(g_hInstance,
			MAKEINTRESOURCE(IDI_ICON1));
	DrawIcon(hdc,100,100,hIcon);
	EndPaint(hWnd,&ps);
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_SETCURSOR:
		if(LOWORD(lParam)==HTCLIENT){
//		HCURSOR hRec=LoadCursorFromFile("c:/windows/Cursors/aero_working.ani");
//		HCURSOR hBall=LoadCursorFromFile("C:/Windows/Cursors/aero_working_l.ani");
//		HCURSOR hRec=LoadCursor(g_hInstance,
//				MAKEINTRESOURCE(IDC_CURSOR1));
//		HCURSOR hBall = LoadCursor(g_hInstance,
//				MAKEINTRESOURCE(IDC_CURSOR2));
		POINT pt={0};
		GetCursorPos(&pt);//��Ļ����ϵ��������λ��
		ScreenToClient(hWnd,&pt);
		RECT rc={0};
		GetClientRect (hWnd,&rc);//�ͻ������ڱ߽���Ϣ
		if(pt.x<=rc.right/2)
			SetCursor(hRec);
		else
			SetCursor(hBall);
		return 0;//���Զ��崦����Ĭ�ϴ����г�ͻ��Ҫ����
		}//ΪʲôҪ�Ӵ����ţ����������case���õ�hBall?
		else
		{
			//�ڷǿͻ���Ĭ�ϴ���defwindowproc
		}
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
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
	wce.hCursor=LoadCursor(g_hInstance,MAKEINTRESOURCE(IDC_CURSOR2));
	wce.hIcon=LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_ICON2));
	wce.hIconSm=NULL;//LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=WndProc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName=NULL;//MAKEINTRESOURCE(IDR_MENU1);//���Ͳ�ƥ�䣬��Ҫ����ת
	//MAKEINTRESOURCE -�����ת�����κ���Դ������ת��
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);//ע������
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)//ֻ�ǽ�ĳ������
{
	HMENU hMenu=LoadMenu(g_hInstance,MAKEINTRESOURCE(IDR_MENU1));
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,CW_USEDEFAULT,
							CW_USEDEFAULT,CW_USEDEFAULT,NULL,
							hMenu,//���˵���������Ҫ�������
							g_hInstance,NULL);
// 	HICON hIcon=LoadIcon(g_hInstance,
// 		MAKEINTRESOURCE(IDI_ICON1));
// 	SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
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



