#ifndef _MYLOG_H
#define _MYLOG_H
/*
 * FUN_IN(funname); add()auto

 * LOG_INF(("this is num :%d", 100));

 * LOG_BIN("instruct", p, nlen);
 
 * log for error need add file and line information
 */
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
typedef std::string stringa;

class stackclass
{
public:
	stackclass(const char *fun_name);
	~stackclass();
	
private:
	stringa m_strlog;
	int m_level;
};


class msglog
{
public:
	enum {COLUMN = 16};
	void logbinary(char *strinfo, const char *pbyte, int nlen);
	void logstring(const char *szformat, ...);
	void logtofile(const char *pszlog);
	friend msglog& get_log_instance();
private:
	msglog(FILE *fp = NULL, stringa strname = ""):
	   m_fp(fp), m_filename(strname){
		   char szbuff[128] = {0};
		   GetTempPathA(128, szbuff);
		   strcat_s(szbuff, 128, "mylog.txt");
		   m_filename = szbuff;

		   m_fp = fopen(m_filename.c_str(), "a");

	   };
	   ~msglog(){
		   fclose(m_fp);
		   m_fp = NULL;
	   }

private:
	FILE *m_fp;
	stringa m_filename;
	stringa m_strlog;
};
#endif

//{{ �˴�Ϊlog�Ľӿ�

//FUN_IN ��û��ֱ�ӵ�����־�������ͨ��һ����Ĺ�����������ʵ�ֵ�
#define FUN_IN(fun_name) stackclass sclss_##fun_name(#fun_name);
//������������Ҫ�����ţ������������Բ���
#define LOG_INF(loginfo) get_log_instance().logstring loginfo;
#define LOG_BIN(strinfo, pbdata, nlen) get_log_instance().logbinary(strinfo, pbdata, nlen);
//}}
