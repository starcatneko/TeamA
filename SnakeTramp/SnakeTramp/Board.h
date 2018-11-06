#pragma once
#include <memory>
#include <vector>

class Card;

#define BOARD_DEF_TROUT_X		(7)		// Ï½‚ÌÃŞÌ«ÙÄ‚Ì”
#define BOARD_DEF_TROUT_Y		(7)		// Ï½‚ÌÃŞÌ«ÙÄ‚Ì”

class VECTOR2;

class Board
{
public:
	Board();
	Board(VECTOR2 troutCnt);	// ˆø”•t‚«ºİ½Ä×¸ÀÏ½”‚Ìw’è‚ª‚Å‚«‚é

	void PushTrout(void);
private:
	~Board();

	std::vector<std::weak_ptr<Card>*> data;

	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;

};

