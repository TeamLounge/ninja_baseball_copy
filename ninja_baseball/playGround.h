#pragma once
#include "gameNode.h"
#include "player.h"
#include "titleScene.h"
#include "stageScene.h"
#include "endingScene.h"
#include "playerSelectScene.h"
#include "enemyManager.h"

class playGround : public gameNode
{
private:
	
	player* _red;
	/*player* _Ryno;*/

	enemyManager* _em;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

