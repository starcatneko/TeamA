#pragma once
#include "SceneState.h"
#include "Board.h"
//class Board;

class SceneResult :
	public SceneState
{
public:
	SceneResult();
	// ƒV[ƒ“‘JˆÚ‚ÉSceneMain‚©‚çBoard‚Ìshared_ptr‚ğó‚¯æ‚é
	SceneResult(std::shared_ptr<Board> board);
	~SceneResult();
	void Init();
	Scene Update(Scene own);
	std::shared_ptr<Board> board;
	bool Draw();

	bool Effect();

};

