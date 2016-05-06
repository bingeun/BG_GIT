#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <list>
#pragma comment(lib, "ws2_32.lib")

//EnterCriticalSection()
//..........
//LeaveCriticalSection()
//멀티스레딩시 한블럭의 처리를 강제하여 보호(전역변수 사용시...)

struct bgUser
{
	SOCKET sock;
	SOCKADDR_IN clientaddr;
};

std::list<bgUser*> users;
std::list<bgUser*>::iterator iter;

DWORD WINAPI ClientThread(LPVOID arg)
{
	bgUser* user = (bgUser*)arg;
	SOCKADDR_IN  clientaddr = user->clientaddr;
	SOCKET sock = user->sock;
	char buf[256] = { 0, };

	while (1)
	{
		ZeroMemory(&buf, sizeof(char) * 256);
		int iRecvByte = recv(sock, buf, 256, 0);
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("[소켓 오류] IP:%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			break;
		}
		if (iRecvByte == 0)
		{
			printf("[클라이언트 종료] IP:%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			break;
		}
		buf[iRecvByte] = 0;
		printf("%s:%hu > %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);
		for (iter = users.begin(); iter != users.end(); iter++)
		{
			bgUser* sendUser = (bgUser*)*iter;
			int iSendByte = send(sendUser->sock, buf,strlen(buf), 0);
			if (iSendByte == SOCKET_ERROR)
			{
				printf("[소켓 오류] IP:%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				break;
			}
			if (iSendByte == 0)
			{
				printf("[클라이언트 종료] IP:%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				break;
			}
		}
	}
	closesocket(sock);

	for (iter = users.begin(); iter != users.end(); iter++)
	{
		bgUser* delUser = (bgUser*)*iter;
		if (delUser->sock == user->sock)
		{
			closesocket(delUser->sock);
			delete delUser;
			users.erase(iter);
			break;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	unsigned short iPort = atoi(argv[1]);
	WSADATA wsa;
	int iRet;
	HANDLE hThread;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}
	else
	{
		SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
		{
			SOCKADDR_IN sa;
			ZeroMemory(&sa, sizeof(sa));
			sa.sin_family = AF_INET;
			sa.sin_port = htons(iPort);
			sa.sin_addr.s_addr = htonl(INADDR_ANY);
			iRet = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));
			if (iRet == SOCKET_ERROR)
				return -1;
			iRet = listen(listenSock, SOMAXCONN);
			if (iRet == SOCKET_ERROR)
				return -1;
			SOCKADDR_IN  clientaddr;
			SOCKET client;
			printf("<<<<<<<<<< 서버를 시작하였습니다 >>>>>>>>>>\n");
			while (1)
			{
				int addlen = sizeof(clientaddr);
				client = accept(listenSock, (SOCKADDR*)&clientaddr, &addlen);
				printf("[클라이언트 접속] IP:%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				bgUser* user = new bgUser;
				user->sock = client;
				user->clientaddr = clientaddr;
				users.push_back(user);
				DWORD dwRecvThreadID;
				hThread = CreateThread(0, 0, ClientThread, (LPVOID)user, 0, &dwRecvThreadID);
			}
		}
		closesocket(listenSock);
	}
	iRet = WSACleanup();
	users.clear();
	return iRet;
}
