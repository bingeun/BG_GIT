#include "bgGameServer.h"
#include "bgServer.h"
#include "bgServerIOCP.h"
#include "bgDebugString.h"
/*
bool bgGameServer::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	{
		bgSynchronize sync(this);
		bgGameUser* pUser = NULL;
		SAFE_NEW(pUser, bgGameUser);
		pUser->m_Socket = socket;
		pUser->m_UserAddress = address;

		I_Debug.Print("IP=%s, PORT=%d", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

		if (pUser)
		{
			I_Server.SendMsg(pUser->m_Socket, "환영합니다~!", PACKET_USER_NAME_REQ);
			m_UserList.push_back(pUser);

			I_ServerIOCP.AddHandleToIOCP((HANDLE)socket, (DWORD)pUser);
			pUser->Create();
		}
	}
	return true;
}
*/
bool bgGameServer::AddUser(SOCKET socket, SOCKADDR_IN address, UCHAR iID)
{
	{
		bgSynchronize sync(this);
		bgGameUser* pUser = NULL;
		SAFE_NEW(pUser, bgGameUser);
		pUser->m_Socket = socket;
		pUser->m_UserAddress = address;

		I_Debug.Print("IP=%s, PORT=%d", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

		if (pUser)
		{
			I_Server.SendMsg(pUser->m_Socket, (char*)iID, PACKET_USER_NAME_REQ);
			m_UserList.push_back(pUser);

			I_ServerIOCP.AddHandleToIOCP((HANDLE)socket, (DWORD)pUser);
			pUser->Create();
		}
	}
	return true;
}

void bgGameServer::DeleteUser(SOCKET socket)
{
	{
		bgSynchronize sync(this);
		std::list<bgGameUser*>::iterator iter;
		std::list<bgGameUser*>::iterator delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin(); iter != I_Server.m_UserList.end(); iter++)
		{
			bgGameUser* pUser = (bgGameUser*)*iter;
			if (pUser->m_Socket == socket)
			{
				char buffer[256] = { 0, };
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				I_Debug.Print("%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				I_Server.Broadcastting(buffer, PACKET_USER_MSG, pUser->m_Socket);
				closesocket(pUser->m_Socket);
				delUser = iter;
				SAFE_DEL(pUser);
				break;
			}
		}
		I_Server.m_UserList.erase(delUser);
	}
}

void bgGameServer::DeleteUser(bgGameUser* pDeleteUser)
{
	{
		bgSynchronize sync(this);
		std::list<bgGameUser*>::iterator iter;
		std::list<bgGameUser*>::iterator delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin(); iter != I_Server.m_UserList.end(); iter++)
		{
			bgGameUser* pUser = (bgGameUser*)*iter;
			if (pUser == pDeleteUser)
			{
				char buffer[256] = { 0, };
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				I_Debug.Print("%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				I_Server.Broadcastting(buffer, PACKET_USER_MSG, pUser->m_Socket);
				closesocket(pUser->m_Socket);
				delUser = iter;
				SAFE_DEL(pUser);
				break;
			}
		}
		I_Server.m_UserList.erase(delUser);
	}
}

void bgGameServer::Broadcastting(UPACKET* pPacket, SOCKET SendSocket)
{
	{
		bgSynchronize sync(this);
		std::list<bgGameUser*>::iterator iter;
		std::list<bgGameUser*>::iterator delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
		iter != I_Server.m_UserList.end();
			iter++)
		{
			bgGameUser* pUser = (bgGameUser*)*iter;
			//if( 0==SendSocket /*|| pUser->m_Socket != SendSocket*/ )
			{
				int iRet = send(pUser->m_Socket, (char*)pPacket, pPacket->ph.len, 0);
				if (iRet < 0)
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			I_Debug.Print("%s에게 %s 보냈습니다.", pUser->m_szName.c_str(), pPacket->msg);
		}
	}
}

void bgGameServer::Broadcastting(T_PACKET* pUserData)
{
	{
		bgSynchronize sync(this);
		std::list<bgGameUser*>::iterator iter;
		std::list<bgGameUser*>::iterator delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
		iter != I_Server.m_UserList.end();
			iter++)
		{
			bgGameUser* pUser = (bgGameUser*)*iter;
			if (pUser->m_Socket != pUserData->pUser->m_Socket)
			{
				int iRet = send(pUser->m_Socket, (char*)&pUserData->packet, pUserData->packet.ph.len, 0);
				if (iRet < 0)
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			I_Debug.Print("%s에게 %s님의 %s 보냈습니다.", pUser->m_szName.c_str(),
				pUserData->pUser->m_szName.c_str(),
				pUserData->packet.msg);
		}
	}
}

void bgGameServer::Broadcastting(char* msg, WORD code, SOCKET SendSocket)
{
	{
		bgSynchronize sync(this);
		std::list<bgGameUser*>::iterator iter;
		std::list<bgGameUser*>::iterator delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
		iter != I_Server.m_UserList.end();
			iter++)
		{
			bgGameUser* pUser = (bgGameUser*)*iter;
			if (0 == SendSocket || pUser->m_Socket != SendSocket)
			{
				if (!SendMsg(pUser->m_Socket, msg, code))
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			I_Debug.Print("%s%s%s", pUser->m_szName.c_str(), msg, "보냈습니다.");
		}
	}
}

bool bgGameServer::Init()
{
	I_Debug.Print("%s", "서버 시작합니다.");
	bgServer::Init();
	m_Acceptor.Set(10000, NULL);
	return true;
}

bool bgGameServer::Release()
{
	return bgServer::Release();
}

bool bgGameServer::Run()
{
	while (m_bStarted)
	{
		m_PacketPool.ProcessPacket();
		Sleep(1);
	}
	return true;
}

bgGameServer::bgGameServer(void)
{

}

bgGameServer::~bgGameServer(void)
{
}
