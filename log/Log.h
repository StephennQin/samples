//*****************************************************************************
//  Copyright (c) 2009 Shenzhen Surfilter Network Technology Co., Ltd. 
//  All Rights Reserved.
//
//  Module Name:
//      Log.h ILog�ӿ�����������ILog�ĸ����ӿڹ���
//
//  Abstract:
//      ILog��HostAuditϵͳ�е�ϵͳ��־�ӿڣ�������¼ϵͳ���й����е���־��
//
//  Notes:
//
//  Created: 2009/09/09
//*****************************************************************************

#ifndef _LOG_H_
#define _LOG_H_
#include <windows.h>
#include <tchar.h>
#include <string>
//#include "Utility/Platform.h"
#include <stdio.h>
#define  VSNPRINTF _vsnprintf;
#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif
#define LOG_CONFIG_FILE "./HTLOG.ini"
typedef TCHAR tchar;

// enum LogLevel
// {
//     LL_None,
//     LL_Verbose,
//     LL_Brief,
//     LL_Warning,
//     LL_Critical
// };

enum LogType
{
    LT_Debug,
    LT_Information,
    LT_Warning,
    LT_Error,
	LT_None
};

class ILog
{
public:
    //+--------------------------------------------------------------------------
    //  Method:     Log         [ILog]
    //  Synopsis:   ��¼ϵͳ������־
    //  Arguments:  [in] sourceName
    //                   ��¼��־��ģ������
    //              [in] logType
    //                   enum LogType�ж������־����
    //              [in] logData
    //                   ��־�ַ�����
    //  Returns:    ��
    //+--------------------------------------------------------------------------
	virtual void Log(const tchar* sourceName, LogType logType, const char *format, ...) =0;

	virtual void LogBin(const tchar* sourceName, LogType logType, const BYTE *logData, int nLen) = 0;
};

#endif
