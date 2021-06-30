#pragma once
#include "gameNode.h"
#include "object.h"

class player;
class enemyManager;

class objectManager : public gameNode
{
private:
	player* _player;
	enemyManager* _em;

	typedef vector<trashCan*> vTrashCan;
	typedef vector<trashCan*>::iterator viTrashCan;

	typedef vector<banana*> vBanana;
	typedef vector<banana*>::iterator viBanana;

	baseball* _ball;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setBaseBall();
	void setTrahCan();
	void setBanana();

	void collsion();

	void setLinkPlayer(player* player) { _player = player; }
	void setLinkEnemyManager(enemyManager* enemyManager) { _em = enemyManager; }

};

