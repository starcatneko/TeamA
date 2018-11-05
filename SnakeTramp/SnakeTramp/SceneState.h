#pragma once
#include "DxLib.h"
#include <memory>
#include <list>
#include <mutex>

class SceneState;

// SceneState	uniqueƒ|ƒCƒ“ƒ^
typedef std::unique_ptr<SceneState> Scene;

class SceneState
{
public:
	virtual ~SceneState();
	virtual void Init() = 0;
	virtual Scene Update(Scene own) = 0;
	virtual bool Draw() = 0;
};

