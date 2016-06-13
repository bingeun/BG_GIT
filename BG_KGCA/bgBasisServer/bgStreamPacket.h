#pragma once
#include "bgServerStd.h"
#include "bgProtocol.h"

#define MAX_RECV_SIZE 10000

class bgUser;

typedef struct
{
	UPACKET packet;
	bgUser* pUser;
} T_PACKET, *P_TPACKET;

class bgStreamPacket
{
public:
	std::list<T_PACKET> m_PacketList;
	typedef std::list<T_PACKET>::iterator m_PackItor;

public:
	UPACKET*	m_pPacket;
	char		m_RecvBuffer[MAX_RECV_SIZE];
	int			m_iStartPos;
	int			m_iWritePos;
	int			m_iReadPos;

public:
	void    Put(char* redvBuffer, int iSize, bgUser* = NULL);

public:
	bgStreamPacket();
	virtual ~bgStreamPacket();
};
