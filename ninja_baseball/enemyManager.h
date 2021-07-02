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
	//          베이스볼 에너미
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
	//          배트 에너미
	/////////////////////////////////
	typedef vector<bat*>				vBat;
	typedef vector<bat*>::iterator		viBat;

	vBat	_vBat;
	viBat	_viBat;

	/////////////////////////////////
	//          글로브 에너미
	/////////////////////////////////
	typedef vector<glove*>				vGlove;
	typedef vector<glove*>::iterator	viGlove;

	vGlove	_vGlove;
	viGlove	_viGlove;

	/////////////////////////////////
	//          카드에너미
	/////////////////////////////////
	typedef vector<card*>				vCard;
	typedef vector<card*>::iterator		viCard;

	vCard _vCard;
	viCard _viCard;


	/////////////////////////////////
	// ######  보스 에너미 #########
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
	//  베이스볼 에너미 관련 함수
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

	void playerLocation();			//플레이어 위치 찾고 본인 위치와 비교하는 함수(베이스볼, 배트)
	void wallLoaction();			//벽 위치 찾고 선 넘지 않게 해주는 함수
	void baseballCollision();		//베이스볼과의 충돌 함수

	vector<whiteBaseball*> getVWb() { return _vWb; }
	vector<whiteBaseball*>::iterator getVIWb() { return _viWb; }

	vector<yellowBaseball*> getVYb() { return _vYb; }
	vector<yellowBaseball*>::iterator getVIYb() { return _viYb; }

	vector<greenBaseball*> getVGb() { return _vGb; }
	vector<greenBaseball*>::iterator getVIGb() { return _viGb; }

	vector<blueBaseball*> getVBb() { return _vBb; }
	vector<blueBaseball*>::iterator getVIBb() { return _viBb; }


	/////////////////////////////////
	//   배트 에너미 관련 함수
	////////////////////////////////

	void setBat1();	//stage1
	void setBat2();	//stage2
	void updateBat();
	void renderBat();

	void batCollision();		//배트와의 충돌 함수


	vector<bat*> getVBat() { return _vBat; }
	vector<bat*>::iterator getVIBat() { return _viBat; }

	/////////////////////////////////
	//   글로브 에너미 관련 함수
	////////////////////////////////

	void setGlove();
	void updateGlove();
	void renderGlove();

	void gloveCollision();		//글로브와의 충돌 함수


	vector<glove*> getVGlove() { return _vGlove; }
	vector<glove*>::iterator getVIGlove() { return _viGlove; }

	/////////////////////////////////
	//   카드에너미관련 함수
	////////////////////////////////
	void setCard();
	void updateCard();
	void renderCard();

	void WhereIsCard();
	void assultedCollisionCard();

	vector<card*> getVCard() { return _vCard; }
	vector<card*>::iterator getVICard() { return _viCard; }

	/////////////////////////////////
	//  ######보스 관련 함수 ########
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

