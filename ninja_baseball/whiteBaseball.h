#pragma once

#include "gameNode.h"
#include "wbState.h"

//red랑 상호참조 해보자
//class red;

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

public:

	void InputHandle();
	wbState* _wbState;

	WHITEBASEBALL _whiteBaseball;
	WBSHADOW _wbShadow;

	//red* _red;

	bool isCrash;				//에너미가 감시 범위 밖에서 돌아다니지 않게 하자
	
	bool isRight;				//에너미가 플레이어의 오른쪽에 있어?
	bool isDown;				//에너미가 플레이어의 아래에 있어?
	bool isCollisionAttack;		//에너미 들어와서 칠거야?
	bool isJump;				//점프했어?


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
	

	void setIsRight(bool _isRight) { isRight = _isRight; }
	void setIsDown(bool _isDown) { isDown = _isDown; }
	void setIsCollisionAttack(bool _isCollisionAttack) { isCollisionAttack = _isCollisionAttack; }

	//상호참조 위함
	//void setRedMemoryAddressLink(red* red) { _red = red; }


};

class whiteBaseball
{
};
