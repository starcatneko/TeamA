#pragma once

#define BOARD_DEF_TROUT_X		(7)		// ﾏｽのﾃﾞﾌｫﾙﾄの数
#define BOARD_DEF_TROUT_Y		(7)		// ﾏｽのﾃﾞﾌｫﾙﾄの数

class VECTOR2;

class Board
{
public:
	Board(bool defFlag, VECTOR2 troutCnt);
	VECTOR2 BoardTrout();			// ﾎﾞｰﾄﾞのﾏｽ数を変更したいならここから
private:
	~Board();
	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;

};

