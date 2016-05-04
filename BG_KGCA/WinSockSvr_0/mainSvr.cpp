#include <WinSock2.h>
//#include <Windows.h> // windows.h 는 반드시 WinSock 아래에 있어야 한다!
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;
	SOCKET sock;

	//     주소체계,  소켓타입,  프로토콜 지정
	socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // IPPROTO_TCP = 0
											   //socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // IPPROTO_UDP = 0

	SOCKADDR_IN sa; //SOCKADDR sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // Host TO Network Short
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
	int iReturn;

	iReturn = bind(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iReturn == SOCKET_ERROR)
	{
		return;
	}

	iReturn = listen(sock, SOMAXCONN);
	if (iReturn == SOCKET_ERROR)
	{
		return;
	}

	SOCKET client;
	while (true)
	{
		int addlength = sizeof(clientAddr);

		// accept() 블록형 함수
		client = accept(sock, (SOCKADDR*)&clientAddr, &addlength);
		printf("Client Connect! ip = %s, port = %d", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		char szBuffer[MAX_PATH] = { 0 };
		while (true)
		{
			// recv() 블록형 함수
			int iRecvByte = recv(client, szBuffer, sizeof(char)*MAX_PATH, 0);
			if (iRecvByte == SOCKET_ERROR)
			{
				return;
			}
			if (iRecvByte == 0)
			{
				// 클라이언트 나감...
			}
			printf("Message = %s", szBuffer);
		}
	}

	WSACleanup();
}