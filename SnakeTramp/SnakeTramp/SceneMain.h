#pragma once
#include "SceneState.h"
#include <memory>
#include <map>

class Board;
class Card;


#define GOAL_EFFECT_TIME (180)			//ゴール時に行う演出のフレーム数

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
	bool Effect(std::map<int,std::string>);

private:
	std::unique_ptr<Card> card;
	std::shared_ptr<Board> board;
	// アニメーション処理等で使うカウンター
	UINT anim_cnt;
};

