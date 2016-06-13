#pragma once
#include "bgUser.h"

class bgGameUser : public bgUser
{
public:
	int		m_iX;
	int		m_iY;
	int		m_iBlock;
	int		m_iRotate;

public:
	void	Movement(UPACKET* pPacket);
	void	AddPacket(T_PACKET& addPacket);
	void	DeleteUser(SOCKET socket);
	void	DeleteUser();
	void	Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);

public:
	bgGameUser(void);
	~bgGameUser(void);
};
