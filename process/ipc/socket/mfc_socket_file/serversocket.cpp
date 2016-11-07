// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCServer.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions
BOOL CServerSocket::InitServer(UINT nPort)
{//Create�ĵڶ�������������TCP����UDPͨ��
	if (!Create(nPort))
	{
		return FALSE;
	}
	return Listen();
}
//�����ļ���Ϣ�Ľṹ��
typedef struct _tagHeader
{
	char szName[128];
	long nLen;
}HEADER,*LPHEADER;
void CServerSocket::OnAccept(int nErrorCode) 
{
	//���տͻ�������
	CSocket client;
	Accept(client);
	//�����շ�(�����ļ�)
	//���Ƚ����ļ���Ϣ(���ƺͳ���)
	HEADER header={0};
	RecvData(client,(BYTE*)&header,sizeof(header));
	//Ȼ�󣬽����ļ�����
	BYTE *pData=(BYTE*)malloc(header.nLen);
	RecvData(client,pData,header.nLen);
	//���ļ����ݱ��浽��������
	CString sPath="c:/";
	sPath+=header.szName;
	AfxMessageBox(sPath);
	CFile file;
	file.Open(sPath,CFile::modeCreate|CFile::modeWrite);
	file.Write(pData,header.nLen);
	file.Close();
	free(pData);
	//�ر�
	client.Close();
	CAsyncSocket::OnAccept(nErrorCode);
}

BOOL CServerSocket::RecvData(CSocket& client,
							 BYTE* pData,long nLen)
{
	BYTE* pTmpData=pData;
	long nLeft=nLen;//��ʾʣ��Ļ�û�н��յ����ݵĳ���
	while (nLeft>0)
	{
		int nRecv=client.Receive(pTmpData,nLeft);
		if (nRecv==SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft-=nRecv;
		pTmpData+=nRecv;
	}
	return TRUE;
}
