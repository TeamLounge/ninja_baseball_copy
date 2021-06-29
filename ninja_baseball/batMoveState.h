#pragma once
#include "batState.h"

class bat;

class batMoveState :public batState
{
public:

	int frameCount;
	int timeCount;		//���� �� ���� �ð� ������ idle�� ��ȭ�ϱ� ����.

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};
