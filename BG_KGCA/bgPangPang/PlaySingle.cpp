#include "GameMain.h"


void GameMain::CreateBullet(BULLET_TYPE iType, float fX, float fY)
{
	switch (iType)
	{
	case BULLET_SINGLE:
		if (m_CountBullet < 1)
		{
			objBullet* pBullet = new objBullet;
			pBullet->Init();
			pBullet->SetSprite(L"BulletSingle");
			pBullet->m_BulletType = BULLET_SINGLE;
			pBullet->m_fPosYHead = fY;
			pBullet->SetObject(fX + BLOCK_W, fY, 0.0f);
			m_Bullet.push_back(*pBullet);

			m_CountBullet++;
		}
		break;

	case BULLET_DOUBLE:
		if (m_CountBullet < 2)
		{
			objBullet* pBullet = new objBullet;
			pBullet->Init();
			pBullet->SetSprite(L"BulletDouble");
			pBullet->m_BulletType = BULLET_DOUBLE;
			pBullet->m_fPosYHead = fY;
			pBullet->SetObject(fX + BLOCK_W, fY, 0.0f);
			m_Bullet.push_back(*pBullet);

			m_CountBullet++;
		}
		break;

	case BULLET_FIXED:
		if (m_CountBullet < 1)
		{
			objBullet* pBullet = new objBullet;
			pBullet->Init();
			pBullet->SetSprite(L"BulletFixed");
			pBullet->m_BulletType = BULLET_FIXED;
			pBullet->m_fPosYHead = fY;
			pBullet->SetObject(fX + BLOCK_W, fY, 0.0f);
			m_Bullet.push_back(*pBullet);

			m_CountBullet++;
		}
		break;

	case BULLET_GUN:
		if (m_CountBullet < 30) // 1회 발사에 3개씩 총 10회 발사 가능
		{
			objBullet* pBullet = new objBullet;
			pBullet->Init();
			pBullet->SetSprite(L"BulletGun");
			pBullet->m_BulletType = BULLET_GUN;
			pBullet->m_fPosYHead = fY;
			pBullet->SetObject(fX + BLOCK_W, fY, 0.0f);
			m_Bullet.push_back(*pBullet);

			objBullet* pBulletLeft = new objBullet;
			pBulletLeft->Init();
			pBulletLeft->SetSprite(L"BulletGunLeft");
			pBulletLeft->m_BulletType = BULLET_GUN_LEFT;
			pBulletLeft->m_fPosYHead = fY;
			pBulletLeft->SetObject(fX, fY, 0.0f);
			m_Bullet.push_back(*pBulletLeft);

			objBullet* pBulletRight = new objBullet;
			pBulletRight->Init();
			pBulletRight->SetSprite(L"BulletGunRight");
			pBulletRight->m_BulletType = BULLET_GUN_RIGHT;
			pBulletRight->m_fPosYHead = fY;
			pBulletRight->SetObject(fX + (BLOCK_W * 2), fY, 0.0f);
			m_Bullet.push_back(*pBulletRight);

			m_CountBullet += 3;
		}
		break;

	//case BULLET_GUN_LEFT:
	//	if (m_CountBullet < 30) // 1회 발사에 3개씩 총 10회 발사 가능
	//	{
	//		objBullet* pBulletLeft = new objBullet;
	//		pBulletLeft->Init();
	//		pBulletLeft->SetSprite(L"BulletGunLeft");
	//		pBulletLeft->m_BulletType = BULLET_GUN_LEFT;
	//		pBulletLeft->SetObject(fX, fY, 0.0f);
	//		m_Bullet.push_back(*pBulletLeft);

	//		m_CountBullet++;
	//	}
	//	break;

	//case BULLET_GUN_RIGHT:
	//	if (m_CountBullet < 30) // 1회 발사에 3개씩 총 10회 발사 가능
	//	{
	//		objBullet* pBulletRight = new objBullet;
	//		pBulletRight->Init();
	//		pBulletRight->SetSprite(L"BulletGunRight");
	//		pBulletRight->m_BulletType = BULLET_GUN_RIGHT;
	//		pBulletRight->SetObject(fX + (BLOCK_W * 2), fY, 0.0f);
	//		m_Bullet.push_back(*pBulletRight);

	//		m_CountBullet++;
	//	}
	//	break;
	}
}

