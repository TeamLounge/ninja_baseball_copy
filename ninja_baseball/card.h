#pragma once
#include "gameNode.h"
#include "cardState.h"

struct CARD
{
	RECT rc;
	float x, y;
	image* img;
};

//ī�� �����찡 ���� �����ǰ� �ؾߵȴ�.
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

	//�߷�
	float _gravity, _jumpPower;
	//���� �ӵ�
	float _speed;
	//����������, ���ݹ޾Ҵ���, ���������� ��� �Ұ� �����
	bool _isJump, _isLeft, _isDamaged, _isUpper, _isApex;
	//���� ��Ҵ��� Ȯ��
	bool _isRightWall, _isLeftWall, _isTopWall, _isBottomWall;
	//Dash �������� �ָԹ߻� �������� Ȯ�ο�
	bool _isDash, _isPunchBullet;
	//�÷��̾��� ���� X�� ����Y�� �޾ƿ����� �������.
	float _rpX, _rpY;
	//���ݿ� ��Ʈ
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

	//���� �Լ�
	void setIsUpper(bool isUpper) { _isUpper = isUpper; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsDash(bool isDash) { _isDash = isDash; }
	void setIsBullet(bool isPunchBullet) { _isPunchBullet = isPunchBullet; }
	void setIsDamaged(bool isDamaged) { _isDamaged = isDamaged; }
	void setIsJump(bool isJump) { _isJump = isJump; }

	//���� ����
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

