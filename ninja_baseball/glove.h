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

	bool isCrash;					//에너미가 감시 범위 밖에서 돌아다니지 않게 하자

	bool isRight;					//에너미가 플레이어의 오른쪽에 있어?
	bool isDown;					//에너미가 플레이어의 아래에 있어?
	bool isCollisionAttack;			//에너미 들어와서 공격했어?
	bool isCollisionDamaged;		//에너미 들어와서 맞았어?
	bool isJump;					//점프했어?
	bool isXOverlap;				//에너미와 플레이어 중점이 X범위 안에서 비슷해? (떨림방지용)
	bool isYOverlap;				//에너미와 플레이어 중점이 Y범위 안에서 비슷해? (떨림방지용)
	bool isLand;					//점프 후 바닥에 도착했냐!!!!
	bool isDamaged;					//맞았어?
	bool isDeath;					//count == 5이고, 그래서 죽었어?

	int damageCount;				//맞은 횟수
	int timeCount;					//공격 인터벌 주기 위함

	bool isattack;					//에너미가 공격했어??
	bool isdamage;					//에너미가 데미지 받았어??							
	bool iscatch;					//에저미가 잡혔어??


	//이미지 좌표 수정 위한 bool값들
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
	void setIsCollisionDamaged(bool _isCollisionDamaged) { isCollisionDamaged = _isCollisionDamaged; }
	void setIsXOverlap(bool _isXOverlap) { isXOverlap = _isXOverlap; }
	void setIsYOverlap(bool _isYOverlap) { isYOverlap = _isYOverlap; }

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }

	void setCurrentFrameX(int currentX) { _currentFrameX = currentX; }
	void setCurrentFrameY(int currentY) { _currentFrameY = currentY; }

	void setImageName(string s) { _imgName = s; }
};

