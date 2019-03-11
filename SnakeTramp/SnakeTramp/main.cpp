#include "DxLib.h"
#include "ImgMng.h"
#include "GameTask.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)	return -1;	// �c�w���C�u�������������� �G���[���N�����璼���ɏI��
	SetDrawScreen(DX_SCREEN_BACK);
	
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		lpGameTask.Run();
	}
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}