#include "bgNetris.h"

void bgNetris::SetBlockNext()
{
	int i;

	// 좌표(가운데,가장위), 블럭(다음블럭), 회전(0도)
	m_iX = BOARD_W / 2 - 1;
	m_iY = 1;
	m_iBlock = m_iBlockNext[0];
	m_iRotate = 0;

	// 카운트
	m_iCountBlock++;

	// 다음블럭 대기열 한칸씩 이동
	for (i = 0; i < MAX_NEXT - 1; i++)
		m_iBlockNext[i] = m_iBlockNext[i + 1];
	m_iBlockNext[MAX_NEXT - 1] = rand() % 7 + 1;
}

void bgNetris::InitPlayer()
{
	int i;

	// 모든 플레이어들 공통적인 변수 초기화
	m_iX = BOARD_W / 2 - 1;
	m_iY = 1;
	m_iBlock = rand() % 7 + 1;
	m_iRotate = 0;
	m_iScore = 0;

	m_iCountBlock = 0;
	m_iCountDelLine = 0;

	m_fTermBlockDown = DEFAULT_TERM_BLOCKDOWN;
	m_fTimeBlockDown = g_fAccumulation;

	for (i = 0; i < MAX_ITEM; i++)
		m_iItem[i] = 0;
	for (i = 0; i < MAX_NEXT; i++)
		m_iBlockNext[i] = rand() % 7 + 1;

	// 플레이어 자기 자신일 경우
	if (m_iPlayerID == m_iMyID)
	{
		m_iBlockW = BLOCK_BIG_W;
		m_iBlockH = BLOCK_BIG_H;
		m_iBoardX = 689 - BLOCK_BIG_W;
		m_iBoardY = 113 - BLOCK_BIG_H;

	}
	// 다른 플레이어일 경우
	else
	{
		int iID = (m_iPlayerID + MAX_PLAYER - m_iMyID) % MAX_PLAYER;
		m_iBlockW = BLOCK_SMALL_W;
		m_iBlockH = BLOCK_SMALL_H;
		m_iBoardX = (516 - BLOCK_SMALL_W) - ((iID / 2) * 167);
		m_iBoardY = (15 - BLOCK_SMALL_H) + ((iID % 2) * 418);

	}
}

void bgNetris::InitBoard()
{
	int x, y;

	// 빈 공간
	for (y = 1; y < BOARD_H + 1; y++)
	{
		for (x = 1; x < BOARD_W + 1; x++)
		{
			m_iBoard[y][x] = 0;
		}
	}

	// 벽 (좌측, 우측)
	for (y = 0; y < BOARD_H + 2; y++)
	{
		m_iBoard[y][0] = m_iBoard[y][BOARD_W + 1] = BLOCK_EDGE;
	}

	// 벽 (위, 아래)
	for (x = 1; x < BOARD_W + 1; x++)
	{
		m_iBoard[0][x] = m_iBoard[BOARD_H + 1][x] = BLOCK_EDGE;
	}
}

void bgNetris::SaveTetromino(int iX, int iY, int iBlock, int iRotate)
{
	int x, y;
	iRotate %= 4;

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			// 테트로미노의 위치(x,y)에 블럭이 있으면...
			if (Tetromino[iBlock - 1][iRotate][y][x] != 0)
				m_iBoard[iY + y][iX + x] = iBlock * 10; // 보드의 해당 위치(iX + x, iY + y)에 저장시킴
		}
	}
}

bool bgNetris::CollideTetromino(int iX, int iY, int iBlock, int iRotate)
{
	int x, y;
	iRotate %= 4;

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			// 테트로미노의 위치(x,y)와 보드의 해당 위치(iX+x,iY+y) 모두에 블럭이 있는경우
			if (Tetromino[iBlock - 1][iRotate][y][x] != 0 && m_iBoard[iY + y][iX + x] != 0)
				return true; // 충돌함 리턴
		}
	}
	return false; // 충돌하지 않음
}

void bgNetris::DelLine(int iY)
{
	int x, y, iDel;

	// 가장 아랫줄부터 전체 줄을 반복
	for (y = iY; y > 1; y--)
	{
		// 한 줄을 검사하여 빈 블럭이 있다면 건너뜀
		for (x = 1; x <= BOARD_W; x++)
		{
			if (m_iBoard[y][x] < 10)
				break;
		}

		// 한 줄에 모두 블럭이 있다면...
		if (x > BOARD_W)
		{
			// 윗블럭들을 모두 한칸씩 내림 (해당 줄을 지움)
			for (iDel = y; iDel > 1; iDel--)
			{
				for (x = 1; x <= BOARD_W; x++)
				{
					m_iBoard[iDel][x] = m_iBoard[iDel - 1][x];
				}
			}
			// 가장 윗줄은 빈 블럭으로 지정
			for (x = 1; x <= BOARD_W; x++)
			{
				m_iBoard[1][x] = BLOCK_NONE;
			}
			y++; // 한줄씩 내려왔으므로 해당 줄 다시 검사
		}
	}

}

