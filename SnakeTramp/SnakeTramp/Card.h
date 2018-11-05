#pragma once

// カードのスート（柄）用
enum CARD_SUIT {
	SUIT_SPADE,
	SUIT_CRUB,
	SUIT_DIA,
	SUIT_HEART,
	SUIT_NUM
};

class Card
{
public:
	Card();
	~Card();
private:
	// カードのスート（柄）
	CARD_SUIT suit;
	// カードの数値 1~13の範囲内
	int number;
	
};

