#include "stdafx.h"
#define WM_MYMESSAGE WM_USER+1001
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate( LPCREATESTRUCT pcs);
	afx_msg void OnPaint( );
	afx_msg LRESULT OnMyMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnOk();
	afx_msg void OnEnChange();
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_EN_CHANGE(1002,OnEnChange)
	ON_MESSAGE(WM_MYMESSAGE,OnMyMsg)//��Щ������˴�������ô
	ON_WM_CREATE()//д������Ҫͨ��MSDN���鿴��
	ON_WM_PAINT()
	ON_COMMAND(1001,OnOk)
END_MESSAGE_MAP()
void CMyFrameWnd::OnEnChange()
{
	AfxMessageBox("���ݱ��޸�");
}
void CMyFrameWnd::OnOk()
{
	AfxMessageBox("OK��ť�����");
}
LRESULT CMyFrameWnd::OnMyMsg(WPARAM wParam, LPARAM lParamM)
{
	AfxMessageBox("�Լ��������Ϣ������");
	return 0;
}
void CMyFrameWnd::OnPaint( )
{
	PAINTSTRUCT ps ={0};
	HDC hdc = ::BeginPaint(this->m_hWnd,&ps);
	::TextOut(hdc,50,50,"hello",5);
	::EndPaint(m_hWnd,&ps);
}
int CMyFrameWnd::OnCreate( LPCREATESTRUCT pcs)
{
	::CreateWindowEx(0,"BUTTON","OK",
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		100,100,100,40,this->m_hWnd,(HMENU)1001,
		AfxGetInstanceHandle(),NULL);
	::CreateWindowEx(0,"EDIT","",
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		400,100,100,100,this->m_hWnd,
		(HMENU)1002,AfxGetInstanceHandle(),NULL);
	AfxMessageBox("CMyFrameWnd::OnCreate");
	::PostMessage(this->m_hWnd,WM_MYMESSAGE,1,2);
	return CFrameWnd::OnCreate(pcs);
}
class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd *pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCCmd");
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}
