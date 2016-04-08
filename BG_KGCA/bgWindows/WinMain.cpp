#include "bgWindow.h"

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
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
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
	bgWindow win;
	if (win.SetWindow(hInstance) == true)
	{
		Run();
	}
	return 0;
}