#pragma once
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"
#include <windows.h>

#include "Tetromino.h"

#define BOARD_W			(10)
#define BOARD_H			(20)
#define BLOCK_BIG_W		(32)
#define BLOCK_BIG_H		(32)
#define BLOCK_SMALL_W	(16)
#define BLOCK_SMALL_H	(16)
#define MAX_NEXT		(3)
#define MAX_ITEM		(9)
#define MAX_PLAYER		(8)

#define DEFAULT_TERM_BLOCKDOWN	(0.8f)

//extern const int Tetromino[7][4][4][4];

class bgNetris
{
public:
	bgObject	m_objBlock;

	int		m_iBoard[BOARD_H + 2][BOARD_W + 2];
	int		m_iX;
	int		m_iY;
	int		m_iBlock;
	int		m_iRotate;
	int		m_iScore;
	int		m_iItem[MAX_ITEM];
	int		m_iBlockNext[MAX_NEXT];

	int		m_iMyID;
	int		m_iPlayerID;
	int		m_iBlockW;
	int		m_iBlockH;
	int		m_iBoardX;
	int		m_iBoardY;

	float	m_fTermBlockDown;

public:
	float	m_fTimeBlockDown;

	int		m_iCountBlock;
	int		m_iCountDelLine;

public:
	void	SetPlayerID(int iMyID, int iPlayerID) { m_iMyID = iMyID; m_iPlayerID = iPlayerID; }
	void	SetMove(int iX, int iY) { m_iX = iX; m_iY = iY; }
	void	SetMoveAdd(int iX, int iY) { m_iX += iX; m_iY += iY; }
	void	SetRotate(int iRotate) { m_iRotate = (iRotate) % 4; }
	void	SetRotateAdd(int iRotate) { m_iRotate = (m_iRotate + iRotate) % 4; }
	void	SetBlock(int iBlock) { m_iBlock = iBlock; }
	void	SetBlockNext();
	void	DelLine(int iY = BOARD_H);

	void	InitPlayer();
	void	InitBoard();
	void	SaveTetromino(int iX, int iY, int iBlock, int iRotate);
	bool	CollideTetromino(int iX, int iY, int iBlock, int iRotate);

public:
	void	DrawBlock(int iX, int iY, int iBlock, bool bBig);
	void	DrawTetromino(int iX, int iY, int iBlock, int iRotate, bool bBig);
	void	DrawTetrominoAdd(int iX, int iY, int iBlock, int iRotate, bool bBig);
	void	DrawBoard(bool bBig);
	void	DrawItem();

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	bgNetris();
	virtual ~bgNetris();
};
