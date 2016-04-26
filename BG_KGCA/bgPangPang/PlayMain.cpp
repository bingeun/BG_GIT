#include "GameMain.h"

bool GameMain::MainInit()
{
	m_Ground.SetBitmap(L"main.bmp");
	m_Ground.SetSprite(L"Main");

	return true;
}

bool GameMain::MainFrame()
{
	if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
	{
		m_GameState = STATE_EXIT;
		return true;
	}
	if (m_Input.KeyCheck(VK_RETURN) == KEY_PUSH)
	{
		m_GameState = STATE_SINGLE;
		SingleInit();
		return true;
	}
	return true;
}

bool GameMain::MainRender()
{
	m_Ground.Render();
	return true;
}

bool GameMain::MainExit()
{
	return true;
}
