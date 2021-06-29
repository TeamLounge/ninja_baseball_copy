#pragma once
#include "batState.h"

class bat;

class batIdleState :public batState
{
public:

	int frameCount;
	int timeCount;	//에너미 공격 범위에 플레이어가 들어오면 시작되는 카운트(바로 공격하지 않고, idle 상태 잠시 유지하기 위함)

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};