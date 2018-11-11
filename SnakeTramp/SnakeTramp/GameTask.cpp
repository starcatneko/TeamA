#include "Dxlib.h"
#include "GameTask.h"
#include "ImgMng.h"
#include "SceneTitle.h"
#include "SceneMain.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());


GameTask::GameTask()
{
	state = std::make_unique<SceneTitle>();
	
	//image = LoadGraph("back.png");	
	image.resize(10);
	backOffset = 0;
	Init();
}
GameTask::~GameTask()
{

}

void GameTask::Init()
{
	//image[0] = lpImgMng.Load("../Assets/Image/taitle.png");
}

bool GameTask::PressKey(int key)
{
	static std::map<int, int> keymap;
	
	if (keymap[key] == -1)
	{
		keymap[key] = 0;
		return false;
	}

	if (CheckHitKey(key) == true)
	{
		keymap[key]++;
	}
	else if(keymap[key] > 0)
	{
		keymap[key] = -1;
	}

	return (keymap[key] == 1 ? true:false);
}

int GameTask::Timer(std::string name, int time)
{
	//	auto itr = TimerCounter.find(name);
	if (!TimerCounter[name])
	{
		return TimerCounter[name] = time;
	}

	if (TimerCounter[name] > 0) {
		TimerCounter[name]--;
	}
	if (TimerCounter[name] <= 0)
	{
		TimerCounter[name] = -1;
		return 0;
	}
	return TimerCounter[name];
}
int GameTask::Timer(std::string name)
{
	if (!TimerCounter[name])
	{
		return -1;
	}
	if (TimerCounter[name] <= 0)
	{
		return 0;
	}
	return TimerCounter[name];

}

void GameTask::TimerReset()
{
	TimerCounter.erase(TimerCounter.begin(), TimerCounter.end());
}
//背景
void GameTask::DrawBack()
{
	static int  FontHandle = CreateFontToHandle(NULL, 128, 3);

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y,	0x313131, true);
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			//SetFontSize(128);
			DrawStringToHandle(x * 128 + backOffset - 128,
				y * 128 + backOffset - 128 + 6,
				"◆", 0x140000, FontHandle);
			DrawStringToHandle(x * 128 + backOffset - 128,
				y * 128 + backOffset - 128,
				"◆", 0x280000, FontHandle);
			//SetFontSize(DEFAULT_FONT_SIZE);

			//DrawGraph(x*128+backOffset, y*128+ backOffset, image, true);
		}
	}
	backOffset++;
	if (backOffset > 128) backOffset = 0;
}

void GameTask::Run()
{
	static bool imgflg = false;
	if (!imgflg)
	{
		image[0] = lpImgMng.Load("../Assets/Image/taitle.png");
		imgflg = true;
	}
	ClsDrawScreen();

	DrawBack();

	state = state->Update(std::move(state));
	state->Draw();

	ScreenFlip();
}

