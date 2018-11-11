#pragma once
#include "SceneState.h"
#include <memory>
#include <map>

class Board;
class Player;
class Card;
class Player;


#define GOAL_EFFECT_TIME (180)			//ゴール時に行う演出のフレーム数

class SceneMain :
	public SceneState
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	bool SetStock();
	Scene Update(Scene own);
	bool Draw();
	bool GoalEffect();
	bool Fade_in();
	bool Effect();

private:
	std::shared_ptr<Board> board;
	std::unique_ptr<Player> player;
	// アニメーション処理等で使うカウンター
	void PlayerMove();
	bool Goalflg;
	UINT anim_cnt;
};

