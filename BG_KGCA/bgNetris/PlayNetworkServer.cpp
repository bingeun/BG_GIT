#include "GameMain.h"
#include "bgGameServer.h"
#include "bgServerIOCP.h"
#include "bgDebugString.h"

bool GameMain::ServerInit()
{
	m_Back.SetBitmap(L"net_back.bmp");
	m_Back.SetSprite(L"NetBack");
	m_UI.SetBitmap(L"ui.bmp");
	m_UI.SetSprite(L"UIServer");

	m_Sound.Play(m_arySound[SOUND_BGM_BACK3], true);

	m_PlayState = PLAYSTATE_WAIT;
	I_ServerIOCP.Init();
	I_Server.Init();
	m_Udp.Init();

	return true;
}

bool GameMain::ServerFrame()
{
	int i;
	switch (m_PlayState)
	{
	case PLAYSTATE_PLAY: //////////////////////////////// ��Ƽ�÷��� ������!
	{
		if (m_bActivate == true)
		{
			if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
			{
				m_PlayState = PLAYSTATE_GAMEOVER;
			}
			if (m_Input.IsKeyHoldRepeat(VK_LEFT) || m_Input.KeyCheck(VK_LEFT) == KEY_PUSH)
			{
				if (!m_NetrisClnt.m_Netris[0].CollideTetromino(m_NetrisClnt.m_Netris[0].m_iX - 1, m_NetrisClnt.m_Netris[0].m_iY, m_NetrisClnt.m_Netris[0].m_iBlock, m_NetrisClnt.m_Netris[0].m_iRotate))
					m_NetrisClnt.m_Netris[0].SetMoveAdd(-1, 0);
			}
			if (m_Input.IsKeyHoldRepeat(VK_RIGHT) || m_Input.KeyCheck(VK_RIGHT) == KEY_PUSH)
			{
				if (!m_NetrisClnt.m_Netris[0].CollideTetromino(m_NetrisClnt.m_Netris[0].m_iX + 1, m_NetrisClnt.m_Netris[0].m_iY, m_NetrisClnt.m_Netris[0].m_iBlock, m_NetrisClnt.m_Netris[0].m_iRotate))
					m_NetrisClnt.m_Netris[0].SetMoveAdd(1, 0);
			}
			if (m_Input.IsKeyHoldRepeat(VK_UP) || m_Input.KeyCheck(VK_UP) == KEY_PUSH)
			{
				if (!m_NetrisClnt.m_Netris[0].CollideTetromino(m_NetrisClnt.m_Netris[0].m_iX, m_NetrisClnt.m_Netris[0].m_iY, m_NetrisClnt.m_Netris[0].m_iBlock, m_NetrisClnt.m_Netris[0].m_iRotate + 1))
					m_NetrisClnt.m_Netris[0].SetRotateAdd(1);
			}
			if (m_Input.IsKeyHoldRepeat(VK_DOWN) || m_Input.KeyCheck(VK_DOWN) == KEY_PUSH)
			{
				if (!m_NetrisClnt.m_Netris[0].CollideTetromino(m_NetrisClnt.m_Netris[0].m_iX, m_NetrisClnt.m_Netris[0].m_iY + 1, m_NetrisClnt.m_Netris[0].m_iBlock, m_NetrisClnt.m_Netris[0].m_iRotate))
					m_NetrisClnt.m_Netris[0].SetMoveAdd(0, 1);
			}
			if (m_Input.IsKeyHoldRepeat(VK_SPACE) || m_Input.KeyCheck(VK_SPACE) == KEY_PUSH)
			{
				while (!m_NetrisClnt.m_Netris[0].CollideTetromino(m_NetrisClnt.m_Netris[0].m_iX, m_NetrisClnt.m_Netris[0].m_iY + 1, m_NetrisClnt.m_Netris[0].m_iBlock, m_NetrisClnt.m_Netris[0].m_iRotate))
					m_NetrisClnt.m_Netris[0].SetMoveAdd(0, 1);
				m_NetrisClnt.m_Netris[0].m_fTimeBlockDown = g_fAccumulation - m_NetrisClnt.m_Netris[0].m_fTermBlockDown;
			}
		}

		m_Back.Frame();
		m_UI.Frame();

		//for (i = 0; i < MAX_PLAYER; i++)
		{
			i = 0;
			if (g_fAccumulation - m_NetrisClnt.m_Netris[i].m_fTimeBlockDown >= m_NetrisClnt.m_Netris[i].m_fTermBlockDown)
			{
				// �Ʒ� ���� ������...
				if (m_NetrisClnt.m_Netris[i].CollideTetromino(m_NetrisClnt.m_Netris[i].m_iX, m_NetrisClnt.m_Netris[i].m_iY + 1, m_NetrisClnt.m_Netris[i].m_iBlock, m_NetrisClnt.m_Netris[i].m_iRotate))
				{
					m_NetrisClnt.m_Netris[i].SaveTetromino(m_NetrisClnt.m_Netris[i].m_iX, m_NetrisClnt.m_Netris[i].m_iY, m_NetrisClnt.m_Netris[i].m_iBlock, m_NetrisClnt.m_Netris[i].m_iRotate);
					m_NetrisClnt.m_Netris[i].DelLine();
					m_NetrisClnt.m_Netris[i].SetBlockNext();
				}
				// �Ʒ� ���� ������...
				else
				{
					m_NetrisClnt.m_Netris[i].SetMoveAdd(0, 1);
				}
				m_NetrisClnt.m_Netris[i].m_fTimeBlockDown = g_fAccumulation;
			}

			m_NetrisClnt.m_Netris[i].Frame();
		}
	}
	break;
	case PLAYSTATE_TRAIN: ////////////////////////////////////// ȥ�ڿ�����!
	{

	}
	break;
	case PLAYSTATE_WAIT: ////////////////////////////////////// ���ӽ��� �����~
	{
		if (m_bActivate == true)
		{
			if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
			{
				m_GameState = GAMESTATE_MAIN;
				m_PlayState = PLAYSTATE_GAMEOVER;
				m_Sound.Stop();
				ClientExit();
				MainInit();
				return true;
			}
			if (m_Input.KeyCheck(VK_F1) == KEY_PUSH)
			{
				m_PlayState = PLAYSTATE_PLAY;
				for (int i = 0; i < MAX_PLAYER; i++)
				{
					m_NetrisClnt.m_Netris[i].SetPlayerID(0, i);
					m_NetrisClnt.m_Netris[i].Init();
				}

				for (int i = 0; i < MAX_PLAYER; i++)
				{
					TPACKET_PLAYER_INFO userdata;
					userdata.iID = i;
					userdata.iCMD = PLAYER_INFO_CMD_INIT;
					userdata.iValue = 0;
					userdata.iX = m_NetrisClnt.m_Netris[i].m_iX;
					userdata.iY = m_NetrisClnt.m_Netris[i].m_iY;
					userdata.iBlock = m_NetrisClnt.m_Netris[i].m_iBlock;
					userdata.iRotate = m_NetrisClnt.m_Netris[i].m_iRotate;

					char buffer[256] = { 0, };
					int iSize = sizeof(userdata);
					memcpy(buffer, &userdata, iSize);
					m_NetrisClnt.SendMsg(buffer, iSize, PACKET_PLAYER_INFO);
				}
				return true;
			}
			if (m_Input.KeyCheck(VK_F2) == KEY_PUSH)
			{
				m_PlayState = PLAYSTATE_PLAY;
				for (int i = 0; i < MAX_PLAYER; i++)
				{
					m_NetrisClnt.m_Netris[i].SetPlayerID(0, i);
					m_NetrisClnt.m_Netris[i].Init();
				}
				return true;
			}
		}
	}
	break;
	case PLAYSTATE_GAMEOVER: /////////////////////////////////// ���ӿ���~!
	{
		m_PlayState = PLAYSTATE_WAIT;
	}
	break;
	}

	return true;
}

bool GameMain::ServerRender()
{
	int i;
	switch (m_PlayState)
	{
	case PLAYSTATE_PLAY: //////////////////////////////// ��Ƽ�÷��� ������!
	{
		m_Back.Render();
		m_UI.Render();

		for (i = 0; i < MAX_PLAYER; i++)
			m_NetrisClnt.m_Netris[i].Render();
	}
	break;
	case PLAYSTATE_TRAIN: ////////////////////////////////////// ȥ�ڿ�����!
	{

	}
	break;
	case PLAYSTATE_WAIT: ////////////////////////////////////// ���ӽ��� �����~
	{
		m_Back.Render();
		m_UI.Render();

		//for (i = 0; i < MAX_PLAYER; i++)
		//	m_NetrisClnt.m_Netris[i].Render();
	}
	break;
	case PLAYSTATE_GAMEOVER: /////////////////////////////////// ���ӿ���~!
	{

	}
	break;
	}

	return true;
}

bool GameMain::ServerExit()
{
	m_Udp.Release();
	I_Server.Release();
	I_ServerIOCP.Release();
	return true;
}
