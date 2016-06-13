#pragma once
#include "bgThread.h"
#include "bgPacket.h"

class bgAcceptor : public bgThread
{
public:
	SOCKET		m_ListenSock;

public:
	bool		Run();
	bool		Release();
	bool		Set(int iPort, const char* strAddress = 0);
	virtual void	AddUser(SOCKET socket, SOCKADDR_IN address);

public:
	bgAcceptor(void);
	~bgAcceptor(void);
};
