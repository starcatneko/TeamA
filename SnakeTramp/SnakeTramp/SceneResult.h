#pragma once
#include "SceneState.h"
class SceneResult :
	public SceneState
{
public:
	SceneResult();
	~SceneResult();
	void Init();
	Scene Update(Scene own);
	bool Draw();

};

