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

	vTrashCan _vtrash;
	viTrashCan _vitrash;

	baseball* _ball;
	banana* _banana;
	cereal* _cereal;
	goldbat* _goldbat;

	int catchtime;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void goldrender();

	void setBaseBall();
	void setTrahCan();
	void setBanana();
	void setCereal();
	void setgoldbat(float x, float y);

	void updateBall();
	void updateBanana();
	void updateCereal();
	void updategoldbat();
	
	void collsion();
	void goldbatCollsion();
	
	void setLinkPlayer(player* player) { _player = player; }
	void setLinkEnemyManager(enemyManager* enemyManager) { _em = enemyManager; }

};

