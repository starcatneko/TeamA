#include "VECTOR2.h"
#include "GameTask.h"
#include "Board.h"
#include "Card.h"


void Board::Update(void)
{
	PushTrout();
	DrawString(50, 0, DebugChar, GetColor(255, 255, 255));
}

bool Board::CheckBoard(VECTOR2 pos)
{
	for (pPos.y -1; pPos.y < pPos.y + 1; pPos.y++)
	{
		for (pPos.x - 1; pPos.x < pPos.x + 1; pPos.x++)
		{

		}
	}
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

bool Board::SetBoard(VECTOR2 pos)
{
	return false;
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

