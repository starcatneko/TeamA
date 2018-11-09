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
	// �s������(�f�o�b�O�p)
	void Update(Card &card);
	// �s������(Dir�̂�)
	void Update(DIR dir);
	// �`��
	void Draw();
	// ���W�擾
	const VECTOR2 &GetPos() {
		return pos;
	}
	// ���W�i�[
	void SetPos(VECTOR2 pos){
		this->pos = pos;
	}
	// �X�[�g�擾
	const CARD_SUIT &GetSuit() {
		return suit;
	}
	// �X�[�g�i�[
	void SetSuit(CARD_SUIT suit) {
		this->suit = suit;
	}
	// �ԍ��擾
	const int &GetNumber() {
		return number;
	}
	// �ԍ��i�[
	void SetNumber(int number) {
		this->number = number;
	}
	// �����擾
	const DIR &GetDir() {
		return dir;
	}
	// �����i�[
	void SetDir(DIR dir) {
		this->dir = dir;
	}

private:
	// �L�[���
	void Key();
	// �ړ�����
	void Move();
	// �ړ�����(Dir����)
	void Move(DIR dir);
	// �X�[�g�E�����̐؂�ւ�
	void Change(Card & card);
	// �摜�ǂݍ���
	void Load(std::string fileName);
	// �������������E���
	void Reset();

	// �v���C���[�̌��݂̃X�[�g�i���j
	CARD_SUIT suit;
	// �v���C���[�̌��݂̐��l
	int number;
	// �v���C���[�̍��W
	VECTOR2 pos;
	// �v���C���[�̃T�C�Y
	VECTOR2 size;
	// �v���C���[�̃A�j���[�V�����J�E���g
	int animCnt;
	// �v���C���[�̌����Ă������
	DIR dir;
	// �L�[���
	char keyData[256];
	char keyDataOld[256];
	// �摜�n���h��(�g���̂͂̂��̂��ł悢)
	std::vector<int> image;
};

/*
��邱�Ƃ́A�v���C���[���󂯎���������ɐi�߂邩�̊m�F�B
�����Đi�߂�Ȃ�i�ށB
				�Ƃ��������B
*/