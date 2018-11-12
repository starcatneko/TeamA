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
	lpGameTask.TimerReset();
	// 万が一Boardのunique_ptrが初期化されていなかった場合resetをする
	if (board) board.reset();
	// boardのコンストラクタに引数を渡さない場合、BOARD_DEF_TROUT_XとBOARD_DEF_TROUT_Yが渡される
	board = std::make_shared<Board>();
	// player(初期座標, 初期サイズ, 初期所持スート, 初期所持数字)
	player = std::make_unique<Player>( BOARD_START, VECTOR2( TROUT_SIZE, TROUT_SIZE), SUIT_SPADE, 10);
	
	PLcard = std::make_shared<Card>(VECTOR2{ -2,1 }, player->GetSuit(), 1);

	// 盤面にカード生成
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
			// 状況で調整
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

	// ゲームオーバー
	if (player->GetNumber() <= 0 || player->GetNumber() >= 22)
	{
		if (lpGameTask.Timer("gameover", 25) == 0)
		{
			board->SetBoard(board->AddObjList(make_shared<Card>(VECTOR2{ 0,0 }, SUIT_NON, 13)));
			return std::make_unique<SceneResult>(board);
		}
		return own;
	}

	// ストック操作が行われない場合、プレイヤー操作の判定をする
	if (!SetStock())
	{
		PlayerMove();
	}
	
	board->Update();

	
	if(player->GetPos() == BOARD_DEF_GOAL*60){
		//ゴール演出();
		Goalflg = true;
	}
	


	// 画面遷移フラグ true:遷移処理開始
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
	 board->描画(); // card->Draw()
	 lpGameTask.player->描画();
	*/

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

	DrawFormatStringToHandle(60, 128, 0xFFFFFF, FontHandle, "%d", player->GetNumber());


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

	DrawString(0, 0, "Main", 0x888888);	
	// Board::描画();
	// Player::描画();
	//(*card).Draw();
	DrawString(0, 0, "Main", 0x888888);
	
	return false;
}


bool SceneMain::SetStock()
{
	// 1～3のいずれかのキーを押しながら方向キーを押した時に、
	// 入力された方向に入力された番号のストックのカードを設置する
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

	PLcard->SetSuit(player->GetSuit());

	board->SetBoard(board->AddObjList(make_shared<Card>(tmp_pos, SUIT_NON, 0)));

}
