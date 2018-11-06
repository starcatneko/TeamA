#include "Board.h"
#include "VECTOR2.h"


VECTOR2 Board::BoardTrout()
{
	return VECTOR2(troutCnt.x, troutCnt.y);
}

bool Board::CheckBoard(VECTOR2 pos)
{
	for (int y = 0; y < BoardTrout().y; y++)
	{
		for (int x = 0; x < BoardTrout().x; x++)
		{

		}
	}
	return false;
}

bool Board::SetBoard(VECTOR2 pos)
{
	return false;
}

Board::Board(bool defFlag, VECTOR2 troutCnt)
{
	changeFlag = defFlag;
	if (changeFlag)
	{
		this->troutCnt = troutCnt;
	}
	else if (!changeFlag)
	{
		this->troutCnt = VECTOR2(BOARD_DEF_TROUT_X, BOARD_DEF_TROUT_Y);
	}
}

Board::~Board()
{
}

