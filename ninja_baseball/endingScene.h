#pragma once
#include "gameNode.h"

class endingScene : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

