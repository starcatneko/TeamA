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
	
	//card = std::make_unique<Card>(VECTOR2{ 2,2 }, SUIT_HEART, 12);
	// board�̃R���X�g���N�^�Ɉ�����n���Ȃ��ꍇ�ABOARD_DEF_TROUT_X��BOARD_DEF_TROUT_Y���n�����
	board = std::make_shared<Board>();
	//player = std::make_unique<Player>(pos,suit,num);
	//player->SetPos(BOARD_START);
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
			int dirVec = 
			Board::SetBoard(Plyaer.Pos+����,stockSuit,stockNum);
		}
	}
	else if(�����L�[����)
	{
	// �ړ��O�̃}�X���ړ��s�}�X�ɂ���
		auto tmp = make_shared<Card>(Player::GetPos(),Player::GetSuit(),0);
		Player::�ړ�(����);
		Board::SetBoard(tmp);
	}
	*/
	board->Update();

	/*
	if(player.pos == BOARD_DEF_GOAL ||
	 Player�̐��l���K��͈͂𒴂���)
	{
		�S�[�����o();
		return std::make_unique<SceneResult>();
	}
	*/


	// ��ʑJ�ڃt���O true:�J�ڏ����J�n
	static bool flg = false;
	if(lpGameTask.PressKey(KEY_INPUT_Z))
	{
		flg = true;
	}
	if (flg == true)
	{
		if (GoalEffect() == true)
		{
			flg = false;
			return std::make_unique<SceneResult>();
		}

	}
	return own;
}

bool SceneMain::Draw()
{
	/*
	 board->�`��(); // card->Draw()
	 lpGameTask.player->�`��();
	*/

	DrawString(0, 0, "Main", 0x888888);	
	return false;
}

bool SceneMain::GoalEffect()
{
	// ���o�̃^�C�}�[
	static UINT timer = 18;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / timer);
	DrawBox(0, 0, 0xfff, 0xfff, 0xffffff, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// �֐����s��A�^�C�}�[��0�ɂȂ����^�C�~���O�ŏ������I���A���̃V�[���ɐ��ڂ�����
	if (timer > 0)
	{
		timer--;
		if (timer == 0)
		{
			timer = 18;
			return true;
		}
	}
	return false;
}