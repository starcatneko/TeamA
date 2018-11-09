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
	// cardの生成

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
	//盤面、Player等初期化処理
}

Scene SceneMain::Update(Scene own)
{
	//card_u->Draw();
	
	// 1～3のいずれかのキーを押しながら方向キーを押した時に、
	// 入力された方向に入力された番号のストックのカードを設置する
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
			//Board::SetBoard(Plyaer.Pos+方向,stockSuit,stockNum);
		}
	}
	
	else if(lpGameTask.PressKey(KEY_INPUT_W) ||
		lpGameTask.PressKey(KEY_INPUT_D) ||
		lpGameTask.PressKey(KEY_INPUT_S) ||
		lpGameTask.PressKey(KEY_INPUT_A))
	{
	// 移動前のマスを移動不可マスにする
		// auto tmp = make_shared<Card>(player->GetPos(),,0);
		 //AddObjList(tmp);
		
		// board->SetBoard(tmp);


		player->SetSuit(board->GetSuit(player->GetPos() / 60));
		player->SetNumber(board->GetNumber(player->GetPos() / 60));
	}
	
	board->Update();
	// playerの挙動制御
	//player->Update(*card_u);

	/*
	if(player.pos == BOARD_DEF_GOAL ||
	 Playerの数値が規定範囲を超える)
	{
		ゴール演出();
		return std::make_unique<SceneResult>();
	}
	*/


	// 画面遷移フラグ true:遷移処理開始
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
	 board->描画(); // card->Draw()
	 lpGameTask.player->描画();
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