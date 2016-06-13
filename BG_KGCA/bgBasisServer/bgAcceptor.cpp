#include "stdio.h"
#include "bgAcceptor.h"
#include "bgUser.h"
#include "bgServer.h"
#include "bgServerIOCP.h"

bool bgAcceptor::Release()
{
	return true;
}

bool bgAcceptor::Run()
{
	SOCKET clientSocket;
	SOCKADDR_IN clientaddr;
	int   addrlen;
	while (m_bStarted)
	{
		addrlen = sizeof(clientaddr);
		clientSocket = accept(m_ListenSock, (SOCKADDR*)&clientaddr, &addrlen);
		if (clientSocket == INVALID_SOCKET)
			continue;

		AddUser(clientSocket, clientaddr);
		Sleep(10);
	}
	return true;
}

void bgAcceptor::AddUser(SOCKET socket, SOCKADDR_IN address)
{
}

bool bgAcceptor::Set(int iPort, const char* strAddress)
{
	int iRet;
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);
	/////////////////////////////////
	//
	/////////////////////////////////
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSock == INVALID_SOCKET)
		return false;

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	if (strAddress == NULL)
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
		serveraddr.sin_addr.s_addr = inet_addr(strAddress);

	serveraddr.sin_port = htons(iPort);
	iRet = ::bind(m_ListenSock, (SOCKADDR*)&serveraddr, sizeof(SOCKADDR));
	if (iRet == SOCKET_ERROR)
		return false;

	iRet = listen(m_ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
		return false;

	int optval = 1;
	setsockopt(m_ListenSock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

	linger optval2;
	int iSize = sizeof(optval2);
	optval2.l_linger = 1000;
	optval2.l_onoff = 1;
	getsockopt(m_ListenSock, SOL_SOCKET, SO_LINGER, (char*)&optval2, &iSize);
	setsockopt(m_ListenSock, SOL_SOCKET, SO_LINGER, (char*)&optval2, iSize);

	int socketType1;
	int typeLen1 = sizeof(socketType1);
	getsockopt(m_ListenSock, SOL_SOCKET, SO_TYPE, (char*)&socketType1, &typeLen1);
	//if( socketType1 == SOCK_STREAM )

	getsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&socketType1, &typeLen1);
	getsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&socketType1, &typeLen1);

	// 쓰레드 생성 
	CreateThread();

	return true;
}
bgAcceptor::bgAcceptor(void)
{
}

bgAcceptor::~bgAcceptor(void)
{
}
