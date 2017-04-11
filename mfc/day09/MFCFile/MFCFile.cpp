// MFCFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MFCFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
//�ļ����ԵĻ�ȡ������
void FileStatus()
{
	CFileStatus status;
	CFile::GetStatus("c:/mfc.txt",status);
	//����һ��ʱ��α���(7��)
	CTimeSpan span(7,0,0,0);
	//�����ļ��Ĵ���ʱ����ǰһ��
	status.m_ctime-=span;
	//�����ļ�����
	CFile::SetStatus("c:/mfc.txt",status);
}
//�ļ����Ҳ���
void FileFind(CString sPath)
{
	//��ʼ����
	CFileFind find;
	BOOL bRet = find.FindFile(sPath+"/*.*");
	while(bRet)
	{
		//������һ��
		bRet = find.FindNextFile();
		//��ȡ�ļ�����
		//CString sName = find.GetFileName();
		sPath = find.GetFilePath();
	if(!find.IsDots())
	{
		if(find.IsDirectory())
		{
			printf("Ŀ¼:%s\n",sPath);
			FileFind(sPath);
		}else
		{
			printf("�ļ�:%s\n",sPath);
		}
	}
	}
	find.Close();
}
// int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
// {
// //	FileStatus();
// 	FileFind("g:");
// 	return 0;
// }


