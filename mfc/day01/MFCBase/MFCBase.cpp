#include "stdafx.h"
class CMyFrameWnd : public CFrameWnd
{
};
class CMyWinApp : public CWinApp
{
public:
	CMyWinApp();
	virtual BOOL InitInstance();
	virtual BOOL InitApplication();
	virtual int Run();
	virtual BOOL OnIdle( LONG lCount );
	virtual int ExitInstance();
};
int CMyWinApp::ExitInstance()
{
	AfxMessageBox("�ƺ���");
	return CWinApp::ExitInstance();
}
BOOL CMyWinApp::OnIdle(LONG lCount)
{
//	AfxMessageBox("���д���");
	return CWinApp::OnIdle(lCount);
}
BOOL CMyWinApp::InitApplication()
{
	AfxMessageBox("��ʼ��");
	return CWinApp::InitApplication();
}
int CMyWinApp::Run()
{
	AfxMessageBox("��Ϣѭ��");
	return CWinApp::Run();
}
CMyWinApp::CMyWinApp(){}

CMyWinApp theApp;//���Ƶ�
BOOL CMyWinApp::InitInstance()
{//�˺�����thisΪ&theApp
	CMyFrameWnd *pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCBase");
	m_pMainWnd = pFrame;
	pFrame ->ShowWindow(SW_SHOW);
	pFrame ->UpdateWindow();
	return TRUE;
}