#pragma once
#include "VECTOR2.h"
#include <vector>
#include <string>

enum CARD_SUIT;
enum DIR;

class Card;
class Board;

class Player
{
public:
	Player( VECTOR2 pos, VECTOR2 size, CARD_SUIT suit, int number);
	~Player();
	// 行動制御(デバッグ用)
	void Update(Card &card);
	// 行動制御(Dirのみ)
	void Update(DIR dir);
	// 描画
	void Draw();
	// 座標取得
	const VECTOR2 &GetPos() {
		return pos;
	}
	// 座標格納
	void SetPos(VECTOR2 pos){
		this->pos = pos;
	}
	// スート取得
	const CARD_SUIT &GetSuit() {
		return suit;
	}
	// スート格納
	void SetSuit(CARD_SUIT suit) {
		this->suit = suit;
	}
	// 番号取得
	const int &GetNumber() {
		return number;
	}
	// 番号格納
	void SetNumber(int number) {
		this->number = number;
	}
	// 方向取得
	const DIR &GetDir() {
		return dir;
	}
	// 方向格納
	void SetDir(DIR dir) {
		this->dir = dir;
	}

private:
	// キー情報
	void Key();
	// 移動処理
	void Move();
	// 移動処理(Dir制御)
	void Move(DIR dir);
	// スート・数字の切り替え
	void Change(Card & card);
	// 画像読み込み
	void Load(std::string fileName);
	// メモリ初期化・解放
	void Reset();

	// プレイヤーの現在のスート（柄）
	CARD_SUIT suit;
	// プレイヤーの現在の数値
	int number;
	// プレイヤーの座標
	VECTOR2 pos;
	// プレイヤーのサイズ
	VECTOR2 size;
	// プレイヤーのアニメーションカウント
	int animCnt;
	// プレイヤーの向いている方向
	DIR dir;
	// キー情報
	char keyData[256];
	char keyDataOld[256];
	// 画像ハンドル(使うのはのちのちでよい)
	std::vector<int> image;
};

/*
やることは、プレイヤーが受け取った方向に進めるかの確認。
そして進めるなら進む。
				という処理。
*/