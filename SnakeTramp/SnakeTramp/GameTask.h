#pragma once
#include <memory>
#include <map>
#include "DxLib.h"
#define lpGameTask GameTask::GetInstance()

#define BOARD_DEF_TROUT_X		(7+1)		// Ͻ����̫�Ă̐�
#define BOARD_DEF_TROUT_Y		(7)		// Ͻ����̫�Ă̐�

#define BOARD_START				(VECTOR2(0,0))	// ��ڲ԰�̽��Ĉʒu
#define BOARD_DEF_GOAL			((VECTOR2(BOARD_DEF_TROUT_X + 1,BOARD_DEF_TROUT_Y))


#define TROUT_SIZE				(60)	// Ͻ�̻���


#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

#define DRAW_DISTANCE			(VECTOR2(SCREEN_SIZE_X/2 - (BOARD_DEF_TROUT_X/2)*TROUT_SIZE,SCREEN_SIZE_Y/2- (BOARD_DEF_TROUT_Y/2)*TROUT_SIZE))	// �Ֆʂ̕`������炷����


// ���͂��ꂽ�\���L�[�̕���
enum DIR
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT
};

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

