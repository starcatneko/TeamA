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
	card = std::make_unique<Card>(VECTOR2( 0, 100), player->GetSuit(), player->GetNumber());

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
	// playerの挙動制御
	player->Update();

	// if(Playerがゴールにたどり着く ||
	// Playerの数値が規定範囲を超える)

	if(lpGameTask.PressKey(KEY_INPUT_Z))
	{
		return std::make_unique<SceneResult>();
	}
	return own;
}

bool SceneMain::Draw()
{
	// Board::描画();
	// Player::描画();
	player->Draw();
	//(*card).Draw();
	card->Draw();

	DrawString(0, 0, "Main", 0x888888);
	
	return false;
}
