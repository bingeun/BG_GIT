#include "bgGamePacketPool.h"
#include "bgGameUser.h"
#include "bgDebugString.h"
#include "bgGameServer.h"
#include "bgGameUser.h"

void bgGamePacketPool::ProcessWork(T_PACKET* pUserData)
{
	UPACKET* pPacket = &(pUserData->packet);
	bgGameUser*   pUser = (bgGameUser*)pUserData->pUser;
	switch (pPacket->ph.type)
	{
	case PACKET_PLAYER_INFO:
	{
		pUser->Movement(pPacket);
		I_Server.Broadcastting(pPacket, pUser->m_Socket);
	}
	break;
	case PACKET_USER_NAME_ACK:
	{
		pUser->m_szName = pPacket->msg;
		char buffer[256] = { 0, };
		sprintf_s(buffer, "[%s]%s", pUser->m_szName.c_str(), "님이 입장하였습니다.");
		ZeroMemory(pPacket->msg, 2048);
		sprintf_s(pPacket->msg, "%s", buffer);
		pPacket->ph.len = sizeof(PACKET_HEADER) + (WORD)strlen(buffer);
		pPacket->ph.type = PACKET_USER_MSG;

		I_Server.Broadcastting(pPacket, pUser->m_Socket);
	}
	break;
	case PACKET_USER_MSG:
	{
		I_Server.Broadcastting(pPacket, pUser->m_Socket);
	}
	break;
	}
}

bgGamePacketPool::bgGamePacketPool(void)
{
}


bgGamePacketPool::~bgGamePacketPool(void)
{
}
