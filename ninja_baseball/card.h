#pragma once
#include "gameNode.h"
#include "cardState.h"

struct CARD
{
	RECT rc;
	float x, y;
	image* img;
};

//카드 쉐도우가 먼저 렌더되게 해야된다.
struct CARDSHADOW
{
	RECT rc;
	float x, y;
	image* img;
};


class card : public gameNode
{
private:
	
public:
	cardState* _cardState;
	CARDSHADOW _cardShadow;
	CARD _card;

	void InputHandle();

	//중력
	float _gravity, _jumpPower;
	//무브 속도
	float _speed;
	//점프중인지, 공격받았는지, 공격중인지 등등 불값 적용들
	bool _isJump, _isLeft, _isDamaged, _isUpper, _isApex;
	//벽에 닿았는지 확인
	bool _isRightWall, _isLeftWall, _isTopWall, _isBottomWall;
	//Dash 어택인지 주먹발사 어택인지 확인용
	bool _isDash, _isPunchBullet;
	//플레이어의 센터 X와 센터Y를 받아오려고 만들었음.
	float _rpX, _rpY;
	//공격용 렉트
	RECT _atkRc;

	card();
	~card();

	virtual HRESULT init();	
	virtual HRESULT init( POINT position);
	virtual void release();
	virtual void update();
	virtual void render();	

	void setImage();
	void setCard();
	void setCardShadow();
	void getGravity();

	//세터 함수
	void setIsUpper(bool isUpper) { _isUpper = isUpper; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsDash(bool isDash) { _isDash = isDash; }
	void setIsBullet(bool isPunchBullet) { _isPunchBullet = isPunchBullet; }
	void setIsDamaged(bool isDamaged) { _isDamaged = isDamaged; }
	void setIsJump(bool isJump) { _isJump = isJump; }

	//게터 설정
	RECT getCardRc() { return _card.rc; }
	RECT getAtkCardRc() { return _atkRc; }
	float getCenterX() { return (_card.rc.left + _card.rc.right) / 2; }
	float getCenterY() { return (_card.rc.top + _card.rc.bottom) / 2; }
	bool getIsUpper() { return _isUpper; }
	bool getIsLeft() { return _isLeft; }
	bool getIsDash() { return _isDash; }
	bool getIsBullet() { return _isPunchBullet; }
};

class card
{
};

