
// GetFlights.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include <list>
#include <string>
#include "ZlProxyIp.h"
#include "common/xgmvar.h"
// CGetFlightsApp:
// �йش����ʵ�֣������ GetFlights.cpp
//
class CGetFlightsApp : public CWinApp
{
public:
	CGetFlightsApp();

// ��д
public:
	virtual BOOL InitInstance();
	static LONG WINAPI ExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);

public:
	std::list<std::wstring>	m_listIP;
	CCriticalSection	m_lockListIP;

	std::wstring GetValidIP();

// ʵ��

	DECLARE_MESSAGE_MAP()

	//���Դ���ip
	static UINT ThreadTestProxyIP( LPVOID pParam );

	typedef struct __tagTestIpThreadPara
	{
		int		id;
		CGetFlightsApp* pThis;
	}TTestIpThreadPara;

	static CWinThread*		m_pTestIpThread1;
	static CWinThread*		m_pTestIpThread2;
	static TTestIpThreadPara m_testIpThread1;
	static TTestIpThreadPara m_testIpThread2;

	static CZlProxyIp	m_tProxyIpBuf[2];
	static UINT		m_uCurWriteBufId;
	static UINT		m_uCurReadBufId;
	CCriticalSection	m_lockIpBuf;
	static MBOOL	m_bWaitPrepareIp;

};

extern CGetFlightsApp theApp;