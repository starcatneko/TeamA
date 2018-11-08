#pragma once
#include <memory>
#include <vector>
#include "VECTOR2.h"

class Card;

#define BOARD_DEF_TROUT_X		(7)		// Ͻ����̫�Ă̐�
#define BOARD_DEF_TROUT_Y		(7)		// Ͻ����̫�Ă̐�

#define BOARD_START				(VECTOR2(0,0))	// ��ڲ԰�̽��Ĉʒu
#define BOARD_DEF_GOAL			((VECTOR2(BOARD_DEF_TROUT_X + 1,BOARD_DEF_TROUT_Y))

#define TROUT_SIZE				(60)	// Ͻ�̻���


class Board
{
public:
	Board();
	~Board();
	Board(VECTOR2 troutCnt);	// �����t���ݽ�׸�Ͻ���̎w�肪�ł���
	void Update(void);

	void PushTrout(void);
private:

	std::vector<std::weak_ptr<Card>*> data;

	bool CheckBoard(VECTOR2 pos, int moveDirection);

	bool changeFlag;

	VECTOR2 troutCnt;

	VECTOR2 pPos;		// ��ڲ԰��Pos
	VECTOR2 ckPos;		// �ړ�����\���Pos

	int moveDirection;

	const TCHAR *DebugChar = "�E";		// ���ޯ�ޗp������

};

