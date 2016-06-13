#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE	(256)

UINT WINAPI FuncSend(void *arg)
{
	SOCKET sock = (SOCKET)arg;
	char szBuf[BUF_SIZE] = { 0, };
	while (true)
	{
		ZeroMemory(szBuf, sizeof(char)*BUF_SIZE);
		fgets(szBuf, BUF_SIZE, stdin);

		if (!strcmp(szBuf, "q\n") || !strcmp(szBuf, "Q\n"))
			break;

		if (szBuf[strlen(szBuf) - 1] == '\n')
			szBuf[strlen(szBuf) - 1] = 0;
		if (strlen(szBuf) == 0)
			break;

		int iSendByte = send(sock, szBuf, strlen(szBuf), 0);
		if (iSendByte == SOCKET_ERROR)
			break;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("\n[사용방법] xxx.exe [port] [ip]");
		printf("\n[사용예시] xxx.exe 10000 127.0.0.1");
		return 1;
	}

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 1;

	unsigned short iPort = atoi(argv[1]);
	char* szIP = argv[2];
	HANDLE hThread;
	int iReturn;

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSock;
	ZeroMemory(&addrSock, sizeof(addrSock));
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(iPort);
	addrSock.sin_addr.s_addr = inet_addr(szIP);
	iReturn = connect(sock, (SOCKADDR*)&addrSock, sizeof(addrSock));
	if (iReturn == SOCKET_ERROR)
		return 1;

	DWORD dwRecvThreadID;
	printf("서버에 접속하였습니다. (Q = 접속종료)\n");
	printf("[전송메세지] >> ");

	hThread = (HANDLE)_beginthreadex(0, 0, FuncSend, (void*)sock, 0, (unsigned int*)&dwRecvThreadID);
	char szBuf[BUF_SIZE] = { 0, };
	while (true)
	{
		memset(szBuf, 0, sizeof(char) * BUF_SIZE);
		int iLength = 0;
		int iRecvByte = recv(sock, szBuf, BUF_SIZE, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
		{
			printf("서버와의 접속이 종료되었습니다.\n");
			break;
		}
		szBuf[iRecvByte] = '\0';
		printf("\n%s\n", szBuf);
		printf("[전송메세지] >> ");
	}

	closesocket(sock);
	iReturn = WSACleanup();

	return iReturn;
}
