#pragma once
#include "bgThread.h"
#include "bgStreamPacket.h"

class bgPacketPool : public bgServerObj
{
public:
	std::list<T_PACKET> m_PacketList;
	typedef std::list<T_PACKET>::iterator m_PackItor;

public:
	virtual bool	AddPacket(T_PACKET& addPacket);
	virtual bool	ProcessPacket();
	virtual void	ProcessWork(T_PACKET* pUserData);

public:
	bgPacketPool(void);
	~bgPacketPool(void);
};
