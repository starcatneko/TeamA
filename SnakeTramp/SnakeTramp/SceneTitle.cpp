#include "GameTask.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Dxlib.h"


SceneTitle::SceneTitle()
{
}


SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

Scene SceneTitle::Update(Scene own)
{
	if (lpGameTask.PressKey(KEY_INPUT_1))
	{
		return std::make_unique<SceneMain>();
	}
	return own;
}

bool SceneTitle::Draw()
{
	DrawString(0, 0, "Title", 0x888888);
	return false;
}