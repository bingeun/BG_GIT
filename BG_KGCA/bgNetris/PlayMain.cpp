#include "GameMain.h"

bool GameMain::MainInit()
{
	m_Back.SetBitmap(L"main.bmp");
	m_Back.SetSprite(L"Main");

	m_Sound.Play(m_arySound[SOUND_BGM_MAIN], true);

	return true;
}

bool GameMain::MainFrame()
{
	if (m_bActivate == true)
	{
		// ESC - ���α׷� ����
		if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
		{
			m_GameState = GAMESTATE_EXIT;
			return true;
		}
		// Enter - Ŭ���̾�Ʈ ��� ����
		if (m_Input.KeyCheck(VK_RETURN) == KEY_PUSH)
		{
			m_GameState = GAMESTATE_NETWORK_CLIENT;
			m_Sound.Stop();
			ClientInit();
			return true;
		}
		// F1 - ���� ��� ����
		if (m_Input.KeyCheck(VK_F1) == KEY_PUSH)
		{
			m_GameState = GAMESTATE_NETWORK_SERVER;
			m_Sound.Stop();
			ServerInit();
			return true;
		}
	}
	return true;
}

bool GameMain::MainRender()
{
	m_Back.Render();
	return true;
}

bool GameMain::MainExit()
{
	return true;
}
