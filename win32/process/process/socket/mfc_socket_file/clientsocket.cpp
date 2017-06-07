// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCClient.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions
BOOL CClientSocket::InitClient(char* pIP,UINT nPort)
{
	//����
	if (!Create())
	{
		return FALSE;
	}
	//����
	return Connect(pIP,nPort);
}
//�����ļ���Ϣ�Ľṹ��
typedef struct _tagHeader
{
	char szName[128];
	long nLen;
}HEADER,*LPHEADER;

BOOL CClientSocket::SendFile(CString sPath)
{
	//�����շ�(�����ļ�)
	//���ȷ����ļ���Ϣ
	CFile file;
	file.Open(sPath,CFile::modeRead);
	CString sName=file.GetFileName();
	int nLen=file.GetLength();
	HEADER header={0};
	strcpy(header.szName,sName);
	header.nLen=nLen;
	SendData((BYTE*)&header,sizeof(header));
	//�����ļ�����
	BYTE* pData=(BYTE*)malloc(nLen);
	file.Read(pData,nLen);
	SendData(pData,nLen);
	//�ر�socket
	Close();
	return TRUE;
}
BOOL CClientSocket::SendData(BYTE* pData,long nLen)
{
	BYTE* pTmpData=pData;
	long nLeft=nLen;//ʣ�໹û�з��͵����ݵĳ���
	while (nLeft>0)
	{
		int nSend=Send(pTmpData,nLeft);
		if (nSend==SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft-=nSend;
		pTmpData+=nSend;
	}
	return TRUE;
}
