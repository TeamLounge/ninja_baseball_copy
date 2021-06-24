#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private :
	
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

