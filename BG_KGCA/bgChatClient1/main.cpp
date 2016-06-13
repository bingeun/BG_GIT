#include "main.h"

static char* GetWtM(WCHAR* data)
{
	char retData[4096] = { 0 };
	int iLength = WideCharToMultiByte(CP_ACP, 0, data, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0, data, -1, retData, iLength, NULL, NULL);
	return NULL; //retData;
}

static WCHAR* GetMtW(char* data)
{
	WCHAR retData[4096] = { 0 };
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0, data, -1, retData, iLength);
	return NULL; //retData;
}

///////////////////////////////////////////////////////////////////////////////////

bool bgMain::Init()
{
	m_Network.Init();
	if (!m_Network.Connect(SERVER_IP, SERVER_PORT))
	{
		return false;
	}
	return true;
}

LRESULT	bgMain::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TCHAR buffer[MAX_PATH] = L"abc";
	int iSendByte = m_Network.SendMsg(GetWtM(buffer), PACKET_CHAT_MSG);
	if (iSendByte == SOCKET_ERROR)
		return 0;
	return 0;
}

void bgMain::MsgEvent(MSG msg)
{
	m_Network.MsgEvent(msg);
}

bool bgMain::Frame()
{
	if (m_Network.m_RecvList.empty() == false)
	{
		for (std::list<UPACKET>::iterator itor = m_Network.m_RecvList.begin(); itor != m_Network.m_RecvList.end(); itor++)
		{
			UPACKET pPacket = *itor;
			switch (pPacket.ph.type)
			{
			case PACKET_CHAT_MSG:
			{
				SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)GetMtW(pPacket.msg));
			}
			break;
			}
		}
		m_Network.m_RecvList.clear();
	}
	return true;
}

bool bgMain::Release()
{
	m_Network.Release();
	return true;
}

bgMain::bgMain()
{
}

bgMain::~bgMain()
{
}

void main()
{
	bgMain win;
	win.Run();
}
