// MyThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCThread.h"
#include "MyThread.h"
#include "MyDialog.h"

// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
{
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	CMyDialog dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
END_MESSAGE_MAP()


// CMyThread ��Ϣ�������
