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

void Board::SetBoard(card_shared card)
{
	data[card->GetPos().y][card->GetPos().x] = card;
}

card_weak Board::GetBoard(VECTOR2 pos)
{
	if (!suit.empty())
	{
		if (*suit.begin())
		{
			return data[pos.y][pos.x];
		}
	}
	return data[pos.y][pos.x];
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
	return false;
}

bool Board::Resize(VECTOR2 vec)
{
	baseData.resize(vec.y * vec.x);

	data.resize(vec.y);

	for (unsigned int j = 0; j < data.size(); j++)
	{
		data[j] = &baseData[j * vec.x];
	}
	
	screenSize = VECTOR2(800, 600);
	boardLT = VECTOR2(((screenSize.x - (TROUT_SIZE * boardSize.x)) / 2), 
						((screenSize.y - (TROUT_SIZE * boardSize.y)) / 2));

	return true;
}

void Board::PushTrout(void)
{
	if (lpGameTask.PressKey(KEY_INPUT_UP))
	{
		moveDirection = DIR_UP;
		DebugChar = "ã";
	}
	else if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
	{
		moveDirection = DIR_RIGHT;
		DebugChar = "‰E";
	}
	else if (lpGameTask.PressKey(KEY_INPUT_DOWN))
	{
		moveDirection = DIR_DOWN;
		DebugChar = "‰º";
	}
	else if (lpGameTask.PressKey(KEY_INPUT_LEFT))
	{
		moveDirection = DIR_LEFT;
		DebugChar = "¶";
	}
}

auto Board::AddObjList(card_shared && objPtr)
{
	cardList.push_back(objPtr);
	auto itr = cardList.end();
	itr--;
	return itr;
}

Board::Board()
{
	troutCnt = VECTOR2(BOARD_DEF_TROUT_X, BOARD_DEF_TROUT_Y);
	Resize(troutCnt);
	moveDirection = DIR_RIGHT;
	pPos = BOARD_START;	
}

Board::Board(VECTOR2 troutCnt)
{
	this->troutCnt = troutCnt;
	Resize(this->troutCnt);
}


Board::~Board()
{
}

