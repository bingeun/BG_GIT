#pragma once
#include "bgStreamPacket.h"
#include "bgThread.h"
#include "bgAcceptor.h"
#include "bgUser.h"

class bgServer : public bgThread
{
public:
	bgAcceptor	m_Acceptor;

public:
	bool		Init();
	bool		Release();
	bool		Run();
	virtual bool	AddUser(SOCKET socket, SOCKADDR_IN address);
	bool		SendMsg(SOCKET socket, char* msg, WORD code);

public:
	bgServer(void);
	~bgServer(void);
};
