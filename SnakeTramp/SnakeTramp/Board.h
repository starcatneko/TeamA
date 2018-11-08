#pragma once
#include <memory>
#include <vector>
#include "VECTOR2.h"

class Card;

#define BOARD_DEF_TROUT_X		(7)		// ﾏｽのﾃﾞﾌｫﾙﾄの数
#define BOARD_DEF_TROUT_Y		(7)		// ﾏｽのﾃﾞﾌｫﾙﾄの数

#define BOARD_START				(VECTOR2(0,0))	// ﾌﾟﾚｲﾔｰのｽﾀｰﾄ位置
#define BOARD_DEF_GOAL			((VECTOR2(BOARD_DEF_TROUT_X + 1,BOARD_DEF_TROUT_Y))

#define TROUT_SIZE				(60)	// ﾏｽのｻｲｽﾞ


class Board
{
public:
	Board();
	~Board();
	Board(VECTOR2 troutCnt);	// 引数付きｺﾝｽﾄﾗｸﾀﾏｽ数の指定ができる
	void Update(void);

	void PushTrout(void);
private:

	std::vector<std::weak_ptr<Card>*> data;

	bool CheckBoard(VECTOR2 pos, int moveDirection);

	bool changeFlag;

	VECTOR2 troutCnt;

	VECTOR2 pPos;		// ﾌﾟﾚｲﾔｰのPos
	VECTOR2 ckPos;		// 移動する予定のPos

	int moveDirection;

	const TCHAR *DebugChar = "右";		// ﾃﾞﾊﾞｯｸﾞ用文字列

};

