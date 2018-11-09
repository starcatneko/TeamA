#pragma once
#include "VECTOR2.h"
#include <string>
#include <vector>

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
	// 引数付きコンストラクタ　※使わないようなら消してください
	Card(VECTOR2 pos,CARD_SUIT suit,int number);
	~Card();
	// インライン展開のほうが処理が速いので使用
	// スート取得
	const CARD_SUIT &GetSuit() {
		return suit;
	}
	// スート格納
	void SetSuit(CARD_SUIT suit) {
		this->suit = suit;
	}
	// 番号取得
	const int &GetNum() {
		return number;
	}
	// 番号格納
	void SetNum(int number) {
		this->number = number;
	}
	// 座標取得
	const VECTOR2 &GetPos() {
		return pos;
	}
	// 座標格納
	void SetPos(VECTOR2 pos) {
		this->pos = pos;
	}
	// 描画
	void Draw();

private:
	// 画像の読み込み
	void Load(std::string fileName);
	// 文字の色(デバッグ用)
	unsigned int SetColor(CARD_SUIT suit);
	// 変数の初期化・解放
	void Reset() {
		std::vector<int>().swap(image);
	}

	// カードのスート（柄）
	CARD_SUIT suit;
	// カードの数値 1~13の範囲内
	int number;
	// カードの座標
	VECTOR2 pos;
	// 文字の色(デバッグ用)
	unsigned int color;
	// 画像ハンドル
	std::vector<int> image;
};

