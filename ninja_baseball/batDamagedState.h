#pragma once
#include "batState.h"

class bat;

class batDamagedState :public batState
{
public:

	int frameCount;
	int damageCount;	//배트의 3단계 변신을 위한 카운트
						//피격(count)  1~2회 : 변신 x
						//피격			3회 : 1단계 변신<noCap mode>	..모자 날아감;
						//피격			4회 : 2단계 변신<noBat mode>	..배트 날아감;	(모자랑 배트는 회전 없이 그대로 날아가지만, 카메라 벽 맞고 튕김 + 알파렌더)
						//피격			5회 : 3단계 변신<death mode>	..죽음;			(360도 회전하며 날아가다가 알파렌더)

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};
