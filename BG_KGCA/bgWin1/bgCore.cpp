#include "bgCore.h"


bool bgCore::GameInit()
{
	return true;
}

bool bgCore::GameFrame()
{
	return true;
}

bool bgCore::GameRender()
{
	return true;
}

bool bgCore::GameRelease()
{
	return true;
}

bool bgCore::GameRun()
{
	return true;
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
