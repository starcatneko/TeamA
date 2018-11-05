#pragma once
#include <memory>
#include <map>
#define lpGameTask GameTask::GetInstance()

class SceneState;

class GameTask
{
public:
	static GameTask &GetInstance()
	{
		return *s_Instance;
	};
	//int keybuf

	// �L�[�������ꂽ���ǂ������`�F�b�N����
	// ���݂̂̃L�[�������\
	bool PressKey(int key);
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