bool GameMain::SingleInit()
{
	m_Ground.SetBitmap(L"back1.bmp");
	m_Ground.SetSprite(L"Back1");

	m_Hero.SetBitmap(L"hero.bmp");
	m_Hero.SetSprite(L"HeroIdle");
	m_Hero.SetObject(BOARD_X + (BOARD_W*BLOCK_W - 45) / 2, BOARD_Y + (BOARD_H*BLOCK_H - 60), HERO_SPEED);

	m_iterBullet = m_Bullet.begin();
	m_Bullet.clear();
	m_BulletType = BULLET_GUN;
	m_CountBullet = 0;

	return true;
}

bool GameMain::SingleFrame()
{
	// 키입력 - ESC - 메인씬으로 이동
	if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
	{
		m_GameState = STATE_MAIN;
		MainInit();
		return true;
	}
	// 키입력 - Left - 주인공 왼쪽으로 이동
	switch (m_Input.KeyCheck(VK_LEFT))
	{
	case KEY_PUSH:
		m_Hero.SetSprite(L"HeroMove");
		break;
	case KEY_UP:
		if (m_Input.KeyCheck(VK_RIGHT) == KEY_HOLD)
			m_Hero.SetSprite(L"HeroMoveRight");
		else
			m_Hero.SetSprite(L"HeroIdle");
		break;
	case KEY_HOLD:
		m_Hero.Left();
		break;
	}
	// 키입력 - Right - 주인공 오른쪽으로 이동
	switch (m_Input.KeyCheck(VK_RIGHT))
	{
	case KEY_PUSH:
		m_Hero.SetSprite(L"HeroMoveRight");
		break;
	case KEY_UP:
		if (m_Input.KeyCheck(VK_LEFT) == KEY_HOLD)
			m_Hero.SetSprite(L"HeroMove");
		else
			m_Hero.SetSprite(L"HeroIdleRight");
		break;
	case KEY_HOLD:
		m_Hero.Right();
		break;
	}
	// 키입력 - 좌측 Ctrl - 무기 발사
	if (m_Input.KeyCheck(VK_LCONTROL) == KEY_PUSH)
	{
		CreateBullet(m_BulletType, (float)m_Hero.m_posObject.x, (float)m_Hero.m_posObject.y);
	}
	// 키입력 - Up
	if (m_Input.KeyCheck(VK_UP) == KEY_HOLD)
	{
		m_Hero.SpeedUp();
	}
	// 키입력 - Down
	if (m_Input.KeyCheck(VK_DOWN) == KEY_HOLD)
	{
		m_Hero.SpeedDown();
	}

	m_Ground.Frame();
	for (m_iterBullet = m_Bullet.begin(); m_iterBullet != m_Bullet.end(); m_iterBullet++)
	{
		m_iterBullet->Frame();
	}
	m_Hero.Frame();


	return true;
}

bool GameMain::SingleRender()
{
	m_Ground.Render();
	for (m_iterBullet = m_Bullet.begin(); m_iterBullet != m_Bullet.end(); m_iterBullet++)
	{
		m_iterBullet->Render();
	}
	m_Hero.Render();

#ifdef _DEBUG
	//TCHAR pszBuffer[MAX_PATH] = L"Print Debug String...";
	//DrawDebug(pszBuffer, 2, 2 + 14 * 2);

	DrawDebug(L"Print Debug String...", 2, 2 + 14 * 2);
#endif //_DEBUG
	return true;
}

bool GameMain::SingleExit()
{
	return true;
}
