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
		// 메세지 큐에서 원시 메세지 1개 가져오기
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 원시 메세지 해석
			DispatchMessage(&msg); // 해석된 메세지를 프로시저에 전달
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
