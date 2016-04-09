#include "bgCore.h"


bool bgCore::Init()
{
	return true;
}

bool bgCore::Frame()
{
	return true;
}

bool bgCore::Render()
{
	return true;
}

bool bgCore::Release()
{
	return true;
}

bool bgCore::GameInit()
{
	m_Timer.Init();
	m_Input.Init();

	Init();
	return true;
}

bool bgCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}

bool bgCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();

	Frame();
	return true;
}

bool bgCore::GameRender()
{
	m_Timer.Render();
	m_Input.Render();

	Render();
	return true;
}

bool bgCore::GameRelease()
{
	m_Timer.Release();
	m_Input.Release();

	Release();
	return true;
}

void bgCore::MsgEvent(MSG msg)
{

}

bool bgCore::Run()
{
	GameInit();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// �޼��� ť���� ���� �޼��� 1�� ��������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // ���� �޼��� �ؼ�
			DispatchMessage(&msg); // �ؼ��� �޼����� ���ν����� ����
			MsgEvent(msg);
		}
		else
		{
			GameRun();
		}
	}
	GameRelease();

	return true;
}

bgCore::bgCore()
{
}


bgCore::~bgCore()
{
}
