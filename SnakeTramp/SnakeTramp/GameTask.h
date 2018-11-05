#pragma once
#include <memory>

#define lpGameTask GameTask::GetInstance()

class SceneState;

class GameTask
{
public:
	static GameTask &GetInstance()
	{
		return *s_Instance;
	};

	void Run();

private:
	struct GameTaskDeleter
	{
		void operator ()(GameTask* GameTask) const
		{
			delete GameTask;
		}
	};

	std::unique_ptr<SceneState> state;
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;

	GameTask();
	~GameTask();

};

