#include "SceneResult.h"
#include "GameTask.h"
#include "SceneTitle.h"
#include "Dxlib.h"

class Board;

SceneResult::SceneResult()
{
}

SceneResult::SceneResult(std::shared_ptr<Board> board)
{
	SceneResult::board = board;
}


SceneResult::~SceneResult()
{

}

void SceneResult::Init()
{

}

Scene SceneResult::Update(Scene own)
{


	// 画面遷移フラグ true:遷移処理開始
	static bool flg = false;
	if (lpGameTask.PressKey(KEY_INPUT_Z))
	{
		flg = true;
	}
	if (flg == true)
	{
		if (Effect() == true)
		{
			return std::make_unique<SceneTitle>();
		}
	}

	return own;
}


bool SceneResult::Draw()
{
	//board描画

	return true;
}


bool SceneResult::Effect()
{
	// 演出のタイマー
	static UINT timer = 18;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / timer);
	DrawBox(0, 0, 0xfff, 0xfff, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//関数実行後、タイマーが0になったタイミングで処理を終了、次のシーンに推移させる
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
