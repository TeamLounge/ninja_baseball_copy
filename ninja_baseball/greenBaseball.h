#pragma once

#include "gameNode.h"
#include "gbState.h"


struct GREENBASEBALL
{
	RECT rc;					//에너미 렉트
	RECT rcAttackRange;			//공격 범위 렉트
	RECT rcStop;				//등장 충돌 렉트

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

	string _imgName;

public:

	void InputHandle();
	gbState* _gbState;

	GREENBASEBALL _greenBaseball;
	GBSHADOW _gbShadow;


	bool isCrash;				//에너미가 감시 범위 밖에서 돌아다니지 않게 하자

	bool isRight;				//에너미가 플레이어의 오른쪽에 있어?
	bool isDown;				//에너미가 플레이어의 아래에 있어?
	bool isCollisionAttack;		//에너미 들어와서 공격했어?
	bool isCollisionDamaged;	//에너미 들어와서 맞았어?
	bool isJump;				//점프했어?
	bool isXOverlap;			//에너미와 플레이어 중점이 X범위 안에서 비슷해? (떨림방지용)
	bool isYOverlap;			//에너미와 플레이어 중점이 Y범위 안에서 비슷해? (떨림방지용)

	bool isDamaged;				//맞았어?
	bool isDeath;				//죽었나?
	bool isLand;
	int damagedCount;			//맞은 횟수
	int timeCount;
	bool isDeathDeleteState;	//죽고 지워줄 준비가 됐는지 판별할 bool값

	bool isattack;              //에너미가 공격했어??
	bool isdamage;				//에너미가 데미지 받았어??							
	bool iscatch;				//에저미가 잡혔어??

	bool isPlayerReached;		//플레이어 특정 좌표 도착했어?


	greenBaseball() {};
	~greenBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();

	//get
	//////////////////////////////////////
	inline RECT getRect() { return _greenBaseball.rc; }
	inline RECT getAttackRect() { return _greenBaseball.rcAttackRange; }

	float getCenterX() { return (_greenBaseball.rc.right + _greenBaseball.rc.left) / 2; }
	float getCenterY() { return (_greenBaseball.rc.bottom + _greenBaseball.rc.top) / 2; }

	float getX() { return _greenBaseball.x; }
	float getY() { return _greenBaseball.y; }

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

	void setX(float x) { _greenBaseball.x = x; }
	void setY(float y) { _greenBaseball.y = y; }

	RECT getShadowRect() { return _gbShadow.rc; }
	void setShadowRc(RECT rc) { _gbShadow.rc = rc; }

	float getShadowX() { return _gbShadow.x; }
	float getShadowY() { return _gbShadow.y; }

	void setShadowX(float x) { _gbShadow.x = x; }
	void setShadowY(float y) { _gbShadow.y = y; }

	void setRc(RECT rc) { _greenBaseball.rc = rc; }
};
