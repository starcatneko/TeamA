#pragma once
#include "DxLib.h"
#include <memory>
#include <list>
#include <mutex>

typedef std::unique_ptr<SceneState> Scene;

class SceneState
{
public:
	virtual ~SceneState();
	virtual void Init() = 0;
	virtual Scene Update(Scene own, std::unique_ptr</*�L�[�R���g���[���N���X*/> &mousectl) = 0;
	virtual bool Draw();
};

