#include "TWindow.h"

bool GameInit()
{
	return true;
}

bool GameRelease()
{
	return true;
}

bool GameRun()
{
	return true;
}

bool Run()
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	TWindow win;
	if (win.SetWindow(hInstance) == true)
	{
		Run();
	}
	return 0;
}