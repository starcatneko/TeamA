#include "Player.h"
#include "Card.h"
#include "GameTask.h"
#include "ImgMng.h"

Player::Player(VECTOR2 pos, VECTOR2 size, CARD_SUIT suit, int number)
{
	Reset();
	image.resize(1);
	Load("Reimu.png");
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

void Player::Update()
{
	Key();
	Move();
}

void Player::Draw()
{
	if (suit == SUIT_SPADE) DrawString(pos.x, pos.y - 45, "SPADE", 0xff9e3d);
	else if (suit == SUIT_CRUB) DrawString(pos.x, pos.y - 45, "CRUB", 0xff9e3d);
	else if (suit == SUIT_DIA) DrawString(pos.x, pos.y - 45, "DIA", 0xff9e3d);
	else if (suit == SUIT_HEART) DrawString(pos.x, pos.y - 45, "HEART", 0xff9e3d);

	DrawFormatString(0/*pos.x*/, 30/*pos.y - 45*/, 0xffffff, "pos.x = %d", pos.x);
	DrawFormatString(0/*pos.x*/, 45/*pos.y - 30*/, 0xffffff, "pos.y = %d", pos.y);
	DrawFormatString(pos.x,pos.y - 30, 0xff9e3d, "%d", number);

	if (animCnt >= 0) animCnt++;
	if (animCnt > 38) animCnt = 0;

	DrawRectRotaGraph2(
		pos.x + (size.x / 2), pos.y + (size.y / 2),
		size.x * (animCnt / 20),size.y * dir,
		size.x,size.y,
		(size.x / 2),(size.y / 2),
		1.0f,0.0f,
		image[0],
		true,false
	);

	DrawBox( pos.x, pos.y, pos.x + size.x, pos.y + size.y, 0xff0000, false);
}

void Player::Key()
{
	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);
}

void Player::Move()
{
	// è„
	if (keyData[KEY_INPUT_W] && !keyDataOld[KEY_INPUT_W]) {
		pos.y -= size.y;
		dir = DIR_UP;
	}
	// âE
	if (keyData[KEY_INPUT_D] && !keyDataOld[KEY_INPUT_D]) {
		pos.x += size.x;
		dir = DIR_RIGHT;
	}
	// â∫
	if (keyData[KEY_INPUT_S] && !keyDataOld[KEY_INPUT_S]) {
		pos.y += size.y;
		dir = DIR_DOWN;
	}
	// ç∂
	if (keyData[KEY_INPUT_A] && !keyDataOld[KEY_INPUT_A]) {
		pos.x -= size.x;
		dir = DIR_LEFT;
	}
}

void Player::Load(std::string fileName)
{
	image[0] = lpImgMng.Load("../Assets/Image/" + fileName);
}

void Player::Reset()
{
	std::vector<int>().swap(image);
}
