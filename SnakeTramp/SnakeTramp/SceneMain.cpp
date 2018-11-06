#include "GameTask.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "VECTOR2.h"
#include "Dxlib.h"


SceneMain::SceneMain()
{

}


SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// ������Board��unique_ptr������������Ă��Ȃ������ꍇreset������
	if (board) board.reset();

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
	board.get();

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

	DrawString(0, 0, "Main", 0x888888);
	return false;
}
