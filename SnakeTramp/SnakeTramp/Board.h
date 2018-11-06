#pragma once
#include <memory>
#include <vector>

class Card;

#define BOARD_DEF_TROUT_X		(7)		// Ͻ����̫�Ă̐�
#define BOARD_DEF_TROUT_Y		(7)		// Ͻ����̫�Ă̐�

class VECTOR2;

class Board
{
public:
	Board();
	Board(VECTOR2 troutCnt);	// �����t���ݽ�׸�Ͻ���̎w�肪�ł���

	void PushTrout(void);
private:
	~Board();

	std::vector<std::weak_ptr<Card>*> data;

	bool CheckBoard(VECTOR2 pos);
	bool SetBoard(VECTOR2 pos);

	bool changeFlag;

	VECTOR2 troutCnt;

};

