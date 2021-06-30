#pragma once

#include "gameNode.h"
#include "gbState.h"


struct GREENBASEBALL
{
	RECT rc;					//���ʹ� ��Ʈ
	RECT rcAttackRange;			//���� ���� ��Ʈ
	RECT rcStop;				//���� �浹 ��Ʈ

	image* img;

	float x, y;

};

struct GBSHADOW
{
	RECT rc;
	image* img;

	float x, y;

};

class greenBaseball :public gameNode
{

private:
	int _currentFrameX;
	int _currentFrameY;

public:

	void InputHandle();
	gbState* _gbState;

	GREENBASEBALL _greenBaseball;
	GBSHADOW _gbShadow;


	bool isCrash;				//���ʹ̰� ���� ���� �ۿ��� ���ƴٴ��� �ʰ� ����

	bool isRight;				//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;				//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;		//���ʹ� ���ͼ� ĥ�ž�?
	bool isJump;				//�����߾�?
	bool isXOverlap;				//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;				//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)

	bool isattack;              //���ʹ̰� �����߾�??
	bool isdamage;				//���ʹ̰� ������ �޾Ҿ�??							
	bool iscatch;				//�����̰� ������??


	greenBaseball() {};
	~greenBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();

	inline RECT getRect() { return _greenBaseball.rc; }
	inline RECT getAttackRect() { return _greenBaseball.rcAttackRange; }

	float getCenterX() { return (_greenBaseball.rc.right + _greenBaseball.rc.left) / 2; }
	float getCenterY() { return (_greenBaseball.rc.bottom + _greenBaseball.rc.top) / 2; }


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
