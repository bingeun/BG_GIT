#include "GameMain.h"

bool GameMain::NetworkInit()
{
	return true;
}

bool GameMain::NetworkFrame()
{
	if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
	{
		m_GameState = STATE_MAIN;
		MainInit();
		return true;
	}
	if (m_Input.KeyCheck(VK_RETURN) == KEY_PUSH)
	{
	}
	return true;
}

bool GameMain::NetworkRender()
{
	return true;
}

bool GameMain::NetworkExit()
{
	return true;
}
