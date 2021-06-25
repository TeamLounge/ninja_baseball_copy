#pragma once
#include "gameNode.h"

class stageScene : public gameNode
{
private:
	RECT _rc;
	int _count;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

