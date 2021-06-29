#pragma once
#include "gameNode.h"
class stageScene2 : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