void bgNetris::DrawBlock(int iX, int iY, int iBlock, bool bBig)
{
	POINT pos = { iX, iY };
	RECT rect;
	if (bBig)
	{
		rect.left = iBlock % 10 * BLOCK_BIG_W;
		rect.top = iBlock / 10 * BLOCK_BIG_H;
		rect.right = BLOCK_BIG_W;
		rect.bottom = BLOCK_BIG_H;
	}
	else
	{
		rect.left = iBlock % 10 * BLOCK_SMALL_W;
		rect.top = iBlock / 10 * BLOCK_SMALL_H;
		rect.right = BLOCK_SMALL_W;
		rect.bottom = BLOCK_SMALL_H;
	}
	m_objBlock.SetObject((float)iX, (float)iY, 0.0f);
	m_objBlock.m_pBitmap->Draw(g_hOffScreenDC, pos, rect);
}

void bgNetris::DrawTetromino(int iX, int iY, int iBlock, int iRotate, bool bBig)
{
	if (bBig)
		m_objBlock.SetBitmap(L"block_big.bmp");
	else
		m_objBlock.SetBitmap(L"block_small.bmp");

	int x, y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (Tetromino[iBlock - 1][iRotate][y][x] != 0)
			{
				DrawBlock(m_iBoardX + ((iX + x) * m_iBlockW), m_iBoardY + ((iY + y) * m_iBlockH), iBlock * 10, bBig);
			}
		}
	}
}

void bgNetris::DrawTetrominoAdd(int iX, int iY, int iBlock, int iRotate, bool bBig)
{
	if (bBig)
		m_objBlock.SetBitmap(L"block_big.bmp");
	else
		m_objBlock.SetBitmap(L"block_small.bmp");

	int x, y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (Tetromino[iBlock - 1][iRotate][y][x] != 0)
			{
				DrawBlock(iX + (x * m_iBlockW), iY + (y * m_iBlockH), iBlock * 10, bBig);
			}
		}
	}
}

void bgNetris::DrawBoard(bool bBig)
{
	if(bBig)
		m_objBlock.SetBitmap(L"block_big.bmp");
	else
		m_objBlock.SetBitmap(L"block_small.bmp");

	int x, y;
	for (y = 1; y < BOARD_H + 1; y++)
	{
		for (x = 1; x < BOARD_W + 1; x++)
		{
			DrawBlock(m_iBoardX + (x * m_iBlockW), m_iBoardY + (y * m_iBlockH), m_iBoard[y][x], bBig);
		}
	}
}

void bgNetris::DrawItem()
{
	int iID = (m_iPlayerID + MAX_PLAYER - m_iMyID) % MAX_PLAYER;
	int i, x, y, w, h;

	// 0번 아이템은 크게 출력
	m_objBlock.SetBitmap(L"block_big.bmp");
	i = 0;
	w = BLOCK_BIG_W;
	h = BLOCK_BIG_H;
	x = 644 - (iID / 2 * 167) - (i * BLOCK_SMALL_W);
	y = 340 + (iID % 2 * 72) - (iID % 2 * 16);
	DrawBlock(x, y, m_iItem[0], true);

	// 1 ~ MAX_ITEM-1번까지 아이템은 작게 출력
	m_objBlock.SetBitmap(L"block_small.bmp");
	w = BLOCK_SMALL_W;
	h = BLOCK_SMALL_H;
	for (i = 1; i < MAX_ITEM; i++)
	{
		x = 644 - (iID / 2 * 167) - (i * BLOCK_SMALL_W);
		y = 340 + (iID % 2 * 72);
		DrawBlock(x, y, m_iItem[i], false);
	}

}

bool bgNetris::Init()
{
	InitBoard();
	InitPlayer();

	m_objBlock.SetDC(g_hOffScreenDC);
	m_objBlock.Init();
	return true;
}

bool bgNetris::Frame()
{
	return true;
}

bool bgNetris::Render()
{
	DrawBoard(m_iPlayerID == m_iMyID);
	DrawItem();
	DrawTetromino(m_iX, m_iY, m_iBlock, m_iRotate, (m_iPlayerID == m_iMyID));
	return true;
}

bool bgNetris::Release()
{
	return true;
}

bgNetris::bgNetris()
{
}

bgNetris::~bgNetris()
{
}
