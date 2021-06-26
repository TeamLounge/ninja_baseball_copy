#pragma once
#include "gameNode.h"
#include "card.h"
#include "cardState.h"
#include <vector>

class rectPlayer;

class enemyManager : public gameNode
{
private:
	typedef vector<card*>			vCard;
	typedef vector<card*>::iterator viCard;

private:
	rectPlayer* _rp;

	vCard _vCard;
	viCard _viCard;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setCard();
	void updateCard();
	void renderCard();

	void WhereIsCard();

	void setRPMemoryAddressLink(rectPlayer* rp) { _rp = rp; }

	vector<card*> getVCard() { return _vCard; }
	vector<card*>::iterator getVICard() { return _viCard; }
};

class enemyManager
{
};

