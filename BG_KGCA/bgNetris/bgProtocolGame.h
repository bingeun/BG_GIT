#pragma once
#include "bgProtocol.h"

#define PACKET_USER_NAME_REQ	1000	// ��ȭ�� ��û
#define PACKET_USER_NAME_ACK	1001	// ��ȭ�� ����
#define PACKET_USER_MSG			1002	// �޼��� ����

//////////////////////////////////////////////////
#pragma  pack( push, 1 )

#define PACKET_PLAYER_INFO		3000	// �÷��̾� ���� ����
#define PLAYER_INFO_CMD_INIT	0
#define PLAYER_INFO_CMD_MOVE	1
#define PLAYER_INFO_CMD_SAVE	2
#define PLAYER_INFO_CMD_NEXT	3
typedef struct
{
	UCHAR	iID;
	UCHAR	iCMD;
	WORD	iValue;
	UCHAR	iX;
	UCHAR	iY;
	UCHAR	iBlock;
	UCHAR	iRotate;
} TPACKET_PLAYER_INFO;

#pragma pack(pop)
//////////////////////////////////////////////////
