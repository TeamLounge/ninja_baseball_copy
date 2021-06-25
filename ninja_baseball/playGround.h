#pragma once
#include "gameNode.h"
#include "player.h"

class playGround : public gameNode
{
private:
	
	player* _red;
	player* _Ryno;


public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

