#include "bgCore.h"


bool bgCore::Init()
{
	return true;
}

bool bgCore::Frame()
{
	return true;
}

bool bgCore::PreRender()
{
	return true;
}

bool bgCore::Render()
{
	return true;
}

bool bgCore::PostRender()
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
	PreRender();
	Render();

	// 정보 출력
	m_Timer.Render();
	m_Input.Render();
	DebugString();

	PostRender();

	return true;
}

bool bgCore::GameRelease()
{
	m_Timer.Release();
	m_Input.Release();
	Release();
	return true;
}

void bgCore::DebugString()
{
#ifdef _DEBUG
	TCHAR str[MAX_PATH] = { 0, };
	_stprintf_s(str, L"%d, %d\n", 800, 600);
	OutputDebugString(str);
#endif // _DEBUG
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
