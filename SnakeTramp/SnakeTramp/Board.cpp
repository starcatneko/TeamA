#include "VECTOR2.h"
#include "GameTask.h"
#include "Board.h"
#include "Card.h"
#include "ImgMng.h"


void Board::Update(void)
{
	if (lpGameTask.PressKey(KEY_INPUT_SPACE))
	{
		score++;
	}
	Draw();
	PushTrout();
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
	//return SUIT_NON;
	return data[0][0];
}

CARD_SUIT Board::GetSuit(VECTOR2 pos)
{
	//return SUIT_DIA;
	auto tmp = data[pos.y][pos.x].lock()->GetSuit();
	return data[pos.y][pos.x].lock()->GetSuit();
}

int Board::GetNumber(VECTOR2 pos)
{
	//return 12;
	return data[pos.y][pos.x].lock()->GetNum();
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

void Board::Draw(void)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			VECTOR2 *cPos = 0;
			CARD_SUIT *cSuit = 0;
			int *number = 0;
			VEC_INT image;
			*cPos = data[y][x].lock()->GetPos();
			*cSuit = data[y][x].lock()->GetSuit();
			*number = data[y][x].lock()->GetNum();

			card = std::make_unique<Card>(*cPos, *cSuit, *number);
		}
	}

	DrawFormatString(700, 0, 0xffffff, "score = %d", score);

	DrawString(50, 0, DebugChar, 0xffffff);
}

std::shared_ptr<Card> Board::AddObjList(card_shared && objPtr)
{
	cardList.push_back(objPtr);

	auto itr = cardList.end();
	itr--;
	return *itr;
}

Board::Board()
{
	troutCnt = VECTOR2(BOARD_DEF_TROUT_X, BOARD_DEF_TROUT_Y);
	Resize(troutCnt);
	moveDirection = DIR_RIGHT;
	score = 0;
	pPos = BOARD_START;	
}

Board::Board(VECTOR2 troutCnt)
{
	this->troutCnt = troutCnt;
	Resize(this->troutCnt);
	score = 0;
}


Board::~Board()
{
}

