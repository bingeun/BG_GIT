#include "Sample.h"



bool Sample::Init()
{

	return false;
}

bool Sample::Frame()
{
	return false;
}

bool Sample::Render()
{
	return false;
}

bool Sample::Release()
{
	return false;
}

int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	Sample win;
	//win.SetRect(1024, 768);
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}

Sample::Sample()
{
}


Sample::~Sample()
{
}
