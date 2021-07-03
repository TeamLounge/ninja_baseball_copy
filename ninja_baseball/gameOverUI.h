#pragma once
#include "gameNode.h"
#include "TimerUI.h"

class gameOverUI : public gameNode
{
private:
	timerUI* _timerUI;
	bool _isGameOver;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setIsGameOver(bool b) { _isGameOver = b; }
	bool getIsGameOver() { return _isGameOver; }

	void setTimer(int time) { _timerUI->setTime(time); }
};

