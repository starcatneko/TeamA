#pragma once
#include <memory>
#include <vector>

class Card;

#define BOARD_DEF_TROUT_X		(7)		// Ï½‚ÌÃŞÌ«ÙÄ‚Ì”
#define BOARD_DEF_TROUT_Y		(7)		// Ï½‚ÌÃŞÌ«ÙÄ‚Ì”

#define BOARD_START				(VECTOR2(0,0))	// ÌßÚ²Ô°‚Ì½À°ÄˆÊ’u
#define BOARD_DEF_GOAL			((VECTOR2(BOARD_DEF_TROUT_X + 1,BOARD_DEF_TROUT_Y))

class VECTOR2;

class Board
{
public:
	Board();
	Board(VECTOR2 troutCnt);	// ˆø”•t‚«ºİ½Ä×¸ÀÏ½”‚Ìw’è‚ª‚Å‚«‚é
	void Update(void);

	void PushTrout(void);
private:
	~Board();

	std::vector<std::weak_ptr<Card>*> data;

	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;

	VECTOR2 pPos;		// ÌßÚ²Ô°‚ÌPos
	VECTOR2 ckPos;		// ˆÚ“®‚·‚é—\’è‚ÌPos

	int moveDirection;

};

