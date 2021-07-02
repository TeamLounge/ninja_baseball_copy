#pragma once

#include "gameNode.h"
#include "whiteBaseball.h"
#include "yellowBaseball.h"
#include "greenBaseball.h"
#include "blueBaseball.h"
#include "bat.h"
#include "glove.h"
#include "card.h"
#include "boss.h"
#include <vector>

class player;

class enemyManager : public gameNode
{
private:
	player* _player;

	/////////////////////////////////
	//          ���̽��� ���ʹ�
	/////////////////////////////////
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

	/////////////////////////////////
	//          ��Ʈ ���ʹ�
	/////////////////////////////////
	typedef vector<bat*>				vBat;
	typedef vector<bat*>::iterator		viBat;

	vBat	_vBat;
	viBat	_viBat;

	/////////////////////////////////
	//          �۷κ� ���ʹ�
	/////////////////////////////////
	typedef vector<glove*>				vGlove;
	typedef vector<glove*>::iterator	viGlove;

	vGlove	_vGlove;
	viGlove	_viGlove;

	/////////////////////////////////
	//          ī�忡�ʹ�
	/////////////////////////////////
	typedef vector<card*>				vCard;
	typedef vector<card*>::iterator		viCard;

	vCard _vCard;
	viCard _viCard;


	/////////////////////////////////
	// ######  ���� ���ʹ� #########
	/////////////////////////////////
	boss* _boss;

	bool isdamage;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	/////////////////////////////////
	//  ���̽��� ���ʹ� ���� �Լ�
	////////////////////////////////

	void setBlueBaseball();
	void setGreenBaseball();
	void setWhiteBaseball();
	void setYellowBaseball();

	void updateBlueBaseball();
	void updateGreenBaseball();
	void updateWhiteBaseball();
	void updateYellowBaseball();

	void renderBlueBaseball();
	void renderGreenBaseball();
	void renderWhiteBaseball();
	void renderYellowBaseball();

	void playerLocation();			//�÷��̾� ��ġ ã�� ���� ��ġ�� ���ϴ� �Լ�(���̽���, ��Ʈ)
	void wallLoaction();			//�� ��ġ ã�� �� ���� �ʰ� ���ִ� �Լ�
	void baseballCollision();		//���̽������� �浹 �Լ�

	vector<whiteBaseball*> getVWb() { return _vWb; }
	vector<whiteBaseball*>::iterator getVIWb() { return _viWb; }

	vector<yellowBaseball*> getVYb() { return _vYb; }
	vector<yellowBaseball*>::iterator getVIYb() { return _viYb; }

	vector<greenBaseball*> getVGb() { return _vGb; }
	vector<greenBaseball*>::iterator getVIGb() { return _viGb; }

	vector<blueBaseball*> getVBb() { return _vBb; }
	vector<blueBaseball*>::iterator getVIBb() { return _viBb; }


	/////////////////////////////////
	//   ��Ʈ ���ʹ� ���� �Լ�
	////////////////////////////////

	void setBat1();	//stage1
	void setBat2();	//stage2
	void updateBat();
	void renderBat();

	void batCollision();		//��Ʈ���� �浹 �Լ�


	vector<bat*> getVBat() { return _vBat; }
	vector<bat*>::iterator getVIBat() { return _viBat; }

	/////////////////////////////////
	//   �۷κ� ���ʹ� ���� �Լ�
	////////////////////////////////

	void setGlove();
	void updateGlove();
	void renderGlove();

	void gloveCollision();		//�۷κ���� �浹 �Լ�


	vector<glove*> getVGlove() { return _vGlove; }
	vector<glove*>::iterator getVIGlove() { return _viGlove; }

	/////////////////////////////////
	//   ī�忡�ʹ̰��� �Լ�
	////////////////////////////////
	void setCard();
	void updateCard();
	void renderCard();

	void WhereIsCard();
	void assultedCollisionCard();

	vector<card*> getVCard() { return _vCard; }
	vector<card*>::iterator getVICard() { return _viCard; }

	/////////////////////////////////
	//  ######���� ���� �Լ� ########
	/////////////////////////////////
	void setBoss();
	void updateBoss();
	void renderBoss();

	void WhereIsBoss();
	void attackCollision();
	void pinRender();

	boss* getBoss() { return _boss; }
	void assultedCollisionBoss();
};

