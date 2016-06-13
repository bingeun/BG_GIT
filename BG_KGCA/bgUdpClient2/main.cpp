#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <ws2tcpip.h>
//#include <Windows.h>
#include <stdio.h>

#pragma comment (lib,"ws2_32.lib")

int main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKET sockSend = socket(AF_INET, SOCK_DGRAM, 0);
	int iLen, iRet;
	
	int datasize;
	int len = sizeof(datasize);
	if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&datasize, &len) < 0)
	{
		return 0;
	}
	if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&datasize, &len) < 0)
	{
		return 0;
	}

	datasize = 10000;
	if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&datasize, len) < 0)
	{
		return 0;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&datasize, len) < 0)
	{
		return 0;
	}

	// Recv
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	DWORD dwErr = WSAGetLastError();

	int optexe = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&optexe, sizeof(optexe)) < 0)
	{
		return 0;
	}

	// 钢萍某胶泼 弊缝
	// 224.0.0.0 ~ 239.255.255.255
	struct ip_mreq mreq;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	mreq.imr_multiaddr.s_addr = inet_addr("235.7.8.9");

	// 家南 可记
	int ttl = 2;
	iRet = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}

	iRet = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}

	// Send
	SOCKADDR_IN addrSend;
	ZeroMemory(&addrSend, sizeof(addrSend));
	addrSend.sin_family = AF_INET;
	addrSend.sin_port = htons(9000);
	addrSend.sin_addr.s_addr = inet_addr("235.7.8.9");

	SOCKADDR_IN peer;
	char buf[256 + 1] = { 0, };
	char bufSend[256] = "<<<<< Send BG!! >>>>>";
	while (1)
	{
		// Send
		//iLen = sizeof(peer);
		//iRet = sendto(sock, bufSend, strlen(bufSend), 0, (SOCKADDR*)&addrSend, sizeof(addrSend));

		// Recv
		iLen = sizeof(peer);
		iRet = recvfrom(sock, buf, 256, 0, (SOCKADDR*)&peer, &iLen);
		buf[iRet] = 0;
		printf("\n[Recv] %s:%d : %s", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port), buf);

		Sleep(1000);
	}

	// 家南 可记
	iRet = setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}

	iRet = setsockopt(sockSend, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}

	closesocket(sockSend);
	closesocket(sock);
	WSACleanup();
	return 0;
}
