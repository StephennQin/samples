
// SingleWnd.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSingleWndApp:
// �йش����ʵ�֣������ SingleWnd.cpp
//

class CSingleWndApp : public CWinAppEx
{
public:
	CSingleWndApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSingleWndApp theApp;