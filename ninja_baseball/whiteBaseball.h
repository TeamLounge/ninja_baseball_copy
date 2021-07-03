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

	string _imgName;
	int _currentFrameX, _currentFrameY;
public:

	void InputHandle();
	wbState* _wbState;

	WHITEBASEBALL _whiteBaseball;
	WBSHADOW _wbShadow;

	//red* _red;

	bool isCrash;				//���ʹ̰� ���� ���� �ۿ��� ���ƴٴ��� �ʰ� ����
	
	bool isRight;				//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;				//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;		//���ʹ� ���ͼ� �����߾�?
	bool isCollisionDamaged;	//���ʹ� ���ͼ� �¾Ҿ�?
	bool isJump;				//�����߾�?
	bool isXOverlap;			//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;			//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)

	bool isDamaged;				//�¾Ҿ�?
	bool isDeath;				//count == 5�̰�, �׷��� �׾���?
	int damagedCount;			//���� Ƚ��
	int timeCount;

	bool isattack;              //���ʹ̰� �����߾�??
	bool isdamage;				//���ʹ̰� ������ �޾Ҿ�??							
	bool iscatch;				//�����̰� ������??

	float _x = _whiteBaseball.x;
	float _y = _whiteBaseball.y;

	whiteBaseball() {};
	~whiteBaseball() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setShadow();





	//get
	//////////////////////////////////////
	inline RECT getRect() { return _whiteBaseball.rc; }
	inline RECT getAttackRect() { return _whiteBaseball.rcAttackRange; }

	float getCenterX() { return (_whiteBaseball.rc.left + _whiteBaseball.rc.right) / 2; }
	float getCenterY() { return (_whiteBaseball.rc.top + _whiteBaseball.rc.bottom) / 2; }

	float getX() { return _whiteBaseball.x; }
	float getY() { return _whiteBaseball.y; }

	
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

	void setImageName(string imgName) { _imgName = imgName; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
};