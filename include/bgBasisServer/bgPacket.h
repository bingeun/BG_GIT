#pragma once
#include <windows.h>
#include "bgProtocol.h"

#define PACKETBUFFERSIZE   8192

class bgPacket
{
public:
	typedef struct
	{
		WORD* len;
		WORD* type;
	} PACKETHEADER;

public:
	PACKETHEADER	m_PacketHeader;
	char			m_strPacketBuffer[PACKETBUFFERSIZE];
	char*			m_pstrWritePosition;
	char*			m_pstrReadPosition;

public:
	int				m_iReceivedSize;

public:
	WORD		GetID() { return *m_PacketHeader.type; }
	WORD		GetSize() { return *m_PacketHeader.len; }
	char*		GetData() { return m_strPacketBuffer; }
	int			GetDataSize() { return m_iReceivedSize; }

	void		ReadData(void* buffer, int iSize);
	void		WriteData(void* buffer, int iSize);

	bgPacket&	SetID(unsigned short ID);
	
	bgPacket&	operator << (int arg);	// 데이터로 패킷 생성
	bgPacket&	operator >> (int& arg);	// 패킷에서 데이터 얻기

	bgPacket&	operator << (DWORD arg);
	bgPacket&	operator >> (DWORD& arg);

	bgPacket&	operator << (bool arg);
	bgPacket&	operator >> (bool& arg);

	bgPacket&	operator << (unsigned short arg);
	bgPacket&	operator >> (unsigned short& arg);

	bgPacket&	operator << (float arg);
	bgPacket&	operator >> (float& arg);

	bgPacket&	operator << (char* arg);
	bgPacket&	operator >> (char* arg);

	bgPacket&	operator << (bgPacket& arg);
	bgPacket&	operator >> (bgPacket& arg);

	void		Clear();

public:
	bgPacket(void);
	bgPacket(unsigned short type);
	~bgPacket(void);
};

