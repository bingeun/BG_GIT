#include "bgGameUser.h"
#include "bgGameServer.h"

//typedef struct
//{
//	WORD  iX;
//	WORD  iY;
//	WORD  iBlock;
//	WORD  iRotate;
//} TPACKET_PLAYER_INFO;

void bgGameUser::Movement(UPACKET* pPacket)
{
	TPACKET_PLAYER_INFO user;
	memcpy(&user, pPacket->msg, sizeof(char)*pPacket->ph.len - 4);
	m_iX = user.iX;
	m_iY = user.iY;
	m_iBlock = user.iBlock;
	m_iRotate = user.iRotate;
}

void bgGameUser::AddPacket(T_PACKET& addPacket)
{
	I_Server.m_PacketPool.AddPacket(addPacket);
}

void bgGameUser::DeleteUser(SOCKET socket)
{
	I_Server.DeleteUser(socket);
}

void bgGameUser::DeleteUser()
{
	I_Server.DeleteUser(this);
}

void bgGameUser::Dispatch(DWORD dwByteSize, LPOVERLAPPED ov)
{
	OVERLAPPEDEX* pOV = (OVERLAPPEDEX*)ov;
	if (dwByteSize == 0)
		return;
	if (pOV->iFlags == OVERLAPPEDEX::MODE_RECV)
	{
		m_StreamPacket.Put(m_szRecvBuffer.buf, dwByteSize, this);
	}
	if (pOV->iFlags == OVERLAPPEDEX::MODE_SEND)
	{
	}
	WaitForPacketReceive();
}

bgGameUser::bgGameUser(void)
{
}


bgGameUser::~bgGameUser(void)
{
}
