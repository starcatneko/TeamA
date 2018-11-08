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
	// 万が一Boardのunique_ptrが初期化されていなかった場合resetをする
	if (board) board.reset();
	
	//card = std::make_unique<Card>(VECTOR2{ 2,2 }, SUIT_HEART, 12);
	// boardのコンストラクタに引数を渡さない場合、BOARD_DEF_TROUT_XとBOARD_DEF_TROUT_Yが渡される
	board = std::make_shared<Board>();
	//player.pos = BOARD_START;
	//盤面、Player等初期化処理
}

Scene SceneMain::Update(Scene own)
{
	/*
	// 1～3のいずれかのキーを押しながら方向キーを押した時に、
	// 入力された方向に入力された番号のストックのカードを設置する
	if (1~3のいずれかが入力中)
	{
		if(方向キー入力)
		{
			Board::ストック設置(方向,ストックの番号);
		}
	}
	else if(方向キー入力)
	{
		Player::移動(方向);
	}
	*/
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
	static bool flg = false;
	if(lpGameTask.PressKey(KEY_INPUT_Z))
	{
		flg = true;
	}
	if (flg == true)
	{
		if (GoalEffect() == true)
		{
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

	/*
	int BOARD_DIS_X = 64;
	int BOARD_DIS_Y = 64;
	int CHIPSIZE = 48;
		for (int x = 0; x < BOARD_DEF_TROUT_X; x++)
		{
			for (int y = 0; y < BOARD_DEF_TROUT_Y; y++)
			{
				int forx = BOARD_DIS_X + x * CHIPSIZE;
				int fory = BOARD_DIS_Y + y * CHIPSIZE;
				DrawBox(forx, fory,
					forx + CHIPSIZE, fory + CHIPSIZE,
					0x00FF00, false);
			}
		}
		*/
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
};
