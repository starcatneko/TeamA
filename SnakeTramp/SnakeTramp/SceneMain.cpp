#include "GameTask.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "VECTOR2.h"
#include "Dxlib.h"
#include "Card.h"
#include "Player.h"
#include "ImgMng.h"

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
	lpGameTask.TimerReset();
	// ������Board��unique_ptr������������Ă��Ȃ������ꍇreset������
	if (board) board.reset();
	// board�̃R���X�g���N�^�Ɉ�����n���Ȃ��ꍇ�ABOARD_DEF_TROUT_X��BOARD_DEF_TROUT_Y���n�����
	board = std::make_shared<Board>();
	// player(�������W, �����T�C�Y, ���������X�[�g, ������������)
	player = std::make_unique<Player>( BOARD_START, VECTOR2( TROUT_SIZE, TROUT_SIZE), SUIT_SPADE, 10);
	
	PLcard = std::make_shared<Card>(VECTOR2{ -2,1 }, player->GetSuit(), 1);

	image.resize(2);
	flag = false;
	image[0] = ImgMng::GetInstance().Load("../Assets/Image/Panel.png");
	image[1] = ImgMng::GetInstance().Load("../Assets/Image/����.png");

	// �ՖʂɃJ�[�h����
	for (int y = 0; y < BOARD_DEF_TROUT_Y; y++)
	{
		for (int x = 0; x < BOARD_DEF_TROUT_X; x++)
		{

			if (x == 0 || x == BOARD_DEF_TROUT_X-1)
			{
				std::shared_ptr<Card> tmp = board->AddObjList(make_shared<Card>(VECTOR2{ x,y },SUIT_NON, 0));
				board->SetBoard(tmp);
				continue;
			}

			
			int num = ((y*x + x)%2 == 0? GetRand(12)+1:GetRand(7) + 1);

			CARD_SUIT suit = CARD_SUIT((y*x + x) % 2 == 0 ? GetRand(2) + 1: GetRand(2) + 2);
			if (x <= 2 && y <= 1)
			{
				while (num > 5)
				{
					num = GetRand(5)+1;
				}
			}

			if (board->GetNumber(VECTOR2{ x - 1,y }) + num > 18)
			{
				num = GetRand(5) + 1;
			}
			// �󋵂Œ���
			/*
			if (y > 0)
			{
				if ((board->GetSuit(VECTOR2{ x ,y - 1 }) != suit)&&
					(board->GetSuit(VECTOR2{ x -1,y  }) != suit))
				{
					suit = CARD_SUIT(GetRand(3) + 1);
				}
			}
			
			*/
			std::shared_ptr<Card> tmp = board->AddObjList(make_shared<Card>(VECTOR2{ x,y }, suit, num));
			board->SetBoard(tmp);

		}
	}
	
	for (int i = 0; i < STOCK_NUM; i++)
	{
		stock[i] = board->AddObjList(make_shared<Card>(VECTOR2{ BOARD_DEF_TROUT_X, i*2 }, CARD_SUIT(GetRand(3) + 1), GetRand(12) + 1));
	}

	std::shared_ptr<Card> tmp = board->AddObjList(make_shared<Card>(BOARD_DEF_GOAL, SUIT_SPADE, 0));
	board->SetBoard(tmp);
	Goalflg = false;
}


