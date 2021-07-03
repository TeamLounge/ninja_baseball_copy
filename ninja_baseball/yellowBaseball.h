#pragma once

#include "gameNode.h"
#include "ybState.h"

struct YELLOWBASEBALL
{
	RECT rc;
	RECT rcAttackRange;
	RECT rcStop;

	image* img;

	float x, y;

};

struct YBSHADOW
{
	RECT rc;
	image* img;

	float x, y;
};

class yellowBaseball :public gameNode
{
private:
	int _currentFrameX;
	int _currentFrameY;

	string _imgName;

public:

	void InputHandle();
	ybState* _ybState;

	YELLOWBASEBALL _yellowBaseball;
	YBSHADOW _ybShadow;

	bool isCrash;

	bool isRight;				//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;				//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;		//���ʹ� ���ͼ� �����߾�?
	bool isCollisionDamaged;	//���ʹ� ���ͼ� �¾Ҿ�?
	bool isJump;				//�����߾�?
	bool isXOverlap;			//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;			//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)

	bool isDamaged;				//�¾Ҿ�?
	bool isDeath;				//�׾���?
	int damagedCount;			//���� Ƚ��
	int timeCount;

	bool isattack;              //���ʹ̰� �����߾�??
	bool isdamage;				//���ʹ̰� ������ �޾Ҿ�??
	bool iscatch;				//�����̰� ������??
	bool isGreenFly;			//Green�� ���Ҿ�?
	bool isDeathDeleteState;	//�װ� ������ �غ� �ƴ��� �Ǻ��� bool��


	yellowBaseball() {};
	~yellowBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();

	//get
	//////////////////////////////////////
	inline RECT getRect() { return _yellowBaseball.rc; }
	inline RECT getAttackRect() { return _yellowBaseball.rcAttackRange; }

	float getCenterX() { return (_yellowBaseball.rc.right + _yellowBaseball.rc.left) / 2; }
	float getCenterY() { return (_yellowBaseball.rc.bottom + _yellowBaseball.rc.top) / 2; }

	float getX() { return _yellowBaseball.x; }
	float getY() { return _yellowBaseball.y; }

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

	void setX(float x) { _yellowBaseball.x = x; }
	void setY(float y) { _yellowBaseball.y = y; }

	RECT getShadowRect() { return _ybShadow.rc; }
	void setShadowRc(RECT rc) { _ybShadow.rc = rc; }

	float getShadowX() { return _ybShadow.x; }
	float getShadowY() { return _ybShadow.y; }

	void setShadowX(float x) { _ybShadow.x = x; }
	void setShadowY(float y) { _ybShadow.y = y; }

	void setRc(RECT rc) { _yellowBaseball.rc = rc; }
};
