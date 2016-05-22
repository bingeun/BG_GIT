#include "bgAsyncSelect.h"

#define NETWORK_MSG		(WM_USER + 80)

bool bgAsyncSelect::Connect(char* ip, int iPort)
{
	int iResult = WSAAsyncSelect(m_Sock, g_hWnd, NETWORK_MSG, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if (iResult == SOCKET_ERROR)
	{
		return false;
	}

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

void bgAsyncSelect::MsgEvent(MSG msg)
{
	switch (msg.message)
	{
	case NETWORK_MSG:
	{
		if (WSAGETSELECTERROR(msg.lParam) != 0)
		{
			MessageBox(g_hWnd, L"접속 종료", L"종료", MB_OK);
			PostQuitMessage(0);
			return;
		}
		WORD dwSelect = WSAGETSELECTEVENT(msg.lParam);
		switch (dwSelect)
		{
		case FD_CONNECT:
		{
			m_bConnect = true;
		}
		break;
		case FD_CLOSE:
		{
			m_bConnect = false;
		}
		break;
		case FD_READ:
		{
			RecvMsg();
		}
		break;
		case FD_WRITE:
		{
			int kkkk = 0;
		}
		break;
		}
	}
	}
}

bgAsyncSelect::bgAsyncSelect()
{
}

bgAsyncSelect::~bgAsyncSelect()
{
}
