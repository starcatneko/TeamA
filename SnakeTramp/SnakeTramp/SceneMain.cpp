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
	


	// �ՖʂɃJ�[�h����
	for (int y = 0; y < BOARD_DEF_TROUT_Y; y++)
	{
		for (int x = 0; x < BOARD_DEF_TROUT_X; x++)
		{
			if (x == 0)
			{
				std::shared_ptr<Card> tmp = board->AddObjList(make_shared<Card>(VECTOR2{ x,y },SUIT_NON, 0));
				board->SetBoard(tmp);
				continue;
			}


			int num = GetRand(12)+1;
			CARD_SUIT suit = CARD_SUIT(GetRand(3) + 1);

			if (x < 2 && y <= 1)
			{
				while (num < 5)
				{
					num = GetRand(12)+1;
				}
			}

			if (board->GetNumber(VECTOR2{ x - 1,y }) + num > 18)
			{
				num = GetRand(5) + 1;
			}
			// �󋵂Œ���

			if (y > 0)
			{
				if ((board->GetSuit(VECTOR2{ x ,y - 1 }) != suit)&&
					(board->GetSuit(VECTOR2{ x -1,y  }) != suit))
				{
					suit = CARD_SUIT(GetRand(3) + 1);
					x -= 1;
				}
			
			}
			

			std::shared_ptr<Card> tmp = board->AddObjList(make_shared<Card>(VECTOR2{ x,y }, suit, num));
			board->SetBoard(tmp);

		}
	}

	Goalflg = false;
}

bool SceneMain::SetStock()
{
	// 1�`3�̂����ꂩ�̃L�[�������Ȃ�������L�[�����������ɁA
	// ���͂��ꂽ�����ɓ��͂��ꂽ�ԍ��̃X�g�b�N�̃J�[�h��ݒu����
	VECTOR2 sarchTBL[4] = { { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 } };

	int stock_num = 0;

	if (CheckHitKey(KEY_INPUT_1)) stock_num = 1;
	if (CheckHitKey(KEY_INPUT_2)) stock_num = 2;
	if (CheckHitKey(KEY_INPUT_3)) stock_num = 3;

	if (stock_num != 0)
	{
		if (lpGameTask.PressKey(KEY_INPUT_UP))
		{
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_UP], SUIT_DIA, 8)));
			return true;
		}
		if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
		{
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_RIGHT], SUIT_DIA, 8)));
			return true;
		}
		if (lpGameTask.PressKey(KEY_INPUT_DOWN))
		{
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_DOWN], SUIT_DIA, 8)));
			return true;
		}
		if (lpGameTask.PressKey(KEY_INPUT_LEFT))
		{
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_LEFT], SUIT_DIA, 8)));
			return true;
		}
	}
	return false;
}

Scene SceneMain::Update(Scene own)
{
	// �X�g�b�N���삪�s���Ȃ��ꍇ�A�v���C���[����̔��������
	if (!SetStock())
	{
		PlayerMove();
	}
	
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
	Goalflg = false;
	if(lpGameTask.PressKey(KEY_INPUT_Z))
	{
		Goalflg = true;
	}
	if (Goalflg == true)
	{
		if (GoalEffect() == true)
		{
			Goalflg = false;
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

	for (int y = 0; y < BOARD_DEF_TROUT_Y; y++)
	{
		for (int x = 0; x < BOARD_DEF_TROUT_X; x++)
		{
			
				auto tmp = (board->GetBoard(VECTOR2{ x,y }));
				tmp.lock()->Draw();
				int color = (tmp.lock()->GetSuit() <= SUIT_CRUB ? 0xffffff : 0xff0000);


				DrawFormatString(tmp.lock()->GetPos().x * 60 + DRAW_DISTANCE.x,
					tmp.lock()->GetPos().y * 60 + DRAW_DISTANCE.y, color, "%d", tmp.lock()->GetNum());
				DrawFormatString(tmp.lock()->GetPos().x * 60 + DRAW_DISTANCE.x+32,
					tmp.lock()->GetPos().y * 60 + DRAW_DISTANCE.y+32, color, "%d", tmp.lock()->GetSuit());
			
		}
	}

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

void SceneMain::PlayerMove()
{
	VECTOR2 sarchTBL[4] = { {0,-1},{ 1,0 },{ 0,1 },{ -1,0 } };
	VECTOR2 vec = { -1,-1 };
	DIR tmp_dir;
	if (lpGameTask.PressKey(KEY_INPUT_W))
	{
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 ,player->GetPos().y / 60 - 1 }).expired()
			|| (player->GetPos().y / 60 - 1 < 0)) return ;
		vec = sarchTBL[DIR_UP];
		tmp_dir = DIR_UP;
	}
	if (lpGameTask.PressKey(KEY_INPUT_D))
	{
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 + 1,player->GetPos().y / 60 }).expired()
		||(player->GetPos().x / 60 + 1 > BOARD_DEF_TROUT_X)) return ;
		vec = sarchTBL[DIR_RIGHT];
		tmp_dir = DIR_RIGHT;
	}
	if (lpGameTask.PressKey(KEY_INPUT_S))
	{
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 ,player->GetPos().y / 60 + 1 }).expired() 
			|| (player->GetPos().y / 60 + 1> BOARD_DEF_TROUT_Y - 1)) return ;
		vec = sarchTBL[DIR_DOWN];
		tmp_dir = DIR_DOWN;
	}
	if (lpGameTask.PressKey(KEY_INPUT_A))
	{
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 - 1,player->GetPos().y / 60 }).expired() 
			|| (player->GetPos().x / 60 - 1< 0)) return ;
		vec = sarchTBL[DIR_LEFT];
		tmp_dir = DIR_LEFT;
	}
	if (vec == VECTOR2{-1, -1}) return;
	// �ړ��O�̃}�X���ړ��s�}�X�ɂ���
	// auto tmp = make_shared<Card>(player->GetPos(),,0);
	//AddObjList(tmp);
	// board->SetBoard(tmp);

	VECTOR2 tmp_pos = player->GetPos()/60 + vec;

	int  tmp_num = board->GetNumber(tmp_pos);
	CARD_SUIT tmp_suit = board->GetSuit(tmp_pos);

	// �X�[�g����
	if (tmp_suit == SUIT_NON)
	{
		return;
	}

	if (tmp_suit == player->GetSuit())
	{
		tmp_num *= 2;
	}
	if (tmp_suit <= SUIT_CRUB)
	{
		// SUIT������
		tmp_num = tmp_num;
	}
	else
	{
		// SUIT���Ԏ�
		tmp_num = -tmp_num;
	}

	//	board->GetNumber(player->GetPos() / 60) + player->GetNumber()
	//(board->GetSuit(
	player->SetNumber(player->GetNumber()+ tmp_num);
	player->SetSuit(tmp_suit);
	player->Update(tmp_dir);


	board->SetBoard(board->AddObjList(make_shared<Card>(tmp_pos, SUIT_NON, 0)));

}
