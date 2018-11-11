#pragma once
#include "SceneState.h"
#include "Board.h"
//class Board;

class SceneResult :
	public SceneState
{
public:
	SceneResult();
	// シーン遷移時にSceneMainからBoardのshared_ptrを受け取る
	SceneResult(std::shared_ptr<Board> board);
	~SceneResult();
	void Init();
	Scene Update(Scene own);
	std::shared_ptr<Board> board;
	bool Draw();

private:
	bool endflg;
	// boardの0,0に数字が入っていたらゲームオーバー判定
	bool clearflg;
	bool Effect();
};

