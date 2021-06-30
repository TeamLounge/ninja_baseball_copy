#pragma once

#include "gameNode.h"
#include "batState.h"

struct BAT
{
	RECT rc;
	RECT rcAttackRange;
	RECT rcStop;

	image * img;

	float x, y;
};

struct BATSHADOW
{
	RECT rc;
	image* img;

	float x, y;
};

class bat :public gameNode
{
private:
	int _currentFrameX;
	int _currentFrameY;

public:
	void InputHandle();

	batState* _batState;

	BAT _bat;
	BATSHADOW _batShadow;

	bool isRight;				//에너미가 플레이어의 오른쪽에 있어?
	bool isDown;				//에너미가 플레이어의 아래에 있어?
	bool isCollisionAttack;		//에너미 들어와서 칠거야?
	bool isJump;		
	bool isXOverlap;			//에너미와 플레이어 중점이 X범위 안에서 비슷해? (떨림방지용)
	bool isYOverlap;			//에너미와 플레이어 중점이 Y범위 안에서 비슷해? (떨림방지용)
	bool isAttack;				//쳤어?
	bool isDamaged;				//맞았어?
	bool iscatch;				//잡혔어?

	bat() {};
	~bat() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();

	inline RECT getRect() { return _bat.rc; }
	inline RECT getAttackRect() { return _bat.rcAttackRange; }

	float getCenterX() { return (_bat.rc.left + _bat.rc.right) / 2; }
	float getCenterY() { return (_bat.rc.top + _bat.rc.bottom) / 2; }

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

