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

	for (int x = 1; x < BOARD_DEF_TROUT_X; x++)
	{
		for (int y = 0; y < BOARD_DEF_TROUT_Y; y++)
		{
			int num = GetRand(13);
			CARD_SUIT suit = CARD_SUIT(GetRand(3) + 1);

			if (x < 2 && y <= 1)
			{
				while (num < 5)
				{
					num = GetRand(12)+1;
				}
			}
			std::shared_ptr<Card> tmp = board->AddObjList(make_shared<Card>(VECTOR2{ x,y }, suit, num));

			board->SetBoard(tmp);

		}
	}
	//player = std::make_unique<Player>(pos,suit,num);
	//player->SetPos(BOARD_START);
	//�ՖʁAPlayer������������
}

Scene SceneMain::Update(Scene own)
{
	//card_u->Draw();
	
	// 1�`3�̂����ꂩ�̃L�[�������Ȃ�������L�[�����������ɁA
	// ���͂��ꂽ�����ɓ��͂��ꂽ�ԍ��̃X�g�b�N�̃J�[�h��ݒu����
	if (CheckHitKey(KEY_INPUT_1) ||
		CheckHitKey(KEY_INPUT_2) ||
		CheckHitKey(KEY_INPUT_3))
	{
		if(lpGameTask.PressKey(
			KEY_INPUT_UP ||
			KEY_INPUT_RIGHT ||
			KEY_INPUT_DOWN ||
			KEY_INPUT_LEFT))
		{
			// auto dirVec[] = { {0,-1},{1,0},{0,1},{-1,0} };
			//Board::SetBoard(Plyaer.Pos+����,stockSuit,stockNum);
		}
	}
	
	else if(lpGameTask.PressKey(KEY_INPUT_W) ||
		lpGameTask.PressKey(KEY_INPUT_D) ||
		lpGameTask.PressKey(KEY_INPUT_S) ||
		lpGameTask.PressKey(KEY_INPUT_A))
	{
	// �ړ��O�̃}�X���ړ��s�}�X�ɂ���
		// auto tmp = make_shared<Card>(player->GetPos(),,0);
		 //AddObjList(tmp);
		
		// board->SetBoard(tmp);


		player->SetSuit(board->GetSuit(player->GetPos() / 60));
		player->SetNumber(board->GetNumber(player->GetPos() / 60));
	}
	
	board->Update();
	// player�̋�������
	//player->Update(*card_u);

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

	for (int x = 1; x < BOARD_DEF_TROUT_X; x++)
	{
		for (int y = 1; y < BOARD_DEF_TROUT_Y; y++)
		{
			/*
					auto tmp = (board->GetBoard(VECTOR2{ x,y }));
					tmp.lock()->Draw();
					*/
		}
	}
	if(!card.expired())card.lock()->Draw();

	DrawString(0, 0, "Main", 0x888888);	
	// Board::�`��();
	// Player::�`��();
	player->Draw();
	//(*card).Draw();
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