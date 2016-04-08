#include "bgWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	bgWindow win;
	if (win.SetWindow(hInstance) == true)
	{
		Run();
	}
	return 0;
}