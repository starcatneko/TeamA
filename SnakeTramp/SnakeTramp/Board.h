#pragma once

#define BOARD_DEF_TROUT_X		(7)		// Ͻ����̫�Ă̐�
#define BOARD_DEF_TROUT_Y		(7)		// Ͻ����̫�Ă̐�

class VECTOR2;

class Board
{
public:
	Board(bool defFlag, VECTOR2 troutCnt);
	VECTOR2 BoardTrout();			// �ް�ނ�Ͻ����ύX�������Ȃ炱������
private:
	~Board();
	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;
	
};

