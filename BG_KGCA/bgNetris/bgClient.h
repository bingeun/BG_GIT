#pragma once
#include "bgServerStd.h"
#include "bgProtocolGame.h"
#include "bgUser.h"
#include "bgNetris.h"

#define DEFAULT_SERVER_IP "127.0.0.1"

class bgClient : public bgUser
{
public:
	int				m_iSocket;
	unsigned long 	m_hSendThread;
	unsigned long 	m_hRecvThread;
	bool			m_bExit;
	char			m_strBuffer[128];
	bool			m_bSend;
	bool			m_bLoginOK;

	bgNetris		m_Netris[MAX_PLAYER];

public:
	int		CreateConnectSocket(int iPort);
	int		SendMsg(char* pMsg, WORD code);
	int		SendMsg(char* pMsg, int iSize, WORD code);
	int		ProcessPacket();
	
	void	SendPlayerInfo();

	bool	Init();
	bool	Frame();
	bool	Release();

public:
	bgClient(void);
	~bgClient(void);
};
