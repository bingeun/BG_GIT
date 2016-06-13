#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define TIME_SLEEP	(3000)
#define BUF_SIZE	(1024)
#define SERVER_PORT	"10000"

DWORD g_iCountPerSecond = 0;
DWORD g_iBytePerSecond = 0;

DWORD WINAPI PrintMonitoring(LPVOID arg)
{
	while (true)
	{
		printf("패킷 횟수 : %d 회, 패킷 바이트수 : %d Bytes (갱신 : %dms)\n", g_iCountPerSecond, g_iBytePerSecond, TIME_SLEEP);
		InterlockedExchange(&g_iCountPerSecond, 0);
		InterlockedExchange(&g_iBytePerSecond, 0);
		Sleep(TIME_SLEEP);
	}
}

void ErrorHandling(char* szMsg)
{
	fputs(szMsg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	WSADATA		wsaData;
	SOCKET		sockServer, sockClient;
	SOCKADDR_IN	addrServer, addrClient;
	TIMEVAL		timeout;
	fd_set		fdReads, fdReadsCopy;

	int iSizeAddr;
	int iStringLen;
	int ifdNumber;
	char szBuf[BUF_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addrServer, 0, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	addrServer.sin_port = htons(atoi(SERVER_PORT));

	if (bind(sockServer, (SOCKADDR*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
		ErrorHandling("bind() error!");

	if (listen(sockServer, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error!");

	FD_ZERO(&fdReads);
	FD_SET(sockServer, &fdReads);

	DWORD dwPrintThreadID;
	CloseHandle(CreateThread(0, 0, PrintMonitoring, (LPVOID)0, 0, &dwPrintThreadID));

	int i, j;
	while (true)
	{
		fdReadsCopy = fdReads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		ifdNumber = select(0, &fdReadsCopy, 0, 0, &timeout);
		if (ifdNumber == SOCKET_ERROR)
			break;
		if (ifdNumber == 0)
			continue;

		for (i = 0; i < (int)(fdReads.fd_count); i++)
		{
			if (FD_ISSET(fdReads.fd_array[i], &fdReadsCopy))
			{
				// 클라이언트 접속
				if (fdReadsCopy.fd_array[i] == sockServer)
				{
					iSizeAddr = sizeof(addrClient);
					sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &iSizeAddr);
					FD_SET(sockClient, &fdReads);

					printf("[클라이언트 접속!] >> IP : %s, PORT : %d\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));
				}
				else
				{
					iStringLen = recv(fdReads.fd_array[i], szBuf, BUF_SIZE - 1, 0);
					if (iStringLen == 0)
					{
						FD_CLR(fdReads.fd_array[i], &fdReads);
						closesocket(fdReadsCopy.fd_array[i]);
						printf("[클라이언트 접속 종료!] >> %d\n", fdReadsCopy.fd_array[i]);
					}
					else
					{
						// 각각의 클라이언트들에 전송 (Broadcast)
						for (j = 0; j < (int)(fdReads.fd_count); j++)
						{
							int iSendByte = send(fdReads.fd_array[j], szBuf, iStringLen, 0);
							if (iSendByte != -1)
							{
								InterlockedIncrement(&g_iCountPerSecond);
								InterlockedExchange(&g_iBytePerSecond, g_iBytePerSecond += iSendByte);
							}
						} // for (Broadcast)
					}
				}
			} // if (FD_ISSET())
		}
	} // while (true)

	closesocket(sockServer);
	WSACleanup();

	return 0;
}