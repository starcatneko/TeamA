#include "Card.h"
#include "ImgMng.h"
#include "DxLib.h"

Card::Card()
{
	Reset();
	//image.resize(1);	// vector�̎g�p�͈͂�w��
	pos = { 0,0 };
	suit = SUIT_NUM;
	number = 0;
}

Card::Card(VECTOR2 pos, CARD_SUIT suit, int number)
{
	Reset();
	//image.resize(1);	// vector�̎g�p�͈͂�w��
	//Load("");			// �ǂݍ��މ摜���Ȃ����߁A�킴�Ƌ󔒂ɂ��Ă���
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
	int num = 0;
	// �G��
	if (suit == SUIT_SPADE) DrawString(pos.x, pos.y, "�X�y�[�h ", SetColor(suit));
	else if (suit == SUIT_CRUB) DrawString(pos.x, pos.y, "�N���u", SetColor(suit));
	else if (suit == SUIT_DIA) DrawString(pos.x, pos.y, "�_�C�A", SetColor(suit));
	else if (suit == SUIT_HEART) DrawString(pos.x, pos.y, "�n�[�g", SetColor(suit));
	// �ԍ�
	if (suit == SUIT_SPADE) num = 80;
	else num = 60;
	DrawFormatString(pos.x + num, pos.y, SetColor(suit),"%d",number);
}

void Card::Load(std::string fileName)
{
	//image = lpImgMng.GetID(fileName + ".png");
}

unsigned int Card::SetColor(CARD_SUIT suit)
{
	// �ȒP�ɃX�[�g��ĐF��ς���
	if (suit == SUIT_SPADE || suit == SUIT_CRUB) color = 0x000000;
	else if (suit == SUIT_DIA || suit == SUIT_HEART) color = 0xff0000;
	return color;
}
