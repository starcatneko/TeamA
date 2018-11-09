#pragma once
#include "VECTOR2.h"
#include <string>
#include <vector>

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
	// �����t���R���X�g���N�^�@���g��Ȃ��悤�Ȃ�����Ă�������
	Card(VECTOR2 pos,CARD_SUIT suit,int number);
	~Card();
	// �C�����C���W�J�̂ق��������������̂Ŏg�p
	// �X�[�g�擾
	const CARD_SUIT &GetSuit() {
		return suit;
	}
	// �X�[�g�i�[
	void SetSuit(CARD_SUIT suit) {
		this->suit = suit;
	}
	// �ԍ��擾
	const int &GetNum() {
		return number;
	}
	// �ԍ��i�[
	void SetNum(int number) {
		this->number = number;
	}
	// ���W�擾
	const VECTOR2 &GetPos() {
		return pos;
	}
	// ���W�i�[
	void SetPos(VECTOR2 pos) {
		this->pos = pos;
	}
	// �`��
	void Draw();

private:
	// �摜�̓ǂݍ���
	void Load(std::string fileName);
	// �����̐F(�f�o�b�O�p)
	unsigned int SetColor(CARD_SUIT suit);
	// �ϐ��̏������E���
	void Reset() {
		std::vector<int>().swap(image);
	}

	// �J�[�h�̃X�[�g�i���j
	CARD_SUIT suit;
	// �J�[�h�̐��l 1~13�͈͓̔�
	int number;
	// �J�[�h�̍��W
	VECTOR2 pos;
	// �����̐F(�f�o�b�O�p)
	unsigned int color;
	// �摜�n���h��
	std::vector<int> image;
};

