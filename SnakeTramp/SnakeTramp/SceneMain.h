#pragma once
#include "SceneState.h"

class Board;

class SceneMain :
	public SceneState
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	Scene Update(Scene own);
	bool Draw();

	std::shared_ptr<Board> board;
};

