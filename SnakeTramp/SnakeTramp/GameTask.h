#pragma once
#include <memory>

#define lpGameTask GameTask::GetInstance()

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

	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;

	GameTask();
	~GameTask();

};

