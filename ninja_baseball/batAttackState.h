#pragma once
#include "batState.h"

class bat;

class batAttackState :public batState
{
public:

	int frameCount;
	int attackCount;	//���� Ƚ��.. 1ȸ ���� �� �ٷ� �������� �ʰ�(�� ���� ����)

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);

};

