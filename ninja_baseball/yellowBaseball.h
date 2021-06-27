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

public:

	void InputHandle();
	ybState* _ybState;

	YELLOWBASEBALL _yellowBaseball;
	YBSHADOW _ybShadow;
	
	bool isCrash;

	bool isRight;				//에너미가 플레이어의 오른쪽에 있어?
	bool isDown;				//에너미가 플레이어의 아래에 있어?
	bool isCollisionAttack;		//에너미 타격범위에 들어왔어?
	bool isJump;				//점프했어?
	bool isXOverlap;				//에너미와 플레이어 중점이 X범위 안에서 비슷해? (떨림방지용)
	bool isYOverlap;				//에너미와 플레이어 중점이 Y범위 안에서 비슷해? (떨림방지용)



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

};
