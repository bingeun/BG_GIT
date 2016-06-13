#pragma once
#include "bgPacketPool.h"

typedef struct _OVERLAPPEDEX : OVERLAPPED
{
	enum { MODE_RECV = 0, MODE_SEND = 1 };
	int iFlags;
	_OVERLAPPEDEX() { iFlags = MODE_RECV; }
} OVERLAPPEDEX;

class bgUser : public bgServerObj
{
public:
	bgStreamPacket	m_StreamPacket;
	SOCKET			m_Socket;
	basic_string<char>			m_szName;
	SOCKADDR_IN		m_UserAddress;
	WSABUF			m_szRecvBuffer;
	char			m_strBuffer[4096];
	OVERLAPPEDEX	m_ov;

public:
	bool Create();
	bool Run();
	virtual void AddPacket(T_PACKET& addPacket);
	virtual void DeleteUser(SOCKET socket);
	virtual void DeleteUser();
	virtual void WaitForPacketReceive();
	virtual void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);

public:
	bgUser(void);
	~bgUser(void);
};
