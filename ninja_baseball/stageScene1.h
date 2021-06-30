#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
class stageScene1 : public gameNode
{
private:
	player* _red;
	player* _Ryno;

	enemyManager* _em;
	objectManager* _obj;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

