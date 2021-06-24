#pragma once
#include "gameNode.h"
class endingScene : gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

