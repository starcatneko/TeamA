#pragma once
#include <memory>
#include <vector>
#include <list>
#include "VECTOR2.h"
#include "Card.h"



using namespace std;

using card_weak = weak_ptr<Card>;
using card_weakList = list<card_weak>;

using  card_shared = shared_ptr<Card>;
using  card_sharedList = list<card_shared>;

using cardST_unique = unique_ptr<Card>;
using cardST_uniqueList = list<cardST_unique>;



class Board
{
public:
	Board();
	~Board();
	Board(VECTOR2 troutCnt);	// 引数付きｺﾝｽﾄﾗｸﾀﾏｽ数の指定ができる
	void Update(void);

	void SetBoard(card_shared card);
	card_weak GetBoard(VECTOR2 pos);

	CARD_SUIT GetSuit(VECTOR2 pos);
	int GetNumber(VECTOR2 pos);

	void PushTrout(void);
	void Draw(void);

	int score;
	std::shared_ptr<Card> AddObjList(card_shared && objPtr);
private:

	vector<std::weak_ptr<Card>*> data;
	vector<std::weak_ptr<Card>> baseData;

	bool CheckBoard(VECTOR2 pos, int moveDirection);
	bool Resize(VECTOR2 vec);

	VECTOR2 troutCnt;
	VECTOR2 pPos;		// ﾌﾟﾚｲﾔｰのPos
	VECTOR2 ckPos;		// 移動する予定のPos
	VECTOR2 screenSize;
	VECTOR2 boardSize;
	VECTOR2 boardLT;

	card_shared card;

	card_sharedList cardList;
	cardST_uniqueList suit;


	int moveDirection;

	const TCHAR *DebugChar = "右";		// ﾃﾞﾊﾞｯｸﾞ用文字列
};

