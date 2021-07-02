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
};

