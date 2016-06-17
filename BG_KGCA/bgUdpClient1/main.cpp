#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
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

	BOOL bEnable = TRUE;
	iRet = setsockopt(sockSend, SOL_SOCKET, SO_BROADCAST, (char*)&bEnable, sizeof(bEnable));
	if(iRet == SOCKET_ERROR)
	{
		return 1;
	}

	// Recv
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));

	// Send
	SOCKADDR_IN addrSend;
	ZeroMemory(&addrSend, sizeof(addrSend));
	addrSend.sin_family = AF_INET;
	addrSend.sin_port = htons(9000);
	addrSend.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	SOCKADDR_IN peer;
	char buf[256 + 1] = { 0, };
	char bufSend[256] = "<<<<< Send BG!! >>>>>";
	while (1)
	{
		// Send
		iLen = sizeof(peer);
		iRet = sendto(sock, bufSend, strlen(bufSend), 0, (SOCKADDR*)&addrSend, sizeof(addrSend));

		// Recv
		iLen = sizeof(peer);
		iRet = recvfrom(sock, buf, 256, 0, (SOCKADDR*)&peer, &iLen);
		buf[iRet] = 0;
		printf("\n[Recv] %s:%d : %s", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port), buf);

		Sleep(1000);
	}
	closesocket(sockSend);
	closesocket(sock);
	WSACleanup();
	return 0;
}
