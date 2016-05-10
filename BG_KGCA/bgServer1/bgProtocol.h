#pragma once
#include <Windows.h>

#define PACKET_HEADER_SIZE		(4)
#define PACKET_CHAR_MSG			(1000)
#define PACKET_CREATE_CHARACTER	(2000)

/////////////////////////////////////////////
////////// 1바이트 단위 패킹 시작!
#pragma pack(push, 1)

typedef struct
{
	WORD	len;
	WORD	type;
} PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char	msg[2048];
} UPACKET, *P_UPACKET;

typedef struct
{
	byte	szName[13];
	int		iIndex;
	int		iData[50];
} CHARACTER_INFO;

#pragma pack(pop)
////////// 1바이트 단위 패킹 종료!
/////////////////////////////////////////////

// YPACKET p;
// p.msg = "KGCA";
// p.len = PACKET_HEADER_SIZE + strlen(p.msg);
// p.type = PACKET_CHAR_MSG;
// send(p ...);



int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendMsg;
	ZeroMemory(&sendMsg, sizeof(UPACKET));

}