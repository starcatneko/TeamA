#include "SceneMain.h"
#include "SceneTitle.h"
#include "Dxlib.h"


SceneMain::SceneMain()
{

}


SceneMain::~SceneMain()
{
}
void SceneMain::Init()
{
}
Scene SceneMain::Update(Scene own)
{
	if (CheckHitKey(KEY_INPUT_1))
	{
		return std::make_unique<SceneTitle>();
	}
	return own;
}

bool SceneMain::Draw()
{
	DrawString(0, 0, "Main", 0x888888);
	return false;
}
