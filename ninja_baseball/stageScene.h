#pragma once
#include "gameNode.h"

class stageScene : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

