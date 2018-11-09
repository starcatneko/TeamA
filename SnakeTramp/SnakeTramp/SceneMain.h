#pragma once
#include "SceneState.h"
#include <memory>
#include <map>

class Board;
class Player;
class Card;
class Player;


#define GOAL_EFFECT_TIME (180)			//�S�[�����ɍs�����o�̃t���[����

class SceneMain :
	public SceneState
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	Scene Update(Scene own);
	bool Draw();
	bool GoalEffect();
	bool Fade_in();
	bool Effect();

private:
	std::weak_ptr<Card> card;
	std::shared_ptr<Board> board;
	std::unique_ptr<Player> player;
<<<<<<< HEAD
	// �A�j���[�V�����������Ŏg���J�E���^�[
	UINT anim_cnt;
=======
>>>>>>> master
};

