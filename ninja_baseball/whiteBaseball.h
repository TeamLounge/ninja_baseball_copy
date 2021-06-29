#pragma once

#include "gameNode.h"
#include "wbState.h"

struct WHITEBASEBALL
{
	RECT rc;					//에너미 렉트
	RECT rcAttackRange;			//공격 범위 렉트
	RECT rcStop;				//등장 충돌 렉트

	image* img;

	float x, y;

};

struct WBSHADOW
{
	RECT rc;
	image* img;

	float x, y;

};

class whiteBaseball :public gameNode
{

private:

	string _imgName;
	int _currentFrameX, _currentFrameY;
public:

	void InputHandle();
	wbState* _wbState;

	WHITEBASEBALL _whiteBaseball;
	WBSHADOW _wbShadow;

	//red* _red;

	bool isCrash;				//에너미가 감시 범위 밖에서 돌아다니지 않게 하자
	
	bool isRight;				//에너미가 플레이어의 오른쪽에 있어?
	bool isDown;				//에너미가 플레이어의 아래에 있어?
	bool isCollisionAttack;		//에너미 들어와서 공격했어?
	bool isCollisionDamaged;	//에너미 들어와서 맞았어?
	bool isJump;				//점프했어?
	bool isXOverlap;				//에너미와 플레이어 중점이 X범위 안에서 비슷해? (떨림방지용)
	bool isYOverlap;				//에너미와 플레이어 중점이 Y범위 안에서 비슷해? (떨림방지용)

	bool isattack;
	bool isdamage;
	bool iscatch;

	whiteBaseball() {};
	~whiteBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();
	
	inline RECT getRect() { return _whiteBaseball.rc; }
	inline RECT getAttackRect() { return _whiteBaseball.rcAttackRange; }

	float getCenterX() { return (_whiteBaseball.rc.left + _whiteBaseball.rc.right) / 2; }
	float getCenterY() { return (_whiteBaseball.rc.top + _whiteBaseball.rc.bottom) / 2; }
	

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

	void setImageName(string imgName) { _imgName = imgName; }
};