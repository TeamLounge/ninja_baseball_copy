#pragma once

#include "gameNode.h"
#include "gloveState.h"

struct GLOVE
{
	RECT rc;
	RECT rcAttackRange;
	//RECT rcStop;

	image* img;
	
	float x, y;
};

struct GLOVESHADOW
{
	RECT rc;
	image* img;

	float x, y;
};

class glove :public gameNode
{
private:
	int _currentFrameX;
	int _currentFrameY;

	string _imgName;

public:

	void InputHandle();
	gloveState* _gloveState;

	GLOVE _glove;
	GLOVESHADOW _gloveShadow;

	bool isCrash;					//���ʹ̰� ���� ���� �ۿ��� ���ƴٴ��� �ʰ� ����

	bool isRight;					//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;					//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;			//���ʹ� ���ͼ� �����߾�?
	bool isCollisionDamaged;		//���ʹ� ���ͼ� �¾Ҿ�?
	bool isJump;					//�����߾�?
	bool isXOverlap;				//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;				//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)
	bool isLand;					//���� �� �ٴڿ� �����߳�!!!!
	bool isDamaged;					//�¾Ҿ�?
	bool isDeath;					//count == 5�̰�, �׷��� �׾���?

	int damagedCount;				//���� Ƚ��
	int timeCount;					//���� ���͹� �ֱ� ����
	bool isDeathDeleteState;	//�װ� ������ �غ� �ƴ��� �Ǻ��� bool��

	bool isattack;					//���ʹ̰� �����߾�??
	bool isdamage;					//���ʹ̰� ������ �޾Ҿ�??							
	bool iscatch;					//�����̰� ������??

	//�̹��� ��ǥ ���� ���� bool����
	bool isAttackTongueState;
	bool isJumpState;
	bool isMoveState;

	glove() {};
	~glove() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();
	void modifiedLocation();

	//get
	//////////////////////////////////////
	inline RECT getRect() { return _glove.rc; }
	inline RECT getAttackRect() { return _glove.rcAttackRange; }

	float getCenterX() { return (_glove.rc.left + _glove.rc.right) / 2; }
	float getCenterY() { return (_glove.rc.top + _glove.rc.bottom) / 2; }
	
	float getX() { return _glove.x; }
	float getY() { return _glove.y; }

	//set
	//////////////////////////////////////
	void setIsRight(bool _isRight) { isRight = _isRight; }
	void setIsDown(bool _isDown) { isDown = _isDown; }
	void setIsCollisionAttack(bool _isCollisionAttack) { isCollisionAttack = _isCollisionAttack; }
	void setIsCollisionDamaged(bool _isCollisionDamaged) { isCollisionDamaged = _isCollisionDamaged; }
	void setIsXOverlap(bool _isXOverlap) { isXOverlap = _isXOverlap; }
	void setIsYOverlap(bool _isYOverlap) { isYOverlap = _isYOverlap; }

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }

	void setCurrentFrameX(int currentX) { _currentFrameX = currentX; }
	void setCurrentFrameY(int currentY) { _currentFrameY = currentY; }

	void setImageName(string s) { _imgName = s; }

	void setX(float x) { _glove.x = x; }
	void setY(float y) { _glove.y = y; }

	RECT getShadowRect() { return _gloveShadow.rc; }
	void setShadowRc(RECT rc) { _gloveShadow.rc = rc; }

	float getShadowX() { return _gloveShadow.x; }
	float getShadowY() { return _gloveShadow.y; }

	void setShadowX(float x) { _gloveShadow.x = x; }
	void setShadowY(float y) { _gloveShadow.y = y; }

	void setRc(RECT rc) { _glove.rc = rc; }
};

