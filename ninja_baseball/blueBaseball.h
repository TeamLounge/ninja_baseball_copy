#pragma once

#include "gameNode.h"
#include "bbState.h"


struct BLUEBASEBALL
{
	RECT rc;					//���ʹ� ��Ʈ
	RECT rcAttackRange;			//���� ���� ��Ʈ
	RECT rcStop;				//���� �浹 ��Ʈ

	image* img;

	float x, y;

};

struct BBSHADOW
{
	RECT rc;
	image* img;

	float x, y;

};

class blueBaseball :public gameNode
{

private:
	int _currentFrameX;
	int _currentFrameY;

	string _imgName;

public:

	void InputHandle();
	bbState* _bbState;

	BLUEBASEBALL _blueBaseball;
	BBSHADOW _bbShadow;

	//red* _red;

	bool isCrash;				//���ʹ̰� ���� ���� �ۿ��� ���ƴٴ��� �ʰ� ����

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
	bool isDeathDeleteState;	//�װ� ������ �غ� �ƴ��� �Ǻ��� bool��


	bool isattack;              //���ʹ̰� �����߾�??
	bool isdamage;				//���ʹ̰� ������ �޾Ҿ�??							
	bool iscatch;				//�����̰� ������??

	blueBaseball() {};
	~blueBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();


	//get
	//////////////////////////////////////
	inline RECT getRect() { return _blueBaseball.rc; }
	inline RECT getAttackRect() { return _blueBaseball.rcAttackRange; }

	float getCenterX() { return (_blueBaseball.rc.right + _blueBaseball.rc.left) / 2; }
	float getCenterY() { return (_blueBaseball.rc.bottom + _blueBaseball.rc.top) / 2; }

	float getX() { return _blueBaseball.x; }
	float getY() { return _blueBaseball.y; }

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

	void setX(float x) { _blueBaseball.x = x; }
	void setY(float y) { _blueBaseball.y = y; }

	RECT getShadowRect() { return _bbShadow.rc; }
	void setShadowRc(RECT rc) { _bbShadow.rc = rc; }

	float getShadowX() { return _bbShadow.x; }
	float getShadowY() { return _bbShadow.y; }

	void setShadowX(float x) { _bbShadow.x = x; }
	void setShadowY(float y) { _bbShadow.y = y; }

	void setRc(RECT rc) { _blueBaseball.rc = rc; }
};
