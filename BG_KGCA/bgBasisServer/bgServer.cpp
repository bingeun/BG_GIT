#include "bgServer.h"

bool bgServer::SendMsg(SOCKET socket, char* msg, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	//sprintf( sendmsg.msg, "%s", msg );
	sprintf_s(sendmsg.msg, "%s", msg);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + (WORD)strlen(sendmsg.msg);

	int iRet = send(socket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
		return false;

	return true;
}

bool bgServer::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	return true;
}

bool bgServer::Init()
{
	// 쓰레드 생성 
	CreateThread();
	return true;
}

bool bgServer::Run()
{
	return true;
}

bool bgServer::Release()
{
	return true;
}

bgServer::bgServer(void)
{
}

bgServer::~bgServer(void)
{
}
