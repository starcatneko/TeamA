#pragma once
#include "SceneState.h"
#include "Board.h"
//class Board;

class SceneResult :
	public SceneState
{
public:
	SceneResult();
	// �V�[���J�ڎ���SceneMain����Board��shared_ptr���󂯎��
	SceneResult(std::shared_ptr<Board> board);
	~SceneResult();
	void Init();
	Scene Update(Scene own);
	std::shared_ptr<Board> board;
	bool Draw();

	bool Effect();

};

