#include "GameTask.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Dxlib.h"


SceneTitle::SceneTitle()
{
	cnt = 0;
}


SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

Scene SceneTitle::Update(Scene own)
{
	if (lpGameTask.PressKey(KEY_INPUT_Z))
	{
		return std::make_unique<SceneMain>();
	}
	return own;
}

bool SceneTitle::Draw()
{
	cnt++;
	SetFontSize(32);
	if(cnt / 30 % 2 == 0){
		DrawString(300, 400, "PRESS Z KEY", 0xFFFFFF);
	}
	SetFontSize(DEFAULT_FONT_SIZE);
	DrawGraph(100, 80, lpGameTask.image[0], true);
	//DrawString(0, 0, "Title", 0x888888);
	return false;
}