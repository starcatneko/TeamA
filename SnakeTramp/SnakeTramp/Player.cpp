#include "Player.h"
#include "Card.h"
#include "GameTask.h"
#include "ImgMng.h"

Player::Player(VECTOR2 pos, VECTOR2 size, CARD_SUIT suit, int number)
{
	Reset();
	image.resize(1);
	Load("pl.png");
	this->pos = pos;
	this->size = size;
	this->suit = suit;
	this->number = number;
	dir = DIR_RIGHT;
	animCnt = 0;
}

Player::~Player()
{
	Reset();
}

void Player::Update(Card &card)
{
	Key();
	Move();
	Change(card);
}

void Player::Update(DIR dir)
{
	this->dir = dir;
	Move(dir);
}

void Player::Draw()
{
	VECTOR2 drawpos = pos + DRAW_DISTANCE;

	//if (suit == SUIT_SPADE) DrawString(drawpos.x, drawpos.y - 45, "SPADE", 0xff9e3d);
	//else if (suit == SUIT_CRUB) DrawString(drawpos.x, drawpos.y - 45, "CRUB", 0xff9e3d);
	//else if (suit == SUIT_DIA) DrawString(drawpos.x, drawpos.y - 45, "DIA", 0xff9e3d);
	//else if (suit == SUIT_HEART) DrawString(drawpos.x, drawpos.y - 45, "HEART", 0xff9e3d);

	//DrawFormatString(0/*pos.x*/, 30/*pos.y - 45*/, 0xffffff, "pos.x = %d", pos.x);
	//DrawFormatString(0/*pos.x*/, 45/*pos.y - 30*/, 0xffffff, "pos.y = %d", pos.y);
	//DrawFormatString(drawpos.x, drawpos.y - 30, 0xff9e3d, "%d", number);
	// アニメーションカウント
	if (animCnt >= 0) animCnt++;
	if (animCnt > 38) animCnt = 0;
	// 描画
	DrawRectRotaGraph2(
		drawpos.x + (size.x / 2), drawpos.y + (size.y / 2),
		size.x * (animCnt / 20),size.y * dir,
		size.x,size.y,
		(size.x / 2),(size.y / 2),
		1.0f,0.0f,
		image[0],
		true,false
	);

	DrawBox(drawpos.x, drawpos.y, drawpos.x + size.x, drawpos.y + size.y, 0xff0000, false);
}

void Player::Key()
{
	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);
}

void Player::Move()
{
	// 上
	if (keyData[KEY_INPUT_W] && !keyDataOld[KEY_INPUT_W]) {
		pos.y -= size.y;
		dir = DIR_UP;
	}
	// 右
	if (keyData[KEY_INPUT_D] && !keyDataOld[KEY_INPUT_D]) {
		pos.x += size.x;
		dir = DIR_RIGHT;
	}
	// 下
	if (keyData[KEY_INPUT_S] && !keyDataOld[KEY_INPUT_S]) {
		pos.y += size.y;
		dir = DIR_DOWN;
	}
	// 左
	if (keyData[KEY_INPUT_A] && !keyDataOld[KEY_INPUT_A]) {
		pos.x -= size.x;
		dir = DIR_LEFT;
	}
}

void Player::Move(DIR dir)
{
	//上
	if (dir == DIR_UP) {
		pos.y -= size.y;
		dir = DIR_UP;
	}
	//右
	if (dir == DIR_RIGHT) {
		pos.x += size.x;
		dir = DIR_RIGHT;
	}
	//下
	if (dir == DIR_DOWN) {
		pos.y += size.y;
		dir = DIR_DOWN;
	}
	//左
	if (dir == DIR_LEFT) {
		pos.x -= size.x;
		dir = DIR_LEFT;
	}
}

void Player::Change(Card & card)
{
	// スート切り替え
	if (keyData[KEY_INPUT_E] && !keyDataOld[KEY_INPUT_E]) {
		suit = (CARD_SUIT)(suit + 1);
		if (suit > (CARD_SUIT)(SUIT_NUM - 1)) suit = SUIT_SPADE;
	}
	card.SetSuit(suit);

	// 数字切り替え
	if (keyData[KEY_INPUT_Q] && !keyDataOld[KEY_INPUT_Q]) {
		number += 1;
		if (number > 13) number = 1;
	}
	card.SetNum(number);
}

void Player::Load(std::string fileName)
{
	image[0] = lpImgMng.Load("../Assets/Image/" + fileName);
}

void Player::Reset()
{
	std::vector<int>().swap(image);
}
