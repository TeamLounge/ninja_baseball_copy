#pragma once
#include "bbState.h"

class blueBaseball;

class bbIdleState :public bbState
{
	int frameCount;
	int timeCount;	//에너미 공격 범위에 플레이어가 들어오면 시작되는 카운트(바로 공격하지 않고, idle 상태 잠시 유지하기 위함)

	virtual bbState* inputHandle(blueBaseball* blueBaseball);
	virtual void update(blueBaseball* blueBaseball);
	virtual void enter(blueBaseball* blueBaseball);
	virtual void exit(blueBaseball* blueBaseball);
};
