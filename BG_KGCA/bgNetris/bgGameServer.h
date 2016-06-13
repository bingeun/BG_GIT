#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "bgStd.h"
#include "bgServer.h"
#include "bgGamePacketPool.h"
#include "bgGameAccept.h"
#include "bgGameUser.h"

#define I_Server bgGameServer::GetInstance()

class bgGameServer : public bgSingleton<bgGameServer>, public bgServer
{
private:
	friend class bgSingleton<bgGameServer>;

public:
	bgGamePacketPool   m_PacketPool;
	bgGameAccept       m_Acceptor;

	std::list<bgGameUser*>	m_UserList;
	typedef std::list<bgGameUser*>::iterator m_ListItor;

	int		m_iUserCount;

public:
	bool	Init();
	bool	Release();
	bool	Run();
	LRESULT	MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void	Print(char* fmt, ...);
	//bool	AddUser(SOCKET socket, SOCKADDR_IN address);
	bool	AddUser(SOCKET socket, SOCKADDR_IN address, UCHAR iID);
	void	DeleteUser(SOCKET socket);
	void	DeleteUser(bgGameUser* pUser);
	void	Broadcastting(char* msg, WORD code, SOCKET SendSocket = 0);
	void	Broadcastting(T_PACKET* pUserData);
	void	Broadcastting(UPACKET* pPacket, SOCKET pSendUser = NULL);

public:
	bgGameServer(void);
	~bgGameServer(void);
};
