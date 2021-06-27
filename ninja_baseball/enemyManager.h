#pragma once

#include "gameNode.h"
#include "whiteBaseball.h"
#include "card.h"
#include <vector>

class player;

class enemyManager : public gameNode
{
private:
	typedef vector<whiteBaseball*>				vWhiteBaseball;
	typedef vector<whiteBaseball*>::iterator	viWhiteBaseball;

	typedef vector<card*>				vCard;
	typedef vector<card*>::iterator		viCard;

private:
	vWhiteBaseball  _vWb;
	viWhiteBaseball _viWb;

	/////////////////////////////////
	//          ī�忡�ʹ�
	/////////////////////////////////
	vCard _vCard;
	viCard _viCard;

	player* _player;
	
public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	vector<whiteBaseball*> getVWb() { return _vWb; }
	vector<whiteBaseball*>::iterator getVIWb() { return _viWb; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	void setWB();
	void updateWB();
	void renderWB();

	void playerLocation();

	void collision();

	/////////////////////////////////
	//   ī�忡�ʹ̰��� �Լ�
	////////////////////////////////
	void setCard();
	void updateCard();
	void renderCard();

	void WhereIsCard();

	vector<card*> getVCard()			{ return _vCard; }
	vector<card*>::iterator getVICard() { return _viCard; }
};

