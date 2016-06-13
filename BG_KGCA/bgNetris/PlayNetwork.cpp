#include "GameMain.h"

bool GameMain::NetworkInit()
{
	srand((unsigned)time(NULL));

	m_fTimeStartGame = g_fAccumulation;

	m_Back.SetBitmap(L"net_back.bmp");
	m_Back.SetSprite(L"NetBack");

	m_Sound.Play(m_arySound[SOUND_BGM_BACK3], true);

	return true;
}

bool GameMain::NetworkFrame()
{
	if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
	{
		m_GameState = GAMESTATE_MAIN;
		m_Sound.Stop();
		NetworkExit();
		MainInit();
		return true;
	}
	return true;
}

bool GameMain::NetworkRender()
{
	m_Back.Render();

#ifdef _DEBUG
	//TCHAR pszBuffer[MAX_PATH] = L"Print Debug String...";
	//DrawDebug(pszBuffer, 2, 2 + 14 * 2);

	DrawDebug(L"Print Debug String...", 2, 2 + 14 * 2);
#endif //_DEBUG
	return true;
}

bool GameMain::NetworkExit()
{
	return true;
}
