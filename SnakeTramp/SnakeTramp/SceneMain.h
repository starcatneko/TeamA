#pragma once
#include "SceneState.h"
#include <memory>

class SceneMain :
	public SceneState
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	Scene Update(Scene own);
	bool Draw();
};

