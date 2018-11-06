#pragma once
#include <memory>
#include <vector>

class Card;

#define BOARD_DEF_TROUT_X		(7)		// Ͻ����̫�Ă̐�
#define BOARD_DEF_TROUT_Y		(7)		// Ͻ����̫�Ă̐�

#define BOARD_START				(VECTOR2(0,0))	// ��ڲ԰�̽��Ĉʒu
#define BOARD_DEF_GOAL			((VECTOR2(BOARD_DEF_TROUT_X + 1,BOARD_DEF_TROUT_Y))

class VECTOR2;

class Board
{
public:
	Board();
	Board(VECTOR2 troutCnt);	// �����t���ݽ�׸�Ͻ���̎w�肪�ł���
	void Update(void);

	void PushTrout(void);
private:
	~Board();

	std::vector<std::weak_ptr<Card>*> data;

	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;

	VECTOR2 pPos;		// ��ڲ԰��Pos
	VECTOR2 ckPos;		// �ړ�����\���Pos

	int moveDirection;

};

