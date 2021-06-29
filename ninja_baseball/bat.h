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

	bool isRight;				//���ʹ̰� �÷��̾��� �����ʿ� �־�?
	bool isDown;				//���ʹ̰� �÷��̾��� �Ʒ��� �־�?
	bool isCollisionAttack;		//���ʹ� ���ͼ� �����߾�?
	bool isCollisionDamaged;	//���ʹ� ���ͼ� �¾Ҿ�?
	bool isJump;		
	bool isXOverlap;			//���ʹ̿� �÷��̾� ������ X���� �ȿ��� �����? (����������)
	bool isYOverlap;			//���ʹ̿� �÷��̾� ������ Y���� �ȿ��� �����? (����������)
	bool isAttack;				//�ƾ�?
	bool isDamaged;				//�¾Ҿ�?

	//��Ʈ �ܰ�
	bool noCap;			//step1 : ���� ������
	bool noBat;			//step2 : ��Ʈ ���ư�
	bool death;			//step3 : ����

	int damageCount;	//��Ʈ�� 3�ܰ� ������ ���� ī��Ʈ
						//�ǰ�(count)  1~2ȸ : ���� x
						//�ǰ�			3ȸ : 1�ܰ� ����<noCap mode>	..���� ���ư�;
						//�ǰ�			4ȸ : 2�ܰ� ����<noBat mode>	..��Ʈ ���ư�;	(���ڶ� ��Ʈ�� ȸ�� ���� �״�� ���ư�����, ī�޶� �� �°� ƨ�� + ���ķ���)
						//�ǰ�			5ȸ : 3�ܰ� ����<death mode>	..����;			(360�� ȸ���ϸ� ���ư��ٰ� ���ķ���)

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
	void setIsCollisionDamaged(bool _isCollisionDamaged) { isCollisionDamaged = _isCollisionDamaged; }
	void setIsXOverlap(bool _isXOverlap) { isXOverlap = _isXOverlap; }
	void setIsYOverlap(bool _isYOverlap) { isYOverlap = _isYOverlap; }

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }

	void setCurrentFrameX(int currentX) { _currentFrameX = currentX; }
	void setCurrentFrameY(int currentY) { _currentFrameY = currentY; }
};

