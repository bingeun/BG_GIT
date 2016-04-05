#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "bgKey.h"
#include "Tetromino.h"

extern const int Tetromino[7][4][4][4];
extern const char BoxChar[9][3];
extern const int BlockColor[9];

const int SIZE_BOARD_W = 10;
const int SIZE_BOARD_H = 20;
const int POS_BOARD_X = 80 / 2 - (SIZE_BOARD_W + 2);
const int POS_BOARD_Y = 2;
const int POS_NEXT_X = SIZE_BOARD_W + 4;
const int POS_NEXT_Y = 2;
const int POS_SCORE_X = POS_BOARD_X + SIZE_BOARD_W * 2 + 9;
const int POS_SCORE_Y = POS_BOARD_Y;

int Board[SIZE_BOARD_H + 1][SIZE_BOARD_W + 2];

struct PlayerInfo
{
	int x;
	int y;
	int rotate;
	int block;
	int block_next;
	int score;
	clock_t tick;
};

void GotoXY(int x, int y)
{
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
}

void SetCursor(bool bVisible = true)
{
	GotoXY(0, 0);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = bVisible; // true 보임, false 안보임
	ConsoleCursor.dwSize = 1; // 커서사이즈
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void SetColor(int block)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BlockColor[block]);
}

void SetColor(int text_color, int back_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color | back_color);
}

void DrawBlock(int x, int y, int block)
{
	GotoXY(x, y);
	SetColor(block);
	printf("%s", BoxChar[block % 9]);
}

void DrawTetromino(int x, int y, int block, int rotate, bool isBack = false)
{
	int i, j;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			if (Tetromino[block - 1][rotate][j][i] != 0)
			{
				if(isBack)
					DrawBlock((x + i) * 2 + POS_BOARD_X, (y + j) + POS_BOARD_Y, 0);
				else
					DrawBlock((x + i) * 2 + POS_BOARD_X, (y + j) + POS_BOARD_Y, block);
			}
		}
	}
}

void DrawNext(int now_block, int next_block)
{
	DrawTetromino(POS_NEXT_X, POS_NEXT_Y, now_block, 0, true);
	DrawTetromino(POS_NEXT_X, POS_NEXT_Y, next_block, 0, false);
}

void PrintScore(int score)
{
	SetColor(TEXT_COLOR_WL, BACK_COLOR_KD);
	GotoXY(POS_SCORE_X, POS_SCORE_Y - 1);
	printf("SCORE");
	GotoXY(POS_SCORE_X, POS_SCORE_Y);
	printf("%7d", score);
}

bool CollideTetromino(int x, int y, int block, int rotate)
{
	int i, j;
	rotate %= 4;

	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			// 테트로미노의 위치(i,j)와 보드의 해당 위치(x,y) 모두에 블럭이 있는경우
			if (Tetromino[block - 1][rotate][j][i] != 0 && Board[y + j][x + i] != 0)
				return true; // 충돌함 리턴
		}
	}
	return false; // 충돌하지 않음 리턴
}

int CollideBottom(int x, int y, int block, int rotate)
{
	while (CollideTetromino(x, y, block, rotate) == false)
		y++;
	return (y - 1 < 0) ? 0 : y - 1;
}

void DropBoard(int del_line)
{
	int i, j;
	for (j = del_line; j > 0; j--)
	{
		for (i = 1; i <= SIZE_BOARD_W; i++)
		{
			Board[j][i] = Board[j - 1][i];
		}
	}
	for (i = 1; i <= SIZE_BOARD_W; i++)
	{
		Board[0][i] = 0;
	}
}

int DeleteLine()
{
	int i, j, iCountLine = 0;
	for (j = SIZE_BOARD_H - 1; j > 0; j--)
	{
		for (i = 1; i <= SIZE_BOARD_W; i++)
		{
			if (Board[j][i] == 0)
				break;
		}
		// 한 줄이 채워졌다면...
		if (i >= SIZE_BOARD_W)
		{
			DropBoard(j);
			iCountLine++;
			j++;
		}
	}
	return iCountLine;
}

void SaveTetromino(int x, int y, int block, int rotate)
{
	int i, j;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			if (Tetromino[block - 1][rotate][j][i] != 0)
				Board[y + j][x + i] = block;
		}
	}
}

void InitBoard()
{
	// 빈공간
	int i, j;
	for (j = 0; j < SIZE_BOARD_H; j++)
	{
		for (i = 1; i < SIZE_BOARD_W + 1; i++)
		{
			Board[j][i] = 0;
		}
	}
	// 벽 (좌측, 우측)
	for (j = 0; j < SIZE_BOARD_H; j++)
	{
		Board[j][0] = Board[j][SIZE_BOARD_W + 1] = 8;
	}
	// 벽 (아래)
	for (i = 0; i < SIZE_BOARD_W + 2; i++)
	{
		Board[SIZE_BOARD_H][i] = 8;
	}
}

void InitPlayer(PlayerInfo* player)
{
	player->x = SIZE_BOARD_W / 2 - 1;
	player->y = 0;
	player->rotate = 0;
	player->block = rand() % 7 + 1;
	player->block_next = rand() % 7 + 1;
	player->tick = clock();
	player->score = 0;
}

void SetNext(PlayerInfo* player)
{
	player->x = SIZE_BOARD_W / 2 - 1;
	player->y = 0;
	player->rotate = 0;
	player->block = player->block_next;
	player->block_next = rand() % 7 + 1;
	player->tick = clock();
}

