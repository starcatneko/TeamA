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
	clearflg = (board->GetNumber(VECTOR2{ 0,0 }) == 0 ? true : false);
	endflg = false;
}


SceneResult::~SceneResult()
{

}

void SceneResult::Init()
{

}

Scene SceneResult::Update(Scene own)
{
	// �Q�[���I�[�o�[���o
	if (clearflg == false)
	{
		if (lpGameTask.Timer("gameoverstart", 25)==0)
		{
			if (lpGameTask.PressKey(KEY_INPUT_Z))
			{
				endflg = true;
			}
			if (endflg == true)
			{
				if (lpGameTask.Timer("end", 10) == 0)
				{
					return std::make_unique<SceneTitle>();
				}
			}
		}
		return own;
	}

	// ��ʑJ�ڃt���O true:�J�ڏ����J�n
	if (lpGameTask.PressKey(KEY_INPUT_Z))
	{
		endflg = true;
	}
	if (endflg == true)
	{
		if (lpGameTask.Timer("end", 10) == 0)
		{
			return std::make_unique<SceneTitle>();
		}
	}

	return own;
}


bool SceneResult::Draw()
{
	// �Q�[���I�[�o�[���o
	if (clearflg == false)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((255 / 20)* lpGameTask.Timer("gameoverstart")));
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		return false;
	}

	//board�`��

	DrawString(0, 0, "���ĂƂ߂�", 0xffffff);

	if (lpGameTask.Timer("resultstart", 15) > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((255 / 15)* lpGameTask.Timer("resultstart")));
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (lpGameTask.Timer("end") > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (255 / 15) * lpGameTask.Timer("end"));
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	return true;
}


