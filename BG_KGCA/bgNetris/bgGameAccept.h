#pragma once
#include "bgAcceptor.h"

class bgGameAccept : public bgAcceptor
{
public:
	//void AddUser(SOCKET socket, SOCKADDR_IN address);
	void AddUser(SOCKET socket, SOCKADDR_IN address, UCHAR iID);

public:
	bgGameAccept(void);
	~bgGameAccept(void);
};
