#pragma once
#include "bgThread.h"
#include <ws2tcpip.h>

class bgUdpSocketSvr : public bgThread
{
public:
	SOCKET		m_RecvSocket;
	SOCKET		m_SendSocket;
	SOCKADDR_IN	m_RecvAddr;
	SOCKADDR_IN	m_SendAddr;

public:
	bool		Init();
	bool		Run();
	bool		Release();

public:
	bgUdpSocketSvr(void);
	~bgUdpSocketSvr(void);
};
