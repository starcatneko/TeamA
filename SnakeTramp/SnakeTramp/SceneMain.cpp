#include "GameTask.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "VECTOR2.h"
#include "Dxlib.h"

#include "Card.h"
#include "Player.h"

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
	
	// board�̃R���X�g���N�^�Ɉ�����n���Ȃ��ꍇ�ABOARD_DEF_TROUT_X��BOARD_DEF_TROUT_Y���n�����
	board = std::make_shared<Board>();
	// player(�������W, �����T�C�Y, ���������X�[�g, ������������)
	player = std::make_unique<Player>( BOARD_START, VECTOR2( TROUT_SIZE, TROUT_SIZE), SUIT_SPADE, 1);
	// card�̐���
	card = std::make_unique<Card>(VECTOR2( 0, 100), player->GetSuit(), player->GetNumber());

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
	// player�̋�������
	player->Update();

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
	player->Draw();
	//(*card).Draw();
	card->Draw();

	DrawString(0, 0, "Main", 0x888888);
	
	return false;
}
