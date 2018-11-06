#pragma once
#include "SceneState.h"

class Board;
class Card;

class SceneMain :
	public SceneState
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	Scene Update(Scene own);
	bool Draw();

	std::unique_ptr<Card> card;
	std::shared_ptr<Board> board;
};

