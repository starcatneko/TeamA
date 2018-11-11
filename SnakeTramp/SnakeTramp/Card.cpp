#include "Card.h"
#include "ImgMng.h"
#include "GameTask.h"
#include "DxLib.h"

Card::Card()
{
	Reset();
	image.resize(1);			// vectorの使用範囲を指定
	Load("trump.png");			// 読み込む画像がないため、わざと空白にしている
	pos = { 0,0 };
	suit = SUIT_NUM;
	number = 0;
}

Card::Card(VECTOR2 pos, CARD_SUIT suit, int number)
{
	Reset();
	image.resize(1);	// vectorの使用範囲を指定
	Load("trump.png");			// 読み込む画像がないため、わざと空白にしている
	this->pos = pos;
	this->suit = suit;
	this->number = number;
}

Card::~Card()
{
	Reset();
}

void Card::Draw()
{
	// カードのサイズ
	VECTOR2 size = {50,75};
	int num = 0;
	// 絵柄
	/*
	if (suit == SUIT_SPADE) DrawString(pos.x, pos.y, "スペード ", SetColor(suit));
	else if (suit == SUIT_CRUB) DrawString(pos.x, pos.y, "クラブ", SetColor(suit));
	else if (suit == SUIT_DIA) DrawString(pos.x, pos.y, "ダイア", SetColor(suit));
	else if (suit == SUIT_HEART) DrawString(pos.x, pos.y, "ハート", SetColor(suit));
	*/
	// 番号
	if (suit == SUIT_SPADE) num = 80;
	else num = 60;
	DrawFormatString(pos.x + num, pos.y, SetColor(suit),"%d",number);
	// 画像
	DrawRectRotaGraph2(
		pos.x * 60 + (size.x / 2) + DRAW_DISTANCE.x,pos.y * 60 + (size.y / 2) + DRAW_DISTANCE.y,
		size.x * (CARD_SUIT)(suit - 1), size.y * (number - 1),
		size.x,size.y,
		(size.x / 2),(size.y / 2),
		1.0f,0.0f,
		image[0],
		true,false
	);
}

void Card::Load(std::string fileName)
{
	image[0] = lpImgMng.Load("../Assets/Image/" + fileName);
}

unsigned int Card::SetColor(CARD_SUIT suit)
{
	// 簡単にスートを見て色を変える
	if (suit == SUIT_SPADE || suit == SUIT_CRUB) color = 0x000000;
	else if (suit == SUIT_DIA || suit == SUIT_HEART) color = 0xff0000;
	return color;
}
