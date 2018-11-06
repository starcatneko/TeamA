#include "GameTask.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "VECTOR2.h"
#include "Dxlib.h"

#include "Card.h"

#include <memory>


SceneMain::SceneMain()
{
	Init();
}
SceneMain::~SceneMain()
{
}
void SceneMain::Init()
{
	// ������Board��unique_ptr������������Ă��Ȃ������ꍇreset������
	if (board) board.reset();
	
	//card = std::make_unique<Card>(VECTOR2{ 2,2 }, SUIT_HEART, 12);
	// board�̃R���X�g���N�^�Ɉ�����n���Ȃ��ꍇ�ABOARD_DEF_TROUT_X��BOARD_DEF_TROUT_Y���n�����
	board = std::make_shared<Board>();
	

	//�ՖʁAPlayer������������
}

Scene SceneMain::Update(Scene own)
{
	/*
	// 1�`3�̂����ꂩ�̃L�[�������Ȃ�������L�[�����������ɁA
	// ���͂��ꂽ�����ɓ��͂��ꂽ�ԍ��̃X�g�b�N�̃J�[�h��ݒu����
	if (1~3�̂����ꂩ�����͒�)
	{
		if(�����L�[����)
		{
			Board::�X�g�b�N�ݒu(����,�X�g�b�N�̔ԍ�);
		}
	}
	else if(�����L�[����)
	{
		Player::�ړ�(����);
	}
	*/
	board->Update();

	// if(Player���S�[���ɂ��ǂ蒅�� ||
	// Player�̐��l���K��͈͂𒴂���)

	if(lpGameTask.PressKey(KEY_INPUT_Z))
	{
		return std::make_unique<SceneResult>();
	}
	return own;
}

bool SceneMain::Draw()
{
	// Board::�`��();
	// Player::�`��();
	//(*card).Draw();
	DrawString(0, 0, "Main", 0x888888);
	
	return false;
}
