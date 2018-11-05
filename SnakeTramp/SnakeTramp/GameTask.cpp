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

void GameTask::Run()
{
	ClsDrawScreen();

	state = state->Update(std::move(state));
	state->Draw();
	ScreenFlip();
}
