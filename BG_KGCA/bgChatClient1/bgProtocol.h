#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>

#define PACKET_HEADER_SIZE	(4)
#define MAX_MESSAGE			(2048)
#define MAX_NAME			(12)
#define MAX_CHAR_DATA		(64)
#define MAX_ITEM_DATA		(16)

#pragma pack(push, 1)

typedef struct
{
	WORD  len;
	WORD  type;
} PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char	msg[MAX_MESSAGE];
} UPACKET, *P_UPACKET;

// 캐릭터 생성 패킷
typedef struct
{
	byte	szName[MAX_NAME];
	int		iIndex;
	int		iData[MAX_CHAR_DATA];
} CHARACTER_INFO;

// 아이템 생성 패킷
typedef struct {
	byte	szName[MAX_NAME];
	int		iIndex;
	int		iData[MAX_ITEM_DATA];
} ITEM_INFO;

#pragma pack(pop)

#define PACKET_CHAT_MSG			1000
#define PACKET_GAME_START		2000
#define PACKET_GAME_END			3000
#define PACKET_CHAR_CREATE		4000
#define PACKET_CHAR_MOVE		5000
