#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
INT CALLBACK DialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		MessageBox(hwndDlg,"WM_INITDIALOG","infor",MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndDlg,"WM_CREATE","infor",MB_OK);
		break;
	case WM_SYSCOMMAND:
		//�����Ϣ������������Ĭ�ϴ����
		if(wParam == SC_CLOSE)
		{
			DestroyWindow(hwndDlg);
//			EndDialog(hwndDlg,12345);
			//destroywindow�������ٴ��ڣ����ǲ��ܽ�����Ϣѭ��
			//ֻ�����ز�������
			return true;
		}
		break;
	}
	return false;
	//����Ĭ�ϵĴ���������
}

void OnNoModel(HWND hWnd)
{
	HWND hwndDlg=CreateDialog(g_hInstance,MAKEINTRESOURCE(IDD_DIALOG1),
				hWnd,DialogProc);
	ShowWindow(hwndDlg,SW_SHOWDEFAULT);
}
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case ID_NOMODEL:
		OnNoModel(hWnd);
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



