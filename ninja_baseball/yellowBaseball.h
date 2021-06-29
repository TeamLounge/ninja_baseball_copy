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


public:

	void InputHandle();
	ybState* _ybState;

	YELLOWBASEBALL _yellowBaseball;
	YBSHADOW _ybShadow;

	bool isCrash;

	bool isRight;				//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;				//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;		//���ʹ� Ÿ�ݹ����� ���Ծ�?
	bool isJump;				//�����߾�?
	bool isXOverlap;				//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;				//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)

	bool isattack;              //���ʹ̰� �����߾�??
	bool isdamage;				//���ʹ̰� ������ �޾Ҿ�??							
	bool iscatch;				//�����̰� ������??


	yellowBaseball() {};
	~yellowBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();

	inline RECT getRect() { return _yellowBaseball.rc; }
	inline RECT getAttackRect() { return _yellowBaseball.rcAttackRange; }

	float getCenterX() { return (_yellowBaseball.rc.right + _yellowBaseball.rc.left) / 2; }
	float getCenterY() { return (_yellowBaseball.rc.bottom + _yellowBaseball.rc.top) / 2; }


	void setIsRight(bool _isRight) { isRight = _isRight; }
	void setIsDown(bool _isDown) { isDown = _isDown; }
	void setIsCollisionAttack(bool _isCollisionAttack) { isCollisionAttack = _isCollisionAttack; }
	void setIsXOverlap(bool _isXOverlap) { isXOverlap = _isXOverlap; }
	void setIsYOverlap(bool _isYOverlap) { isYOverlap = _isYOverlap; }

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }

	void setCurrentFrameX(int currentX) { _currentFrameX = currentX; }
	void setCurrentFrameY(int currentY) { _currentFrameY = currentY; }
};
