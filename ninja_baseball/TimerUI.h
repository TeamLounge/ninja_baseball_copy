#pragma once
#include "gameNode.h"
class timerUI : public gameNode
{
private:
	int _time; //처음 타이머 시간
	int _timeStandard; //타이머가 1씩 내려가는 기준 시간
	float _worldTime;
	float _x, _y;
public :
	HRESULT init(int time, int time_standard, float x, float y); //전체 시간과 타이머가 몇초마다 내려갈지,  타이머 중점좌표
	void release();
	void update(float x, float y);
	void render();

	int getTime() { return _time; }
	void setTime(int time) { _time = time; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
};

