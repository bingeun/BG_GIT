#include "bgNetwork.h"

bool bgNetwork::Init()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == m_Sock)
	{
		return false;
	}
	return true;
}

bool bgNetwork::Release()
{
	closesocket(m_Sock);
	WSACleanup();
	return true;
}

bool bgNetwork::Connect(char* ip, int iPort)
{
	SOCKADDR_IN server;
	ZeroMemory(&server, sizeof(SOCKADDR_IN));
	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);
	server.sin_addr.s_addr = inet_addr(ip);

	DWORD dwRet = WSAConnect(m_Sock, (sockaddr*)&server, sizeof(SOCKADDR_IN), NULL, NULL, NULL, NULL);
	if (SOCKET_ERROR == dwRet)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}
	return true;
}

int bgNetwork::SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.type = type;
	memcpy(sendmsg.msg, msg, strlen(msg));
	sendmsg.ph.len = strlen(sendmsg.msg) + PACKET_HEADER_SIZE;
	int iRet = send(sock, (char*)&sendmsg, sendmsg.ph.len, 0);
	return iRet;
}

int bgNetwork::SendMsg(char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.type = type;
	memcpy(sendmsg.msg, msg, strlen(msg));
	sendmsg.ph.len = strlen(sendmsg.msg) + PACKET_HEADER_SIZE;
	int iRet = send(m_Sock, (char*)&sendmsg, sendmsg.ph.len, 0);
	return iRet;
}

int bgNetwork::RecvMsg()
{
	{
		int iLen = 0;
		m_iRecvByte += recv(m_Sock, &m_szRecvBuffer[m_iStartByte], PACKET_HEADER_SIZE - m_iRecvByte, 0);
		if (m_iRecvByte == 0 || m_iRecvByte == SOCKET_ERROR)
		{
			return 0;
		}
		if (m_iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer;
			while (m_iRecvByte < pPacket->ph.len)
			{
				m_iRecvByte += recv(m_Sock, &m_szRecvBuffer[m_iRecvByte],
					pPacket->ph.len - m_iRecvByte, 0);
			}
			if (m_iRecvByte == pPacket->ph.len)
			{
				UPACKET recvmsg;
				memset(&recvmsg, 0, sizeof(recvmsg));
				memcpy(&recvmsg, pPacket, pPacket->ph.len);
				m_RecvList.push_back(recvmsg);
				m_iStartByte = m_iRecvByte = 0;
			}
		}
		else
		{
			m_iStartByte += m_iRecvByte;
		}
	}
	return 0;
}

bgNetwork::bgNetwork()
{
	m_iRecvByte;
	m_iStartByte;
	m_bConnect = false;
	ZeroMemory(m_szRecvBuffer, sizeof(char) * 2048);
}

bgNetwork::~bgNetwork()
{
}
