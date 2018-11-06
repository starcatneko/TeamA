#include "Dxlib.h"
#include "GameTask.h"


std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());


GameTask::GameTask()
{
}


GameTask::~GameTask()
{
}

void GameTask::Run()
{
	ScreenFlip();
	ClsDrawScreen();
	//state = state->Update(std::move(state));
	//state->Draw();
}
