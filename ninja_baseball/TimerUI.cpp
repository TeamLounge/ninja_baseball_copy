#include "stdafx.h"
#include "timerUI.h"

HRESULT timerUI::init(int time, int timeStandard, float x, float y)
{
	_time = time;
	_timeStandard = timeStandard;
	_x = x;
	_y = y;
	_worldTime = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void timerUI::release()
{
}

void timerUI::update(float x, float y)
{
	_x = x;
	_y = y;

	if (_time != 0 && TIMEMANAGER->getWorldTime() - _worldTime >= _timeStandard)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_time--;
	}
	if (_time <= 0)
	{
		_time = 0;
	}
}

void timerUI::render()
{
	int ten = _time / 10;
	int one = _time % 10;

	char str[128];
	sprintf_s(str, "timer_%d", ten);
	IMAGEMANAGER->findImage(str)->render(getMemDC(), _x - IMAGEMANAGER->findImage(str)->getWidth(), _y);
	sprintf_s(str, "timer_%d", one);
	IMAGEMANAGER->findImage(str)->render(getMemDC(), _x + 3, _y);
}
