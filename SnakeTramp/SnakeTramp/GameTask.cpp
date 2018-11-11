#include "Dxlib.h"
#include "GameTask.h"
#include "SceneTitle.h"
#include "SceneMain.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());


GameTask::GameTask()
{
	state = std::make_unique<SceneTitle>();
}


GameTask::~GameTask()
{

}

bool GameTask::PressKey(int key)
{
	static std::map<int, int> keymap;
	
	if (keymap[key] == -1)
	{
		keymap[key] = 0;
		return false;
	}

	if (CheckHitKey(key) == true)
	{
		keymap[key]++;
	}
	else if(keymap[key] > 0)
	{
		keymap[key] = -1;
	}

	return (keymap[key] == 1 ? true:false);
}

void GameTask::Run()
{
	ClsDrawScreen();

	state = state->Update(std::move(state));
	state->Draw();
	ScreenFlip();
}
