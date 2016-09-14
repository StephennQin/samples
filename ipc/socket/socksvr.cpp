// SockSvr.cpp : Defines the entry point for the console application.
//
/*
	send����ѭ���ж��Ƿ�����ȫ
	int nleft = nsize;
	while(nleft > 0)
	{
		int nsend = send(socket, psend, nleft, 0);	
		nleft -= nsend;
		psend += nsend;
	}
	
 */
#include <stdafx.h>
#include <WINSOCK2.H>
#include <windows.h>
#include <process.h>
#include <stdio.h>
#pragma  comment(lib,"ws2_32.lib")
static unsigned int g_clientno = 0;

typedef struct _param{
	SOCKET clientsocket;
	SOCKADDR_IN clientaddr;
	unsigned int clientno;
}PARAM, *PPARAM;

void __cdecl clientpro(void *pParam)
{
	PARAM para = *(PPARAM)pParam;
	//��������
	while(true){
		//��������
		char szRecv[256]={0};
		int nRecv;
		if(nRecv=recv(para.clientsocket,szRecv,256,0)==SOCKET_ERROR)
		{
			system("cls");
			closesocket(para.clientsocket);
			return ;
		}
		char *ClientIP=inet_ntoa(para.clientaddr.sin_addr);
		printf("--------------------------\n%d:%s:%s\n",para.clientno,ClientIP,szRecv);
		printf("DataLen:%d\n",nRecv);
		//��������
		getchar();
		char szSend[]="hello,i am a Server";
		send(para.clientsocket,szSend,strlen(szSend),0);
	}
}
//TCP��������
void TCPServer()
{
	//���������׽���
	SOCKET hSockSvr=
		socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (hSockSvr==INVALID_SOCKET)
	{
		return;
	}
	//��IP��ַ�Ͷ˿�
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5678);
	svrAddr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&svrAddr,
		sizeof(svrAddr));
	listen(hSockSvr,5);
	printf("�ȴ��ͻ�������...\n");
	PARAM para = {0};
	int nLen=sizeof(para.clientaddr);
	////////////////////////////////////
	while(true){
		para.clientsocket = accept(hSockSvr,(SOCKADDR*)&para.clientaddr,&nLen);
		para.clientno = g_clientno++;
		_beginthread(clientpro, 0, &para);
	}
	closesocket(hSockSvr);
}
void UDPServer()
{
	//�����׽���
	SOCKET hSockSvr=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockSvr==INVALID_SOCKET)
	{
		return;
	}
	//�󶨵�ַ�Ͷ˿�
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5679);
	svrAddr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&svrAddr,sizeof(svrAddr));
	//�����շ�
	//�����������Ƚ�������
	char szRecv[256]={0};
	SOCKADDR_IN clientAddr={0};
	int nLen=sizeof(clientAddr);
	int nRecv=recvfrom(hSockSvr,szRecv,sizeof(szRecv),0,
		(SOCKADDR*)&clientAddr,&nLen);
	char *IP=inet_ntoa(clientAddr.sin_addr);
	printf("%s:%s\n",IP,szRecv);
	printf("DataLen:%d\n",nRecv);
	//Ȼ����
	char szSend[]="hello,i am a UDPsender";
	sendto(hSockSvr,szSend,strlen(szSend),0,
		(SOCKADDR*)&clientAddr,nLen);
	//�ر��׽���
	closesocket(hSockSvr);
}
int main(int argc, char* argv[])
{
	//��ʼ��socket��
	WSADATA wsa={0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	//�����ͨ��
	TCPServer();
	//UDPServer();
	//ж��socket
	WSACleanup();
	return 0;
}