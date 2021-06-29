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

public:

	void InputHandle();
	gloveState* _gloveState;

	GLOVE _glove;
	GLOVESHADOW _gloveShadow;

	bool isCrash;					//���ʹ̰� ���� ���� �ۿ��� ���ƴٴ��� �ʰ� ����

	bool isRight;					//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;					//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;			//���ʹ� ���ͼ� ĥ�ž�?
	bool isJump;					//�����߾�?
	bool isXOverlap;				//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;				//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)
	bool isLand;					//���� �� �ٴڿ� �����߳�!!!!


	//�̹��� ��ǥ ���� ���� bool����
	bool isAttackTongueState;
	bool isJumpState;

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


	inline RECT getRect() { return _glove.rc; }
	inline RECT getAttackRect() { return _glove.rcAttackRange; }

	float getCenterX() { return (_glove.rc.left + _glove.rc.right) / 2; }
	float getCenterY() { return (_glove.rc.top + _glove.rc.bottom) / 2; }

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

