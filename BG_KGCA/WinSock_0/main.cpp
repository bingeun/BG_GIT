#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("\n[�����] xxx.exe [port] [ip]");
		printf("\n[��뿹��] xxx.exe 10000 192.168.0.100");
		return 1;
	}
	unsigned short iPort = atoi(argv[1]);
	char* ip = argv[2];
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return 1; }
	{
		SOCKET sock;
		sock = socket(AF_INET, SOCK_STREAM, 0);
		{
			SOCKADDR_IN sa;//sockaddr name;
			ZeroMemory(&sa, sizeof(sa));
			sa.sin_family = AF_INET;
			sa.sin_port = htons(iPort);// host byte ���� to network byte ���� short
			sa.sin_addr.s_addr = inet_addr(ip);
			iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
			if (iRet == SOCKET_ERROR) { return 1; }
			{
				char buf[256] = { 0, };
				int iLen = 0;
				while (1)
				{
					ZeroMemory(buf, sizeof(char) * 256);
					printf("\n ���� ������ �Է��Ͻÿ�?");
					fgets(buf, 256, stdin);
					if (buf[strlen(buf) - 1] == '\n')
						buf[strlen(buf) - 1] = 0;
					if (strlen(buf) == 0) break; // ���ʹ� ����!
					int iSendByte = send(sock, buf, strlen(buf), 0);
					printf("%d ����Ʈ�� �����Ͽ����ϴ�.", iSendByte);

					memset(buf, 0, sizeof(char) & 256);
					int iLen = 0;
					int iRecvByte = recv(sock, buf, 256, 0);
					if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
					{
						printf("���� ����");
					}
					buf[iRecvByte] = '\n';
					printf("\n%s", buf);
				}
			}
		}
		closesocket(sock);
	}
	// ������ ���� �Ҹ�
	iRet = WSACleanup();
	return iRet;
}