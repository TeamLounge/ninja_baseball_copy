#pragma once
#include "wbState.h"

class whiteBaseball;

class wbIdleState :public wbState
{
public:

	int frameCount;
	int timeCount;	//에너미 공격 범위에 플레이어가 들어오면 시작되는 카운트(바로 공격하지 않고, idle 상태 잠시 유지하기 위함)

	virtual wbState* inputHandle(whiteBaseball* whiteBaseball);
	virtual void update(whiteBaseball* whiteBaseball);
	virtual void enter(whiteBaseball* whiteBaseball);
	virtual void exit(whiteBaseball* whiteBaseball);
};
