#pragma once

#include "gameNode.h"
#include "wbState.h"

struct WHITEBASEBALL
{
	RECT rc;					//���ʹ� ��Ʈ
	RECT rcAttackRange;			//���� ���� ��Ʈ
	RECT rcStop;				//���� �浹 ��Ʈ

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

	bool isCrash;				//���ʹ̰� ���� ���� �ۿ��� ���ƴٴ��� �ʰ� ����
	
	bool isRight;				//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;				//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;		//���ʹ� ���ͼ� ĥ�ž�?
	bool isJump;				//�����߾�?
	bool isXOverlap;				//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;				//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)


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
	void setIsXOverlap(bool _isXOverlap) { isXOverlap = _isXOverlap; }
	void setIsYOverlap(bool _isYOverlap) { isYOverlap = _isYOverlap; }

	//��ȣ���� ����
	//void setRedMemoryAddressLink(red* red) { _red = red; }


};