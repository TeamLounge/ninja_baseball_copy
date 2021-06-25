#pragma once
#include "gameNode.h"
#include "player.h"
#include "redShadow.h" //������ �׸��� ���

class playGround : public gameNode
{
private:
	
	player* _red;
	
	redShadow* _redShadow; //������ �׸��� ����

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

