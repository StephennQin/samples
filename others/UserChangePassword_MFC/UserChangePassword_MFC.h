
// UserChangePassword_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUserChangePassword_MFCApp:
// �йش����ʵ�֣������ UserChangePassword_MFC.cpp
//

class CUserChangePassword_MFCApp : public CWinAppEx
{
public:
	CUserChangePassword_MFCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUserChangePassword_MFCApp theApp;