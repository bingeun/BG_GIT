#include "bgPacketPool.h"


bool bgPacketPool::AddPacket(T_PACKET& addPacket)
{
	{
		bgSynchronize sync(this);
		m_PacketList.push_back(addPacket);
	}
	return true;
}

bool bgPacketPool::ProcessPacket()
{
	{
		bgSynchronize sync(this);
		std::list<T_PACKET>::iterator iter;
		for (iter = m_PacketList.begin(); iter != m_PacketList.end(); iter++)
		{
			T_PACKET* pUserData = (T_PACKET*)&(*iter);
			ProcessWork(pUserData);
		}
		m_PacketList.clear();
	}
	return true;
}

void bgPacketPool::ProcessWork(T_PACKET* pUserData)
{
}

bgPacketPool::bgPacketPool(void)
{
}


bgPacketPool::~bgPacketPool(void)
{
}
