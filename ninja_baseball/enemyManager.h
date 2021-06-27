#pragma once

#include "gameNode.h"
#include "whiteBaseball.h"
#include "yellowBaseball.h"
#include "greenBaseball.h"
#include "blueBaseball.h"
#include "card.h"
#include <vector>

class player;

class enemyManager : public gameNode
{
private:
	typedef vector<whiteBaseball*>				vWhiteBaseball;
	typedef vector<whiteBaseball*>::iterator	viWhiteBaseball;

	typedef vector<yellowBaseball*>				vYellowBaseball;
	typedef vector<yellowBaseball*>::iterator	viYellowBaseball;

	typedef vector<greenBaseball*>				vGreenBaseball;
	typedef vector<greenBaseball*>::iterator	viGreenBaseball;

	typedef vector<blueBaseball*>				vBlueBaseball;
	typedef vector<blueBaseball*>::iterator		viBlueBaseball;

	vWhiteBaseball		_vWb;
	viWhiteBaseball		_viWb;

	vYellowBaseball		_vYb;
	viYellowBaseball	_viYb;

	vGreenBaseball		_vGb;
	viGreenBaseball		_viGb;

	vBlueBaseball		_vBb;
	viBlueBaseball		_viBb;

	typedef vector<card*>				vCard;
	typedef vector<card*>::iterator		viCard;

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

	vector<yellowBaseball*> getVYb() { return _vYb; }
	vector<yellowBaseball*>::iterator getVIYb() { return _viYb; }

	vector<greenBaseball*> getVGb() { return _vGb; }
	vector<greenBaseball*>::iterator getVIGb() { return _viGb; }

	vector<blueBaseball*> getVBb() { return _vBb; }
	vector<blueBaseball*>::iterator getVIBb() { return _viBb; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	void setBaseball();
	void updateBaseball();
	void renderBaseball();

	void playerLocation();			//�÷��̾� ��ġ ã�� ���� ��ġ�� ���ϴ� �Լ�
	void baseballCollision();		//�÷��̾���� �浹 �Լ�

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

