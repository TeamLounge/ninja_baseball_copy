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

	typedef vector<baseball*> vBaseball;
	typedef vector<baseball*>::iterator viBaseball;

	typedef vector<trashCan*> vTrashCan;
	typedef vector<trashCan*>::iterator viTrashCan;

	typedef vector<banana*> vBanana;
	typedef vector<banana*>::iterator viBanana;



	vBaseball _vball;
	viBaseball _viball;

	vTrashCan _vtrash;
	viTrashCan _vitrash;

	vBanana _vbana;
	vBanana _vbana;



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setBaseBall();
	void setTrahCan();
	void setBanana();

	void setLinkPlayer(player* player) { _player = player; }
	void setLinkEnemyManager(enemyManager* enemyManager) { _em = enemyManager; }

};

