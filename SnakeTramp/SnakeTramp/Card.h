#pragma once

// �J�[�h�̃X�[�g�i���j�p
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
	// �J�[�h�̃X�[�g�i���j
	CARD_SUIT suit;
	// �J�[�h�̐��l 1~13�͈͓̔�
	int number;
	
};

