#pragma once

#include "gameNode.h"
#include "wbState.h"

//red�� ��ȣ���� �غ���
//class red;

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

	//��ȣ���� ����
	//void setRedMemoryAddressLink(red* red) { _red = red; }


};

class whiteBaseball
{
};
