#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
int g_kind=0;//��־��
void OnCommand(HWND hWnd,WPARAM wParam)
{//��ͼ������paint��Ϣ�ﻭ
	g_kind = LOWORD(wParam);
	switch(LOWORD(wParam))
	{
	case ID_REC:
	case ID_PIT:
	case ID_CIR:
	case ID_LINE:
	case ID_BMP:
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	}
}
void DrawPit(HDC hdc)
{
	for(int i=0;i<256;i++)
		for(int j=0;j<256;j++)
		SetPixel(hdc,i,j,RGB(i,j,0));
}
void DrawCir(HDC hdc)
{
	//��ʵ��������ǻ���Բ��
	Ellipse(hdc,200,200,300,300);
	Ellipse(hdc,240,240,500,54);
}
void DrawLine(HDC hdc)
{
	MoveToEx(hdc,50,50,NULL);
	LineTo(hdc,200,100);
//	Arc(hdc,200,300,400,500,230,230,450,450);
	//����ʱ�뷽��ȡ��
	//����ĺ�������ȡ������
	SetArcDirection(hdc,AD_CLOCKWISE);
	Arc(hdc,200,300,400,500,230,230,450,450);
}
void DrawRec(HDC hdc)
{
	Rectangle(hdc,300,-300,400,-400);
	//����Բ�Ǿ���,��������������ʾ���Ŀ�͸ߣ���������
	RoundRect(hdc,100,100,300,30,10,10);
}
void DrawBmp(HDC hdc)
{
	//�����Դ
	//����λͼ
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	BITMAP bmpInfo = {0};
	//��̬��ȡλͼ�Ŀ�͸�
	GetObject(hBmp,sizeof(bmpInfo),&bmpInfo);
	//����һ���뵱ǰDCƥ����ڴ�DC������һ����������
	HDC hMemdc = CreateCompatibleDC(hdc);
	HGDIOBJ nOldBmp = SelectObject(hMemdc,hBmp);
	//��ͼƬ�͸��ڴ�DC���ڴ�DC������ͼƬ�����������л��Ƴ���
	BitBlt(hdc,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,hMemdc,10,10,SRCCOPY);
//	StretchBlt(hdc,100,100,240,240,hMemdc,
//				0,0,48,48,NOTSRCCOPY);
	//���ų���
	SelectObject(hMemdc,nOldBmp);//����������滻���ܣ�������Ҫ����
	DeleteObject(hBmp);
	DeleteObject(hMemdc);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps={0};
	HDC hdc = BeginPaint(hWnd,&ps);
	HPEN hPen = CreatePen(PS_DASH,1,RGB(255,0,0));
	HGDIOBJ nOldPen = SelectObject(hdc,hPen);
//	HBRUSH hBrush= CreateSolidBrush(RGB(0,255,0));
//	HBRUSH hBrush= CreateHatchBrush(HS_CROSS,
//									RGB(0,255,0));
//	HBRUSH hBrush= CreatePatternBrush();
	//͸��ˢ��
//	HGDIOBJ hBrush= GetStockObject(NULL_BRUSH);
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	//λͼ��ˢҪ����λͼ��Դ
	HGDIOBJ nOldBrush = SelectObject(hdc,hBrush);
	int nOldMode = SetMapMode(hdc,MM_ANISOTROPIC);
	SetWindowExtEx(hdc,1,1,NULL);
	SetViewportExtEx(hdc,3,3,NULL);
	//��ı�����ķ��򣬸ı����ֵ�������
	switch(g_kind)
	{
	case ID_BMP:
		DrawBmp(hdc);
		break;
	case ID_REC:
		DrawRec(hdc);
		break;
	case ID_PIT:
		DrawPit(hdc);
		break;
	case ID_CIR:
		DrawCir(hdc);
		break;
	case ID_LINE:
		DrawLine(hdc);
		break;
	}
	SetMapMode(hdc,nOldMode);
	SelectObject(hdc,nOldBrush);
	SelectObject(hdc,nOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	EndPaint(hWnd,&ps);
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
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
	wce.hbrBackground=CreateSolidBrush(RGB(0,0,255));
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
	//WM_PAINT��Ϣ��GetMessage�����᲻���ڵ�ȥ�����費��Ҫ
	//PAINT����Ҫ�Ļ��Ͳ���WM_PAINT��Ϣ
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



