#include "bgGameAccept.h"
#include "bgGameServer.h"
/*
void bgGameAccept::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	I_Server.AddUser(socket, address);
}
*/
void bgGameAccept::AddUser(SOCKET socket, SOCKADDR_IN address, UCHAR iID)
{
	I_Server.AddUser(socket, address, iID);
}

bgGameAccept::bgGameAccept(void)
{
}


bgGameAccept::~bgGameAccept(void)
{
}
