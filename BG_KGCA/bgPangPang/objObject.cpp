#include "objObject.h"
#include "GameMain.h"


bool objObject::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	// 개수대로 로드하는 문제로 인해서 메인에서 로드...
	// I_SpriteMgr.Add(L"../../data/bgPangPang/object.txt");
	SetBitmap(L"object.bmp");
	m_bLife = false;

	return true;
}

bool objObject::Frame()
{
	//bgObject::Frame();
	
	switch (m_ObjectType)
	{
	case OBJECT_BALL:
	{
		m_fPosX += g_fSPF * m_fPosA;
		m_fPosY += g_fSPF * m_fPosB;
		//m_fPosY = BOARD_Y + (BOARD_H*BLOCK_H) + (g_fSPF * m_fPosB); ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_posObject.x = (int)m_fPosX;
		m_posObject.y = (int)m_fPosY;

		// X좌표가 게임 Width를 벗어나면...
		int iWidthObject = m_pSprite->m_iterFrame->rectSrc.right;
		if (m_posObject.x < BOARD_X)
		{
			m_posObject.x = BOARD_X + 1;
			m_fPosA = abs(m_fPosA);
		}
		else if (m_posObject.x > BOARD_X + (BOARD_W*BLOCK_W) - iWidthObject)
		{
			m_posObject.x = BOARD_X + (BOARD_W*BLOCK_W) - iWidthObject - 1;
			m_fPosA = -1.0f * abs(m_fPosA);
		}

		// Y좌표가 게임 Height를 벗어나면...
		int iHeightObject = m_pSprite->m_iterFrame->rectSrc.bottom;
		if (m_posObject.y < BOARD_Y)
		{
			m_posObject.y = BOARD_Y + 1;
			m_fPosB = abs(m_fPosB);
		}
		else if (m_posObject.y > BOARD_Y + (BOARD_H*BLOCK_H) - iHeightObject)
		{
			m_posObject.y = BOARD_Y + (BOARD_H*BLOCK_H) - iHeightObject - 1;
			m_fPosB = -1.0f * abs(m_fPosB);
		}
	}
	break;

	case OBJECT_POLYGON:
	{
		m_fPosX += g_fSPF * m_fPosA;
		m_fPosY += g_fSPF * m_fPosB;
		m_posObject.x = (int)m_fPosX;
		m_posObject.y = (int)m_fPosY;

		// X좌표가 게임 Width를 벗어나면...
		int iWidthObject = m_pSprite->m_iterFrame->rectSrc.right;
		if (m_posObject.x < BOARD_X)
		{
			m_posObject.x = BOARD_X + 1;
			m_fPosA = abs(m_fPosA);
		}
		else if (m_posObject.x > BOARD_X + (BOARD_W*BLOCK_W) - iWidthObject)
		{
			m_posObject.x = BOARD_X + (BOARD_W*BLOCK_W) - iWidthObject - 1;
			m_fPosA = -1.0f * abs(m_fPosA);
		}

		// Y좌표가 게임 Height를 벗어나면...
		int iHeightObject = m_pSprite->m_iterFrame->rectSrc.bottom;
		if (m_posObject.y < BOARD_Y)
		{
			m_posObject.y = BOARD_Y + 1;
			m_fPosB = abs(m_fPosB);
		}
		else if (m_posObject.y > BOARD_Y + (BOARD_H*BLOCK_H) - iHeightObject)
		{
			m_posObject.y = BOARD_Y + (BOARD_H*BLOCK_H) - iHeightObject - 1;
			m_fPosB = -1.0f * abs(m_fPosB);
		}
	}
	break;

	case OBJECT_BLOCK:
	{
	}
	break;
	}
	return true;
}

bool objObject::Render()
{
	//bgObject::Render();
	if (m_pSprite->m_iterFrame->pBitmap)
	{
		POINT posObject;
		switch (m_ObjectType)
		{
		case OBJECT_BALL:
			switch (m_iObjectSize)
			{
			case 1:
				SetSprite(L"Ball1");
				break;
			case 2:
				SetSprite(L"Ball2");
				break;
			case 3:
				SetSprite(L"Ball3");
				break;
			case 4:
				SetSprite(L"Ball4");
				break;
			case 5:
				SetSprite(L"Ball5");
				break;
			}
			posObject.x = m_posObject.x;
			posObject.y = m_posObject.y;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posObject, m_pSprite->m_iterFrame->rectSrc);
			break;

		case OBJECT_POLYGON:
			switch (m_iObjectSize)
			{
			case 1:
				SetSprite(L"Polygon1");
				break;
			case 2:
				SetSprite(L"Polygon2");
				break;
			case 3:
				SetSprite(L"Polygon3");
				break;
			case 4:
				SetSprite(L"Polygon4");
				break;
			case 5:
				SetSprite(L"Polygon5");
				break;
			}
			posObject.x = m_posObject.x;
			posObject.y = m_posObject.y;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posObject, m_pSprite->m_iterFrame->rectSrc);
			break;

		case OBJECT_BLOCK:
			SetSprite(L"Block1");
			posObject.x = m_posObject.x;
			posObject.y = m_posObject.y;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posObject, m_pSprite->m_iterFrame->rectSrc);
			break;
		}
	}
	return true;
}

bool objObject::Release()
{
	//bgObject::Release();
	return true;
}

objObject::objObject()
{
}


objObject::~objObject()
{
}
