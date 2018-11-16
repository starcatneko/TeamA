#pragma once
#include "SceneState.h"
#include <memory>

class SceneTitle:
	public SceneState
{
public:
	SceneTitle();
	~SceneTitle();
	void Init();
	Scene Update(Scene own);
	bool Draw();
	int cnt;
};

