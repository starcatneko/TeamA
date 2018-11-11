#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "DxLib.h"

#define lpGameTask GameTask::GetInstance()
#define lpTimer &GameTask::GetInstance()->Timer

#define BOARD_DEF_TROUT_X		(7+2)		// Ͻ����̫�Ă̐� �X�^�[�g�E�S�[���̗�𑫂�
#define BOARD_DEF_TROUT_Y		(7)		// Ͻ����̫�Ă̐�

#define BOARD_START				(VECTOR2(0,0))	// ��ڲ԰�̽��Ĉʒu
#define BOARD_DEF_GOAL			(VECTOR2(BOARD_DEF_TROUT_X -1,BOARD_DEF_TROUT_Y-1))

#define TROUT_SIZE				(60)	// Ͻ�̻���

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

#define DRAW_DISTANCE			(VECTOR2(SCREEN_SIZE_X/2 - (BOARD_DEF_TROUT_X/2)*TROUT_SIZE,SCREEN_SIZE_Y/2- (BOARD_DEF_TROUT_Y/2)*TROUT_SIZE))	// �Ֆʂ̕`������炷����

#define STOCK_NUM				(3)

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

	int Timer(std::string name, int time);
	int Timer(std::string name);
	void TimerReset();
	void DrawBack();
	std::vector<int> image;

private:

	struct GameTaskDeleter
	{
		void operator ()(GameTask* GameTask) const
		{
			delete GameTask;
		}
	};
	int backOffset; 

	std::unique_ptr<SceneState> state;
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;
	
	std::map<std::string, int> TimerCounter;

	GameTask();
	~GameTask();

	void Init();

};

