#pragma once
#include "batState.h"

class bat;

class batMoveState :public batState
{
public:

	int frameCount;
	int timeCount;		//등장 후 일정 시간 지나면 idle로 변화하기 위함.

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};
