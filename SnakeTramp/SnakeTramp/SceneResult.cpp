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


	// ��ʑJ�ڃt���O true:�J�ڏ����J�n
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
	//board�`��

	return true;
}


bool SceneResult::Effect()
{
	// ���o�̃^�C�}�[
	static UINT timer = 18;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / timer);
	DrawBox(0, 0, 0xfff, 0xfff, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�֐����s��A�^�C�}�[��0�ɂȂ����^�C�~���O�ŏ������I���A���̃V�[���ɐ��ڂ�����
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
