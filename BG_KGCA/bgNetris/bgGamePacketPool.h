#pragma once
#include "bgPacketPool.h"
#include "bgProtocolGame.h"

class bgGamePacketPool : public bgPacketPool
{
public:
	void ProcessWork(T_PACKET* pUserData);

public:
	bgGamePacketPool(void);
	~bgGamePacketPool(void);
};
