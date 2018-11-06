#pragma once

#define BOARD_DEF_TROUT_X		(7)		// Ï½‚ÌÃŞÌ«ÙÄ‚Ì”
#define BOARD_DEF_TROUT_Y		(7)		// Ï½‚ÌÃŞÌ«ÙÄ‚Ì”

class VECTOR2;

class Board
{
public:
	Board(bool defFlag, VECTOR2 troutCnt);
	VECTOR2 BoardTrout();			// ÎŞ°ÄŞ‚ÌÏ½”‚ğ•ÏX‚µ‚½‚¢‚È‚ç‚±‚±‚©‚ç
private:
	~Board();
	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;
	
};

