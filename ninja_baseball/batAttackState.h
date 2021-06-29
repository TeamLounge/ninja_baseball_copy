#pragma once
#include "batState.h"

class bat;

class batAttackState :public batState
{
public:

	int frameCount;
	int attackCount;	//공격 횟수.. 1회 공격 후 바로 공격하지 않게(휠 윈드 금지)

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);

};

