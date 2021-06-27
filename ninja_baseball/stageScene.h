#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
class stageScene : public gameNode
{
private:
	player* _red;
	player* _Ryno;

	enemyManager* _em;

	RECT _rc;
	int _count;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

