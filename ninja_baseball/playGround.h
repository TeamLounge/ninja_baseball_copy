#pragma once
#include "gameNode.h"
#include "player.h"
#include "titleScene.h"
#include "startScene.h"
#include "stageScene1.h"
#include "stageScene2.h"
#include "stageScene3.h"
#include "endingScene.h"
#include "playerSelectScene.h"
#include "enemyManager.h"

class playGround : public gameNode
{
private:

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setMusic();
};

