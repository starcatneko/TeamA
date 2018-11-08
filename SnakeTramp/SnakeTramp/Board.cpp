#include "VECTOR2.h"
#include "GameTask.h"
#include "Board.h"
#include "Card.h"


void Board::Update(void)
{
	for (int x = 0; x < troutCnt.x + 1; x++)
	{
		DrawLine(x * TROUT_SIZE + 180, 80, x * TROUT_SIZE + 180, 80 + 60 * 7, 0xffffff);
	}
	for (int y = 0; y < troutCnt.y + 1; y++)
	{
		DrawLine(180,y * TROUT_SIZE + 80, 180 + 60 * 7, y * TROUT_SIZE + 80, 0xffffff);
	}
	PushTrout();
	DrawString(50, 0, DebugChar, 0xffffff);
}

bool Board::CheckBoard(VECTOR2 pos, int moveDirection)
{
	switch (moveDirection)
	{
	case DIR_UP:
		break;
	case DIR_RIGHT:
		break;
	case DIR_DOWN:
		break;
	case DIR_LEFT:
		break;
	default:
		break;
	}
	/*for (int y = 0; y < troutCnt.y; y++)
	{
		for (int x = 0; x < troutCnt.x; x++)
		{
			if (data[y][x].expired())
			{
				int a = 0;
			}
		}
	}*/
	return false;
}

void Board::PushTrout(void)
{
	if (lpGameTask.PressKey(KEY_INPUT_UP))
	{
		moveDirection = DIR_UP;
		ckPos = pPos + VECTOR2(0, 1);
		DebugChar = "ã";
	}
	else if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
	{
		moveDirection = DIR_RIGHT;
		ckPos = pPos + VECTOR2(1,0);
		DebugChar = "‰E";
	}
	else if (lpGameTask.PressKey(KEY_INPUT_DOWN))
	{
		moveDirection = DIR_DOWN;
		ckPos = pPos + VECTOR2(0, -1);
		DebugChar = "‰º";
	}
	else if (lpGameTask.PressKey(KEY_INPUT_LEFT))
	{
		moveDirection = DIR_LEFT;
		ckPos = pPos + VECTOR2(-1,0);
		DebugChar = "¶";
	}
}

Board::Board()
{
	troutCnt = VECTOR2(BOARD_DEF_TROUT_X, BOARD_DEF_TROUT_Y);
	moveDirection = DIR_RIGHT;
	pPos = BOARD_START;
}

Board::Board(VECTOR2 troutCnt)
{
	this->troutCnt = troutCnt;
}


Board::~Board()
{
}

