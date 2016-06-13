#include "GameMain.h"

bool GameMain::SingleInit()
{
	m_fTimeStartGame = g_fAccumulation;
	return true;
}

bool GameMain::SingleFrame()
{
	return true;
}

bool GameMain::SingleRender()
{
	return true;
}

bool GameMain::SingleExit()
{
	return true;
}
