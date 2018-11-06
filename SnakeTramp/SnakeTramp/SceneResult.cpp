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

	if (lpGameTask.PressKey(KEY_INPUT_Z))
	{
		return std::make_unique<SceneTitle>();
	}
	return own;
}

bool SceneResult::Draw()
{
	//board•`‰æ

	return true;
}
