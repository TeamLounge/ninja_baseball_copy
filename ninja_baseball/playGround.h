#pragma once
#include "gameNode.h"
#include "player.h"
#include "redShadow.h" //빨강이 그림자 헤더

class playGround : public gameNode
{
private:
	
	player* _red;
	
	redShadow* _redShadow; //빨강이 그림자 선언

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