void DrawBoard(bool back_draw = false)
{
	int i, j;
	for (j = 0; j < SIZE_BOARD_H + 1; j++)
	{
		for (i = 0; i < SIZE_BOARD_W + 2; i++)
		{
			if (back_draw)
				DrawBlock(i * 2 + POS_BOARD_X, j + POS_BOARD_Y, Board[j][i]);
			else
			{
				if (Board[j][i] != 0)
					DrawBlock(i * 2 + POS_BOARD_X, j + POS_BOARD_Y, Board[j][i]);
			}
		}
	}
}

void Draw(PlayerInfo* player)
{
	SetColor(TEXT_COLOR_WL, BACK_COLOR_KD);
	system("cls");
	DrawBoard();
	DrawTetromino(player->x, player->y, player->block, player->rotate);
	DrawNext(player->block, player->block_next);
	PrintScore(player->score);
}

void main()
{
	PlayerInfo player;
	int game_state = 1;
	clock_t tick_now;

	SetCursor(false);
	srand((unsigned)time(NULL));
	{
		InitBoard();
		InitPlayer(&player);
		Draw(&player);

		while (game_state)
		{
			tick_now = clock();
			if (tick_now - player.tick > 700) // 0.7초가 지나면
			{
				player.tick = tick_now;
				///////////////// 키보드 아래 누른것과 같은 처리
				if (false == CollideTetromino(player.x, player.y + 1, player.block, player.rotate))
				{
					DrawTetromino(player.x, player.y, player.block, player.rotate, true);
					player.y++;
					DrawTetromino(player.x, player.y, player.block, player.rotate);
				}
				else
				{
					SaveTetromino(player.x, player.y, player.block, player.rotate);
					player.score += DeleteLine() * 100;
					PrintScore(player.score);
					DrawBoard(true);

					SetNext(&player);
					DrawTetromino(player.x, player.y, player.block, player.rotate);
					DrawNext(player.block, player.block_next);
				}
				///////////////// 여기까지
			}

			while (_kbhit())
			{
				switch (_getch())
				{
					/////////////////////////////////////////////////////////////////
				case KEY_LEFT: // 한 칸 왼쪽으로 이동
					if (false == CollideTetromino(player.x - 1, player.y, player.block, player.rotate))
					{
						DrawTetromino(player.x, player.y, player.block, player.rotate, true);
						player.x--;
						DrawTetromino(player.x, player.y, player.block, player.rotate);
					}
					break;
					/////////////////////////////////////////////////////////////////
				case KEY_RIGHT: // 한 칸 오른쪽으로 이동
					if (false == CollideTetromino(player.x + 1, player.y, player.block, player.rotate))
					{
						DrawTetromino(player.x, player.y, player.block, player.rotate, true);
						player.x++;
						DrawTetromino(player.x, player.y, player.block, player.rotate);
					}
					break;
					/////////////////////////////////////////////////////////////////
				case 'X': // 회전 - 시계방향
				case 'x':
					if (false == CollideTetromino(player.x, player.y, player.block, (player.rotate + 3) % 4))
					{
						DrawTetromino(player.x, player.y, player.block, player.rotate, true);
						player.rotate = (player.rotate + 3) % 4;
						DrawTetromino(player.x, player.y, player.block, player.rotate);
					}
					break;
					/////////////////////////////////////////////////////////////////
				case KEY_UP: // 회전 - 반시계방향
					if (false == CollideTetromino(player.x, player.y, player.block, (player.rotate + 1) % 4))
					{
						DrawTetromino(player.x, player.y, player.block, player.rotate, true);
						player.rotate = (player.rotate + 1) % 4;
						DrawTetromino(player.x, player.y, player.block, player.rotate);
					}
					break;
					/////////////////////////////////////////////////////////////////
				case KEY_DOWN: // 한 줄 내리기
					if (false == CollideTetromino(player.x, player.y + 1, player.block, player.rotate))
					{
						DrawTetromino(player.x, player.y, player.block, player.rotate, true);
						player.y++;
						DrawTetromino(player.x, player.y, player.block, player.rotate);
					}
					else
					{
						SaveTetromino(player.x, player.y, player.block, player.rotate);
						player.score += DeleteLine() * 100;
						PrintScore(player.score);
						DrawBoard(true);

						SetNext(&player);
						DrawTetromino(player.x, player.y, player.block, player.rotate);
						DrawNext(player.block, player.block_next);
					}
					break;
					/////////////////////////////////////////////////////////////////
				case 'Z': // 드롭 다운!
				case 'z':
				case KEY_SPACE:
					DrawTetromino(player.x, player.y, player.block, player.rotate, true);
					player.y = CollideBottom(player.x, player.y, player.block, player.rotate);
					DrawTetromino(player.x, player.y, player.block, player.rotate);
					SaveTetromino(player.x, player.y, player.block, player.rotate);
					player.score += DeleteLine() * 100;
					PrintScore(player.score);
					DrawBoard(true);

					SetNext(&player);
					DrawTetromino(player.x, player.y, player.block, player.rotate);
					DrawNext(player.block, player.block_next);
					break;
					/////////////////////////////////////////////////////////////////
				case KEY_ENTER:
					InitBoard();
					InitPlayer(&player);
					Draw(&player);
					break;
					/////////////////////////////////////////////////////////////////
				case KEY_ESC:
					game_state = 0;
					break;
				}
			}
		}
	}
}