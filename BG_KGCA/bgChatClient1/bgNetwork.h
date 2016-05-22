#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgProtocol.h"

class bgNetwork
{
public:
	SOCKET	m_Sock;
	bool	m_bConnect;
	char	m_szRecvBuffer[2048];
	int		m_iRecvByte;
	int		m_iStartByte;

public:
	std::list<UPACKET>  m_RecvList;

public:
	bool	Init();
	bool	Release();
	virtual int		RecvMsg();
	virtual int		SendMsg(char* msg, WORD type);
	virtual int		SendMsg(SOCKET sock, char* msg, WORD type);
	virtual void	MsgEvent(MSG msg) {};
	virtual bool	Connect(char* ip, int iPort);

public:
	bgNetwork();
	virtual ~bgNetwork();
};
