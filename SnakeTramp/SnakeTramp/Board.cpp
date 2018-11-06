#include "VECTOR2.h"
#include "GameTask.h"
#include "Board.h"
#include "Card.h"


bool Board::CheckBoard(VECTOR2 pos)
{
	for (int y = 0; y < troutCnt.y; y++)
	{
		for (int x = 0; x < troutCnt.x; x++)
		{
			
		}
	}
	return false;
}

bool Board::SetBoard(VECTOR2 pos)
{
	return false;
}

Board::Board()
{
	troutCnt = VECTOR2(BOARD_DEF_TROUT_X, BOARD_DEF_TROUT_Y);
}

Board::Board(VECTOR2 troutCnt)
{
	this->troutCnt = troutCnt;
}

void Board::PushTrout(void)
{
	if (lpGameTask.PressKey(KEY_INPUT_UP))
	{

	}
	else if (lpGameTask.PressKey(KEY_INPUT_DOWN))
	{

	}
	else if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
	{

	}
	else if (lpGameTask.PressKey(KEY_INPUT_LEFT))
	{

	}
}

Board::~Board()
{
}

