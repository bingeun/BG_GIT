#include "GameMain.h"


void GameMain::CreateObject(OBJECT_TYPE iType, float fX, float fY, int iSize)
{
	switch (iType)
	{
	case OBJECT_BALL:
		if (m_CountObject < MAX_OBJECT)
		{
			// ����ִ� ������Ʈ(��, �ٰ���, ���) �迭��ġ ã��
			int iEmpty;
			for (iEmpty = 0; iEmpty < MAX_OBJECT; iEmpty++)
			{
				if (!m_Object[iEmpty].m_bLife)
				{
					m_Object[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� ������Ʈ Ȱ��ȭ
			switch (iSize)
			{
			case 1:
				m_Object[iEmpty].SetSprite(L"Ball1");
				break;
			case 2:
				m_Object[iEmpty].SetSprite(L"Ball2");
				break;
			case 3:
				m_Object[iEmpty].SetSprite(L"Ball3");
				break;
			case 4:
				m_Object[iEmpty].SetSprite(L"Ball4");
				break;
			case 5:
				m_Object[iEmpty].SetSprite(L"Ball5");
				break;
			}
			m_Object[iEmpty].m_iObjectSize = iSize;
			m_Object[iEmpty].m_ObjectType = OBJECT_BALL;
			m_Object[iEmpty].SetObject(fX, fY, OBJECT_SPEED);

			// m_fPosA = X����ӵ�, m_fPosB = Y����ӵ�
			// (��ȣ ? - : + ) ���ϱ� (�⺻�ӵ� + �����ӵ�);
			m_Object[iEmpty].m_fPosA = ((rand() % 2) ? -1 : 1) * (OBJECT_SPEED + (rand() % 100));
			m_Object[iEmpty].m_fPosB = -1.0f * abs(OBJECT_SPEED + (rand() % 100));

			m_CountObject++;
		}
		break;

	case OBJECT_POLYGON:
		if (m_CountObject < MAX_OBJECT)
		{
			// ����ִ� ������Ʈ(��, �ٰ���, ���) �迭��ġ ã��
			int iEmpty;
			for (iEmpty = 0; iEmpty < MAX_OBJECT; iEmpty++)
			{
				if (!m_Object[iEmpty].m_bLife)
				{
					m_Object[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� ������Ʈ Ȱ��ȭ
			switch (iSize)
			{
			case 1:
				m_Object[iEmpty].SetSprite(L"Polygon1");
				break;
			case 2:
				m_Object[iEmpty].SetSprite(L"Polygon2");
				break;
			case 3:
				m_Object[iEmpty].SetSprite(L"Polygon3");
				break;
			case 4:
				m_Object[iEmpty].SetSprite(L"Polygon4");
				break;
			case 5:
				m_Object[iEmpty].SetSprite(L"Polygon5");
				break;
			}
			m_Object[iEmpty].m_iObjectSize = iSize;
			m_Object[iEmpty].m_ObjectType = OBJECT_POLYGON;
			m_Object[iEmpty].SetObject(fX, fY, OBJECT_SPEED);

			// m_fPosA = X����ӵ�, m_fPosB = Y����ӵ�
			// (��ȣ ? - : + ) ���ϱ� (�⺻�ӵ� + �����ӵ�);
			m_Object[iEmpty].m_fPosA = ((rand() % 2) ? -1 : 1) * (OBJECT_SPEED + (rand() % 100));
			m_Object[iEmpty].m_fPosB = -1.0f * abs(OBJECT_SPEED + (rand() % 100));

			m_CountObject++;
		}
		break;

	case OBJECT_BLOCK:
		break;
	}
}

void GameMain::CreateBullet(BULLET_TYPE iType, float fX, float fY)
{
	switch (iType)
	{
	case BULLET_SINGLE:
		if (m_CountBullet < 1)
		{
			// ����ִ� �Ѿ� ������Ʈ �迭��ġ ã��
			int iEmpty;
			for (iEmpty = 0; iEmpty < MAX_BULLET; iEmpty++)
			{
				if (!m_Bullet[iEmpty].m_bLife)
				{
					m_Bullet[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� �Ѿ� Ȱ��ȭ
			m_Bullet[iEmpty].SetSprite(L"BulletSingle");
			m_Bullet[iEmpty].m_BulletType = BULLET_SINGLE;
			m_Bullet[iEmpty].m_fPosYHead = fY;
			m_Bullet[iEmpty].m_fShotTime = g_fAccumulation;
			m_Bullet[iEmpty].SetObject(fX + BLOCK_W, fY, 0.0f);

			m_CountBullet++;
		}
		break;

	case BULLET_DOUBLE:
		if (m_CountBullet < 2)
		{
			// ����ִ� �Ѿ� ������Ʈ �迭��ġ ã��
			int iEmpty;
			for (iEmpty = 0; iEmpty < MAX_BULLET; iEmpty++)
			{
				if (!m_Bullet[iEmpty].m_bLife)
				{
					m_Bullet[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� �Ѿ� Ȱ��ȭ
			m_Bullet[iEmpty].SetSprite(L"BulletDouble");
			m_Bullet[iEmpty].m_BulletType = BULLET_DOUBLE;
			m_Bullet[iEmpty].m_fPosYHead = fY;
			m_Bullet[iEmpty].m_fShotTime = g_fAccumulation;
			m_Bullet[iEmpty].SetObject(fX + BLOCK_W, fY, 0.0f);

			m_CountBullet++;
		}
		break;

	case BULLET_FIXED:
		if (m_CountBullet < 1)
		{
			// ����ִ� �Ѿ� ������Ʈ �迭��ġ ã��
			int iEmpty;
			for (iEmpty = 0; iEmpty < MAX_BULLET; iEmpty++)
			{
				if (!m_Bullet[iEmpty].m_bLife)
				{
					m_Bullet[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� �Ѿ� Ȱ��ȭ
			m_Bullet[iEmpty].SetSprite(L"BulletFixed");
			m_Bullet[iEmpty].m_BulletType = BULLET_FIXED;
			m_Bullet[iEmpty].m_fPosYHead = fY;
			m_Bullet[iEmpty].m_fShotTime = g_fAccumulation;
			m_Bullet[iEmpty].SetObject(fX + BLOCK_W, fY, 0.0f);

			m_CountBullet++;
		}
		break;

	case BULLET_GUN:
		if (m_CountBullet < 3 * (3)) // 1ȸ �߻翡 3���� �� (3)ȸ �߻� ����
		{
			// ����ִ� �Ѿ� ������Ʈ �迭��ġ ã��
			int iEmpty;
			for (iEmpty = 0; iEmpty < MAX_BULLET; iEmpty++)
			{
				if (!m_Bullet[iEmpty].m_bLife)
				{
					m_Bullet[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� �Ѿ� Ȱ��ȭ (��� �Ѿ�)
			m_Bullet[iEmpty].SetSprite(L"BulletGun");
			m_Bullet[iEmpty].m_BulletType = BULLET_GUN;
			m_Bullet[iEmpty].m_fPosYHead = fY;
			m_Bullet[iEmpty].m_fShotTime = g_fAccumulation;
			m_Bullet[iEmpty].SetObject(fX + BLOCK_W, fY, 0.0f);

			// ����ִ� �Ѿ� ������Ʈ �迭��ġ ã��
			for (iEmpty = 0; iEmpty < MAX_BULLET; iEmpty++)
			{
				if (!m_Bullet[iEmpty].m_bLife)
				{
					m_Bullet[iEmpty].m_bLife = true;
					break;
				}
			}

			// �ش� ��ġ�� �Ѿ� Ȱ��ȭ (���� �Ѿ�)
			m_Bullet[iEmpty].SetSprite(L"BulletGunLeft");
			m_Bullet[iEmpty].m_BulletType = BULLET_GUN_LEFT;
			m_Bullet[iEmpty].m_fPosYHead = fY;
			m_Bullet[iEmpty].m_fShotTime = g_fAccumulation;
			m_Bullet[iEmpty].SetObject(fX, fY, 0.0f);

			// ����ִ� �Ѿ� ������Ʈ �迭��ġ ã��
			for (iEmpty = 0; iEmpty < MAX_BULLET; iEmpty++)
			{
				if (!m_Bullet[iEmpty].m_bLife)
				{
					m_Bullet[iEmpty].m_bLife = true;
					break;
				}
			}
			
			// �ش� ��ġ�� �Ѿ� Ȱ��ȭ (������ �Ѿ�)
			m_Bullet[iEmpty].SetSprite(L"BulletGunRight");
			m_Bullet[iEmpty].m_BulletType = BULLET_GUN_RIGHT;
			m_Bullet[iEmpty].m_fPosYHead = fY;
			m_Bullet[iEmpty].m_fShotTime = g_fAccumulation;
			m_Bullet[iEmpty].SetObject(fX + (BLOCK_W * 2), fY, 0.0f);

			m_CountBullet += 3;
		}
		break;
	}
}

void GameMain::CreateEffect(EFFECT_TYPE iType, float fX, float fY)
{
	if (m_CountEffect < MAX_EFFECT)
	{
		// ����ִ� ����Ʈ �迭��ġ ã��
		int iEmpty;
		for (iEmpty = 0; iEmpty < MAX_EFFECT; iEmpty++)
		{
			if (!m_Effect[iEmpty].m_bLife)
			{
				m_Effect[iEmpty].m_bLife = true;
				break;
			}
		}

		switch (iType)
		{
		case EFFECT_NUCLEAR:
			m_Effect[iEmpty].SetSprite(L"EffectNuclear");
			m_Effect[iEmpty].m_EffectType = EFFECT_NUCLEAR;
			break;

		case EFFECT_FLOWER:
			m_Effect[iEmpty].SetSprite(L"EffectFlower");
			m_Effect[iEmpty].m_EffectType = EFFECT_FLOWER;
			break;
		}
		m_Effect[iEmpty].SetObject(fX, fY, 0.0f);

		m_CountEffect++;
	}
}

void GameMain::FrameKey()
{
	// ESC - ���ξ����� �̵�
	if (m_Input.KeyCheck(VK_ESCAPE) == KEY_PUSH)
	{
		m_GameState = STATE_MAIN;
		MainInit();
		return;
	}

	// Left - ���ΰ� �������� �̵�
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

	// Right - ���ΰ� ���������� �̵�
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

	// ����Ctrl - ���� �߻�
	if (m_Input.KeyCheck(VK_LCONTROL) == KEY_PUSH)
	{
		CreateBullet(m_BulletType, (float)m_Hero.m_posObject.x, (float)m_Hero.m_posObject.y);
	}

	// Up - �̵��ӵ� ����
	if (m_Input.KeyCheck(VK_UP) == KEY_HOLD)
	{
		m_Hero.SpeedUp();
	}

	// Down - �̵��ӵ� ����
	if (m_Input.KeyCheck(VK_DOWN) == KEY_HOLD)
	{
		m_Hero.SpeedDown();
	}

	// F1 ~ 4 - ���⺯��
	if (m_Input.KeyCheck(VK_F1) == KEY_PUSH)
	{
		m_BulletType = BULLET_SINGLE;
	}
	if (m_Input.KeyCheck(VK_F2) == KEY_PUSH)
	{
		m_BulletType = BULLET_DOUBLE;
	}
	if (m_Input.KeyCheck(VK_F3) == KEY_PUSH)
	{
		m_BulletType = BULLET_FIXED;
	}
	if (m_Input.KeyCheck(VK_F4) == KEY_PUSH)
	{
		m_BulletType = BULLET_GUN;
	}
}

void GameMain::FrameObject()
{
	int i;
	m_Ground.Frame();
	for (i = 0; i < MAX_BULLET; i++)
	{
		if (m_Bullet[i].m_bLife)
		{
			m_Bullet[i].Frame();
			// m_bLife �� false �� ��� (�Ѿ��� �������...)
			if (!m_Bullet[i].m_bLife)
				m_CountBullet--;
		}
	}
	for (i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Object[i].m_bLife)
		{
			m_Object[i].Frame();
		}
	}
	for (i = 0; i < MAX_EFFECT; i++)
	{
		if (m_Effect[i].m_bLife)
		{
			m_Effect[i].Frame();
			// m_bLife �� false �� ��� (����Ʈ�� �������...)
			if (!m_Effect[i].m_bLife)
				m_CountEffect--;
		}
	}
	m_Hero.Frame();
}

void GameMain::FrameTimer()
{
	// �̱��÷��� ���� ���۵ǰ� �帥�ð�
	if (g_fAccumulation - m_TimeStartGame > 10.0f)
	{
	}

	// ���� �ֱٿ� ���� �����ǰ� �帥�ð�
	if (g_fAccumulation - m_TimeMakeBall > REGENTIME_BALL)
	{
		int iPosXRand = rand() % (CLIENT_W - 300) + 100;
		int iSize = rand() % 5 + 1;
		CreateObject(OBJECT_BALL, (float)iPosXRand, (float)BOARD_Y, iSize);

		m_TimeMakeBall = g_fAccumulation;
	}

	// ���� �ֱٿ� �ٰ����� �����ǰ� �帥�ð�
	if (g_fAccumulation - m_TimeMakePolygon > REGENTIME_POLYGON)
	{
		int iPosXRand = rand() % (CLIENT_W - 300) + 100;
		int iSize = rand() % 5 + 1;
		CreateObject(OBJECT_POLYGON, (float)iPosXRand, (float)BOARD_Y, iSize);

		m_TimeMakePolygon = g_fAccumulation;
	}

	// ���� �ֱٿ� ����� �����ǰ� �帥�ð�
	if (g_fAccumulation - m_TimeMakeBlock > 10.0f)
	{
		m_TimeMakeBlock = g_fAccumulation;
	}

	// ���� �ֱٿ� �ð� �������� �����ǰ� �帥�ð�
	if (g_fAccumulation - m_TimeMakeClock > 10.0f)
	{
		m_TimeMakeClock = g_fAccumulation;
	}
}

void GameMain::FrameCollide()
{
	SPHERE sphObject, sphHero;
	RECT rectObject;
	POINT posBullet;

	int iObject = 0;
	int iBullet = 0;

	// ȭ�鿡 �����ϴ� ��� ���� ����
	for (iBullet = 0; iBullet < MAX_BULLET; iBullet++)
	{
		if(m_Bullet[iBullet].m_bLife)
		{
			posBullet.x = m_Bullet[iBullet].m_posObject.x + (BLOCK_W / 2);
			posBullet.y = (int)m_Bullet[iBullet].m_fPosYHead;
			switch (m_Bullet[iBullet].m_BulletType)
			{
			case BULLET_SINGLE:
			case BULLET_DOUBLE:
			case BULLET_FIXED:
				// ȭ�鿡 �����ϴ� ��� ������Ʈ�� �浹 �˻�
				for (iObject = 0; iObject < MAX_OBJECT; iObject++)
				{
					if (m_Object[iObject].m_bLife)
					{
						switch (m_Object[iObject].m_ObjectType)
						{
						case OBJECT_BALL:
						case OBJECT_POLYGON:
							sphObject.rad = m_Object[iObject].m_pSprite->m_iterFrame->rectSrc.right / 2.0f;
							sphObject.pos.x = m_Object[iObject].m_posObject.x + (int)sphObject.rad;
							sphObject.pos.y = m_Object[iObject].m_posObject.y + (int)sphObject.rad;
							// �ۻ��(����,����,����)�� ���̳� �ٰ����� �浹���� ���
							if (m_Collision.SphereInVLine(sphObject, posBullet, BOARD_Y + BOARD_H*BLOCK_H))
							{
								if (m_Object[iObject].m_iObjectSize > 1)
								{
									CreateObject(m_Object[iObject].m_ObjectType,
										m_Object[iObject].m_fPosX - (m_Object[iObject].m_iObjectSize * m_Object[iObject].m_iObjectSize * 5),
										m_Object[iObject].m_fPosY, m_Object[iObject].m_iObjectSize - 1);
									CreateObject(m_Object[iObject].m_ObjectType,
										m_Object[iObject].m_fPosX + (m_Object[iObject].m_iObjectSize * m_Object[iObject].m_iObjectSize * 5),
										m_Object[iObject].m_fPosY, m_Object[iObject].m_iObjectSize - 1);
								}

								m_Bullet[iBullet].m_bLife = false;
								m_CountBullet--;
								m_Object[iObject].m_bLife = false;
								m_CountObject--;

								///////////////////////////////////////////////////////////////////////////////////////////
								CreateEffect(EFFECT_FLOWER, m_Object[iObject].m_fPosX, m_Object[iObject].m_fPosY);
								iObject = MAX_OBJECT; // �ٸ� ������Ʈ�� �浹�˻����� �ʵ��� ���� ����Ż��
								break;
							}
							break;
						case OBJECT_BLOCK:
							rectObject;
							break;
						}
					}
				}
				break;

			case BULLET_GUN:
			case BULLET_GUN_LEFT:
			case BULLET_GUN_RIGHT:
				// ȭ�鿡 �����ϴ� ��� ������Ʈ�� �浹 �˻�
				for (iObject = 0; iObject < MAX_OBJECT; iObject++)
				{
					if (m_Object[iObject].m_bLife)
					{
						switch (m_Object[iObject].m_ObjectType)
						{
						case OBJECT_BALL:
						case OBJECT_POLYGON:
							sphObject.rad = m_Object[iObject].m_pSprite->m_iterFrame->rectSrc.right / 2.0f;
							sphObject.pos.x = m_Object[iObject].m_posObject.x + (int)sphObject.rad;
							sphObject.pos.y = m_Object[iObject].m_posObject.y + (int)sphObject.rad;
							// �Ѿ��� ���̳� �ٰ����� �浹���� ���
							if (m_Collision.SphereInPoint(sphObject, posBullet))
							{
								if (m_Object[iObject].m_iObjectSize > 1)
								{
									CreateObject(m_Object[iObject].m_ObjectType,
										m_Object[iObject].m_fPosX - (m_Object[iObject].m_iObjectSize * m_Object[iObject].m_iObjectSize * 5),
										m_Object[iObject].m_fPosY, m_Object[iObject].m_iObjectSize - 1);
									CreateObject(m_Object[iObject].m_ObjectType,
										m_Object[iObject].m_fPosX + (m_Object[iObject].m_iObjectSize * m_Object[iObject].m_iObjectSize * 5),
										m_Object[iObject].m_fPosY, m_Object[iObject].m_iObjectSize - 1);
								}

								m_Bullet[iBullet].m_bLife = false;
								m_CountBullet--;
								m_Object[iObject].m_bLife = false;
								m_CountObject--;

								///////////////////////////////////////////////////////////////////////////////////////////
								CreateEffect(EFFECT_FLOWER, m_Object[iObject].m_fPosX, m_Object[iObject].m_fPosY);
								iObject = MAX_OBJECT; // �ٸ� ������Ʈ�� �浹�˻����� �ʵ��� ���� ����Ż��
								break;
							}
							break;
						case OBJECT_BLOCK:
							rectObject;
							break;
						}
					}
				}
				break;
			}
		}
	} // ȭ�鿡 �����ϴ� ��� ���� ���� =====

	// ���ΰ��� ��ȣ�����̸� �浹 �˻����� �ʰ� ����
	if (g_fAccumulation - m_TimeDeath < SAFE_DEATHTIME)
		return;

	// ���ΰ��� ������Ʈ�� �浹 �˻�
	// ���ΰ��� �߽��� x��ǥ(23), y��ǥ(38), ������(20)
	sphHero.pos.x = m_Hero.m_posObject.x + 23;
	sphHero.pos.y = m_Hero.m_posObject.y + 38;
	sphHero.rad = 20;
	for (iObject = 0; iObject < MAX_OBJECT; iObject++)
	{
		if (m_Object[iObject].m_bLife)
		{
			switch (m_Object[iObject].m_ObjectType)
			{
			case OBJECT_BALL:
			case OBJECT_POLYGON:
				sphObject.rad = m_Object[iObject].m_pSprite->m_iterFrame->rectSrc.right / 2.0f;
				sphObject.pos.x = m_Object[iObject].m_posObject.x + (int)sphObject.rad;
				sphObject.pos.y = m_Object[iObject].m_posObject.y + (int)sphObject.rad;
				// ���ΰ��� ���̳� �ٰ����� �浹���� ���
				// SphereInSphere(SPHERE& sphDest, SPHERE& sphSrc);
				if (m_Collision.SphereInSphere(sphObject, sphHero))
				{
					if (m_Object[iObject].m_iObjectSize > 1)
					{
						CreateObject(m_Object[iObject].m_ObjectType,
							m_Object[iObject].m_fPosX - (m_Object[iObject].m_iObjectSize * m_Object[iObject].m_iObjectSize * 5),
							m_Object[iObject].m_fPosY, m_Object[iObject].m_iObjectSize - 1);
						CreateObject(m_Object[iObject].m_ObjectType,
							m_Object[iObject].m_fPosX + (m_Object[iObject].m_iObjectSize * m_Object[iObject].m_iObjectSize * 5),
							m_Object[iObject].m_fPosY, m_Object[iObject].m_iObjectSize - 1);
					}

					m_Object[iObject].m_bLife = false;
					m_CountObject--;

					m_TimeDeath = g_fAccumulation;
					m_CountLife--;

					if (m_CountLife < 1)
					{
						if (m_Hero.m_isLeft)
							m_Hero.SetSprite(L"HeroDie");
						else
							m_Hero.SetSprite(L"HeroDieRight");
					}

					CreateEffect(EFFECT_FLOWER, m_Object[iObject].m_fPosX, m_Object[iObject].m_fPosY);
					iObject = MAX_OBJECT; // �ٸ� ������Ʈ�� �浹�˻����� �ʵ��� ���� ����Ż��
					break;
				}
				break;
			}
		}
	} // ���ΰ��� ������Ʈ�� �浹 �˻� =====
}

bool GameMain::SingleInit()
{
	srand(time(NULL));

	m_Gameover.SetBitmap(L"gameover.bmp");
	m_Gameover.SetSprite(L"Gameover");

	m_Ground.SetBitmap(L"back1.bmp");
	m_Ground.SetSprite(L"Back1");

	m_Hero.SetBitmap(L"hero.bmp");
	m_Hero.SetSprite(L"HeroIdle");
	m_Hero.SetObject(BOARD_X + (BOARD_W*BLOCK_W - 45) / 2, BOARD_Y + (BOARD_H*BLOCK_H - 60), HERO_SPEED);

	int i;
	m_BulletType = DEFAULT_BULLET;

	m_CountBullet = 0;
	for (i = 0; i < MAX_BULLET; i++)
		m_Bullet[i].m_bLife = false;

	m_CountObject = 0;
	for (i = 0; i < MAX_OBJECT; i++)
		m_Object[i].m_bLife = false;

	m_CountEffect = 0;
	for (i = 0; i < MAX_EFFECT; i++)
		m_Effect[i].m_bLife = false;

	m_TimeStartGame = g_fAccumulation;
	m_TimeMakeBall = g_fAccumulation;
	m_TimeMakePolygon = g_fAccumulation;
	m_TimeMakeBlock = g_fAccumulation;
	m_TimeMakeClock = g_fAccumulation;
	m_TimeDeath = g_fAccumulation;

	m_CountLife = 2;

	// SOUND ##### 	m_Sound.Play(m_arySound[SOUND_BGM], true);

	return true;
}

bool GameMain::SingleFrame()
{
	if (m_CountLife < 1)
	{
		if (g_fAccumulation - m_TimeDeath > 7.0f)
		{
			m_GameState = STATE_MAIN;
			MainInit();
			return true;
		}
		else
		{
			float timeGameover = g_fAccumulation - m_TimeDeath;
		}
	}
	else
	{
		FrameKey();
		FrameCollide();
	}
	FrameObject();
	FrameTimer();

	return true;
}

bool GameMain::SingleRender()
{
	m_Ground.Render();
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_Bullet[i].m_bLife)
			m_Bullet[i].Render();
	}
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Object[i].m_bLife)
			m_Object[i].Render();
	}
	//for (int i = 0; i < MAX_EFFECT; i++)
	//{
	//	if (m_Effect[i].m_bLife)
	//		m_Effect[i].Render();
	//}
	m_Hero.Render();

	// ���ӿ��� ���� ���
	if (m_CountLife < 1)
	{
		if (g_fAccumulation - m_TimeDeath <= 7.0f)
		{
			float timeGameover = g_fAccumulation - m_TimeDeath;
			POINT posGameover = m_Gameover.m_posObject;
			//posGameover.y = (int)(-15.0f + timeGameover*30.0f);
			//if (m_Gameover.m_pSprite->m_iterFrame->pBitmap)
			//	m_Gameover.m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posGameover, m_Gameover.m_pSprite->m_iterFrame->rectSrc);
			m_Gameover.m_posObject.y = (int)(-140.0f + timeGameover*50.0f);
			m_Gameover.Render();
		}
	}

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
