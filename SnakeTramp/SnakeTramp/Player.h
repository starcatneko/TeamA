#pragma once

enum CARD_SUIT;

class Player
{
public:
	Player();
	~Player();

	// �v���C���[�̌��݂̃X�[�g�i���j
	CARD_SUIT suit;
	// �v���C���[�̌��݂̐��l
	int number;


};

