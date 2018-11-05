#pragma once

enum CARD_SUIT;

class Player
{
public:
	Player();
	~Player();

	// プレイヤーの現在のスート（柄）
	CARD_SUIT suit;
	// プレイヤーの現在の数値
	int number;


};

