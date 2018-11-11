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
	// 万が一Boardのunique_ptrが初期化されていなかった場合resetをする
	if (board) board.reset();
	// boardのコンストラクタに引数を渡さない場合、BOARD_DEF_TROUT_XとBOARD_DEF_TROUT_Yが渡される
	board = std::make_shared<Board>();
	// player(初期座標, 初期サイズ, 初期所持スート, 初期所持数字)
	player = std::make_unique<Player>( BOARD_START, VECTOR2( TROUT_SIZE, TROUT_SIZE), SUIT_SPADE, 1);
	


	// 盤面にカード生成
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
			// 状況で調整

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
	// 1～3のいずれかのキーを押しながら方向キーを押した時に、
	// 入力された方向に入力された番号のストックのカードを設置する
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
	// ストック操作が行われない場合、プレイヤー操作の判定をする
	if (!SetStock())
	{
		PlayerMove();
	}
	
	board->Update();

	/*
	if(player.pos == BOARD_DEF_GOAL ||
	 Playerの数値が規定範囲を超える)
	{
		ゴール演出();
		return std::make_unique<SceneResult>();
	}
	*/


	// 画面遷移フラグ true:遷移処理開始
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
	 board->描画(); // card->Draw()
	 lpGameTask.player->描画();
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
	// Board::描画();
	// Player::描画();
	player->Draw();
	//(*card).Draw();
	DrawString(0, 0, "Main", 0x888888);
	
	return false;
}

bool SceneMain::GoalEffect()
{
	// 演出のタイマー
	static UINT timer = 18;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / timer);
	DrawBox(0, 0, 0xfff, 0xfff, 0xffffff, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// 関数実行後、タイマーが0になったタイミングで処理を終了、次のシーンに推移させる
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
	// 移動前のマスを移動不可マスにする
	// auto tmp = make_shared<Card>(player->GetPos(),,0);
	//AddObjList(tmp);
	// board->SetBoard(tmp);

	VECTOR2 tmp_pos = player->GetPos()/60 + vec;

	int  tmp_num = board->GetNumber(tmp_pos);
	CARD_SUIT tmp_suit = board->GetSuit(tmp_pos);

	// スートが空白
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
		// SUITが黒字
		tmp_num = tmp_num;
	}
	else
	{
		// SUITが赤字
		tmp_num = -tmp_num;
	}

	//	board->GetNumber(player->GetPos() / 60) + player->GetNumber()
	//(board->GetSuit(
	player->SetNumber(player->GetNumber()+ tmp_num);
	player->SetSuit(tmp_suit);
	player->Update(tmp_dir);


	board->SetBoard(board->AddObjList(make_shared<Card>(tmp_pos, SUIT_NON, 0)));

}
