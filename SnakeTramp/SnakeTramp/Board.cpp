#include "VECTOR2.h"
#include "GameTask.h"
#include "Board.h"
#include "Card.h"


void Board::Update(void)
{
	PushTrout();
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
		DrawString(50, 0, "ã", GetColor(255, 255, 255));
	}
	else if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
	{
		moveDirection = DIR_RIGHT;
		ckPos = pPos + VECTOR2(1,0);
		DrawString(50, 0, "‰E", GetColor(255, 255, 255));
	}
	else if (lpGameTask.PressKey(KEY_INPUT_DOWN))
	{
		moveDirection = DIR_DOWN;
		ckPos = pPos + VECTOR2(0, -1);
		DrawString(50, 0, "‰º", GetColor(255, 255, 255));
	}
	else if (lpGameTask.PressKey(KEY_INPUT_LEFT))
	{
		moveDirection = DIR_LEFT;
		ckPos = pPos + VECTOR2(-1,0);
		DrawString(50, 0, "ã", GetColor(255, 255, 255));
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

