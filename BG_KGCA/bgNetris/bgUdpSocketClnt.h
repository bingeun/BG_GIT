#pragma once
#include "bgThread.h"
#include <ws2tcpip.h>

class bgUdpSocketClnt : public bgThread
{
public:
	SOCKET			m_SendSocket;
	SOCKET			m_RecvSocket;
	SOCKADDR_IN		m_RecvAddr;
	SOCKADDR_IN		m_SendAddr;
	vector<string>	m_ipList;

public:
	bool	Init();
	bool	Run();
	bool	Release();
	int		GetIPList();

public:
	bgUdpSocketClnt(void);
	~bgUdpSocketClnt(void);
};