Scene SceneMain::Update(Scene own)
{
	Key();
	// �Q�[���I�[�o�[
	if (player->GetNumber() <= 0 || player->GetNumber() >= 22)
	{
		if (lpGameTask.Timer("gameover", 25) == 0)
		{
			board->SetBoard(board->AddObjList(make_shared<Card>(VECTOR2{ 0,0 }, SUIT_NON, 13)));
			return std::make_unique<SceneResult>(board);
		}
		return own;
	}

	// �X�g�b�N���삪�s���Ȃ��ꍇ�A�v���C���[����̔��������
	if (!SetStock())
	{
		PlayerMove();
	}
	
	board->Update();

	
	if(player->GetPos() == BOARD_DEF_GOAL*60){
		//�S�[�����o();
		Goalflg = true;
	}
	


	// ��ʑJ�ڃt���O true:�J�ڏ����J�n
	if(lpGameTask.PressKey(KEY_INPUT_Z))
	{
		Goalflg = true;
	}
	if (Goalflg == true)
	{
		if (lpGameTask.Timer("goalfill") == 0)
		{
			if (lpGameTask.Timer("goalwait", 15) == 0)
			{
				Goalflg = false;
				return std::make_unique<SceneResult>(board);
			}
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
	
	// �n�܂�ƏI�������o��
	{
		// �X�^�[�g
		VECTOR2 bPos = { 160,120 };
		int size = 60;
		DrawRectRotaGraph2(
			bPos.x + (size/ 2), bPos.y + (size / 2),
			0,0,
			size,size,
			(size / 2),(size / 2),
			1.0f, 0.0f,
			image[0],
			true,false
		);
		// �S�[��
		DrawRectRotaGraph2(
			(bPos.x + (60 * 8)) + (size / 2), (bPos.y + (60 * 6)) + (size / 2),
			size, 0,
			size, size,
			(size / 2), (size / 2),
			1.0f, 0.0f,
			image[0],
			true, false
		);
	}

	// ��D�w�i
	{
		VECTOR2 pos = { 675,95 };
		VECTOR2 size = { 110,350 };
		DrawBox(pos.x, pos.y - 30, pos.x + size.x, pos.y + size.y, 0x898989, true); // 675,65 // 785,445
		DrawBox(pos.x + 15, pos.y + 15, (pos.x + size.x) - 15, (pos.y + size.y) - 15, 0x606060, true); // 690, 110 // 760,430
		DrawBox( 700, 120, 700 + 60, 120 + 60, 0x3b3c3d, true); // �ꖇ�ڎg�p�ς�
		DrawBox( 700, 240, 700 + 60, 240 + 60, 0x3b3c3d, true); // �񖇖ڎg�p�ς�
		DrawBox( 700, 360, 700 + 60, 360 + 60, 0x3b3c3d, true); // �O���ڎg�p�ς�
		DrawString( pos.x + 3, pos.y - 12, "Player�̎�D", 0xffffff);
	}

	// �����̏�
	{
		VECTOR2 pos = { 15, 100};
		VECTOR2 size = { 110, 165 };
		DrawBox(pos.x, pos.y - 30, pos.x + size.x, pos.y + size.y, 0x898989, true);
		DrawBox(pos.x + 15, pos.y + 15, (pos.x + size.x) - 15, (pos.y + size.y) - 15, 0x606060, true);
		DrawString(pos.x + 3, pos.y - 12, "Player�̏��", 0xffffff);
	}

	for (auto itr : stock)
	{
		itr->Draw();
	}

	for (int y = 0; y < BOARD_DEF_TROUT_Y; y++)
	{
		for (int x = 1; x < BOARD_DEF_TROUT_X-1; x++)
		{
			
				auto tmp = (board->GetBoard(VECTOR2{ x,y }));
				tmp.lock()->Draw();
				int color = (tmp.lock()->GetSuit() <= SUIT_CRUB ? 0xffffff : 0xff0000);

				/*
				DrawFormatString(tmp.lock()->GetPos().x * 60 + DRAW_DISTANCE.x,
					tmp.lock()->GetPos().y * 60 + DRAW_DISTANCE.y, color, "%d", tmp.lock()->GetNum());
				DrawFormatString(tmp.lock()->GetPos().x * 60 + DRAW_DISTANCE.x+32,
					tmp.lock()->GetPos().y * 60 + DRAW_DISTANCE.y+32, color, "%d", tmp.lock()->GetSuit());
			*/
		}
	}

	
	
	PLcard->Draw();
	static int  FontHandle = CreateFontToHandle(NULL, 40, 3);

	DrawFormatStringToHandle(60 - 10, 128, 0xFFFFFF, FontHandle, "%d", player->GetNumber());

	// �ʂ����ꏊ���g�����v�̗��ʂɂȂ�
	{
		VECTOR2 cp = { 160, 120 };
		int size = 60;
		for (int y = 0; y < BOARD_DEF_TROUT_Y; y++) {
			for (int x = 1; x < BOARD_DEF_TROUT_X - 1; x++) {
				if (board->GetSuit({ x, y }) == SUIT_NON) {
					DrawRectRotaGraph2(
						cp.x + (size / 2) + (size * x), cp.y + (size / 2) + (size * y),
						size * 2, 0,
						size, size,
						(size / 2),(size / 2),
						1.0f,0.0f,
						image[0],
						true, false
					);
				}
			}
		}
	}


	player->Draw();



	if (Goalflg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (255/30)* lpGameTask.Timer("goalfill", 30));
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	if (lpGameTask.Timer("gameover") > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (255 / 25)* lpGameTask.Timer("goalfill", 30));
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	//DrawString(0, 0, "Main", 0x888888);	
	// Board::�`��();
	// Player::�`��();
	//(*card).Draw();
	//DrawString(0, 0, "Main", 0x888888);

	// �������
	{
		VECTOR2 pos = {5,500};
		DrawString(pos.x, pos.y, "Q�L�[�ŊȒP�Ȏ�舵������", 0xffffff);
		DrawString(pos.x, pos.y + GetFontSize(), "�J����������肵�܂�", 0xffffff);
		if (flag == false) {
			if (keyData[KEY_INPUT_Q] && !keyDataOld[KEY_INPUT_Q]) {
				flag = true;
			}
		}
		else {
			if (keyData[KEY_INPUT_Q] && !keyDataOld[KEY_INPUT_Q]) {
				flag = false;
			}
			DrawGraph(0, 0, image[1], true);
		}
	}
	
	return false;
}


bool SceneMain::SetStock()
{
	// 1�`3�̂����ꂩ�̃L�[�������Ȃ�������L�[�����������ɁA
	// ���͂��ꂽ�����ɓ��͂��ꂽ�ԍ��̃X�g�b�N�̃J�[�h��ݒu����
	VECTOR2 sarchTBL[4] = { { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 } };

	int stock_num = -1;

	if (CheckHitKey(KEY_INPUT_1)) stock_num = 0;
	if (CheckHitKey(KEY_INPUT_2)) stock_num = 1;
	if (CheckHitKey(KEY_INPUT_3)) stock_num = 2;

		if (stock_num != -1 && stock[stock_num]->GetSuit() != SUIT_NON)
	{

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(BOARD_DEF_TROUT_X * 60 + DRAW_DISTANCE.x - 12, stock_num * 60 * 2 + DRAW_DISTANCE.y - 12,
				BOARD_DEF_TROUT_X * 60 + DRAW_DISTANCE.x + 12 + 50, stock_num * 60 * 2 + DRAW_DISTANCE.y + 12 + 75, 0x00EE00, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (lpGameTask.PressKey(KEY_INPUT_UP))
		{
			if (player->GetPos().y / 60 - 1 < 0) return false;
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_UP], stock[stock_num]->GetSuit(), stock[stock_num]->GetNum())));
			stock[stock_num]->SetSuit(SUIT_NON);
			return true;
		}
		if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
		{
			if (player->GetPos().x / 60 + 1 >= BOARD_DEF_TROUT_X)  return false;
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_RIGHT], stock[stock_num]->GetSuit(), stock[stock_num]->GetNum())));
			stock[stock_num]->SetSuit(SUIT_NON);
			return true;
		}
		if (lpGameTask.PressKey(KEY_INPUT_DOWN))
		{
			if (player->GetPos().y / 60 + 1 >= BOARD_DEF_TROUT_Y)  return false;
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_DOWN], stock[stock_num]->GetSuit(), stock[stock_num]->GetNum())));
			stock[stock_num]->SetSuit(SUIT_NON);
			return true;
		}
		if (lpGameTask.PressKey(KEY_INPUT_LEFT))
		{
			if (player->GetPos().x / 60 - 1 < 0)  return false;
			board->SetBoard(board->AddObjList(make_shared<Card>(player->GetPos() / 60 + sarchTBL[DIR_LEFT], stock[stock_num]->GetSuit(), stock[stock_num]->GetNum())));
			stock[stock_num]->SetSuit(SUIT_NON);
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
	if (lpGameTask.PressKey(KEY_INPUT_UP))
	{
		if (player->GetPos().y / 60 - 1 < 0) return;
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 ,player->GetPos().y / 60 - 1 }).expired()) return ;
		vec = sarchTBL[DIR_UP];
		tmp_dir = DIR_UP;
	}
	if (lpGameTask.PressKey(KEY_INPUT_RIGHT))
	{
		if (player->GetPos().x/60 +1 >= BOARD_DEF_TROUT_X) return;
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 + 1,player->GetPos().y / 60 }).expired()) return ;
		vec = sarchTBL[DIR_RIGHT];
		tmp_dir = DIR_RIGHT;
	}
	if (lpGameTask.PressKey(KEY_INPUT_DOWN))
	{
		if (player->GetPos().y / 60 + 1 >= BOARD_DEF_TROUT_Y) return;
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 ,player->GetPos().y / 60 + 1 }).expired()) return ;
		vec = sarchTBL[DIR_DOWN];
		tmp_dir = DIR_DOWN;
	}
	if (lpGameTask.PressKey(KEY_INPUT_LEFT))
	{
		if (player->GetPos().x / 60 - 1 < 0) return;
		if (board->GetBoard(VECTOR2{ player->GetPos().x / 60 - 1,player->GetPos().y / 60 }).expired() ) return ;
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

	PLcard->SetSuit(player->GetSuit());

	board->SetBoard(board->AddObjList(make_shared<Card>(tmp_pos, SUIT_NON, 0)));

}

void SceneMain::Key()
{
	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);
}
