#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"


void greenBaseball::InputHandle()
{
	gbState* newState = _gbState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_gbState);
		_gbState = newState;
		_gbState->enter(this);
	}
}

HRESULT greenBaseball::init()
{

	return S_OK;
}

HRESULT greenBaseball::init(POINT position)		//POINT : x, y�� ���� �ҷ����� ��
{
	setImage();
	_greenBaseball.img = new image();

	setShadow();

	_gbState = new gbIdleState();		//Hang���� �����ҰŴϱ� �ٲ���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	_gbState->enter(this);

	_greenBaseball.x = position.x;
	_greenBaseball.y = position.y;		//������ �Է°� �޾ƿðŰ�

	//�̹��� ��ǥ ��
	_greenBaseball.img->setX(_greenBaseball.x);
	_greenBaseball.img->setY(_greenBaseball.y);	//�̹����� ��ǥ�� �°� �ѷ����

	//���� �浹 ��Ʈ
	_greenBaseball.rcStop = RectMakeCenter(_greenBaseball.x - RND->getFromIntTo(800, 900), _greenBaseball.y + 200, 50, 100);

	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isJump = false;
	isXOverlap == false;
	isYOverlap == false;

	return S_OK;
}


void greenBaseball::release()
{
	_gbState->exit(this);
}

void greenBaseball::update()
{
	InputHandle();
	_gbState->update(this);



	//���ʹ�
	_greenBaseball.rc = RectMakeCenter(_greenBaseball.x + 200, _greenBaseball.y + 200, 300, 230);

	if (!isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_gbShadow.rc = RectMakeCenter((_greenBaseball.rc.right + _greenBaseball.rc.left) / 2, _greenBaseball.rc.bottom, 215, 50);
		_gbShadow.y = _greenBaseball.rc.bottom;	//�����ϱ� �������� y���� ��� ������.

	}
	else   //�����ϸ� �׸��� �нż�
	{
		//�׸���
		_gbShadow.rc = RectMakeCenter((_greenBaseball.rc.right + _greenBaseball.rc.left) / 2, _gbShadow.y, 215, 50);	//�����ϱ� ���� y���� ���
	}



}

void greenBaseball::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _greenBaseball.rcAttackRange);	//���� ���� ��Ʈ
		Rectangle(getMemDC(), _greenBaseball.rc);				//���ʹ� ��Ʈ
		Rectangle(getMemDC(), _gbShadow.rc);					//�׸��� ��Ʈ

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
	
	//Rectangle(getMemDC(), _greenBaseball.rcStop);			//���� �浹 ��Ʈ

	_gbShadow.img->render(getMemDC(), _gbShadow.rc.left, _gbShadow.rc.top);
	_greenBaseball.img->frameRender(getMemDC(), _greenBaseball.x, _greenBaseball.y, _gbState->getCurrentFrameX(), _gbState->getCurrentFrameY());
	//_greenBaseball.img->frameRender(getMemDC(), _greenBaseball.rc.left, _greenBaseball.rc.top);


}

void greenBaseball::setImage()
{
	IMAGEMANAGER->addFrameImage("gBaseball_move", "image/3_Enemy/baseball/gBaseball_move.bmp", 2880, 600, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_idle", "image/3_Enemy/baseball/gBaseball_idle.bmp", 1080, 600, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_damaged", "image/3_Enemy/baseball/gBaseball_damaged.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_hang", "image/3_Enemy/baseball/gBaseball_hang.bmp", 360, 600, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_kick", "image/3_Enemy/baseball/gBaseball_kick.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_land", "image/3_Enemy/baseball/gBaseball_land.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_punch", "image/3_Enemy/baseball/gBaseball_punch.bmp", 720, 600, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_roll", "image/3_Enemy/baseball/gBaseball_roll.bmp", 4320, 600, 12, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_spin", "image/3_Enemy/baseball/gBaseball_spin.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("gBaseball_stop", "image/3_Enemy/baseball/gBaseball_stop.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("gBaseball_deathL", "image/3_Enemy/baseball/gBaseball_deathL.bmp", 360, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("gBaseball_deathR", "image/3_Enemy/baseball/gBaseball_deathR.bmp", 360, 300, true, RGB(255, 0, 255), false);

}

void greenBaseball::setShadow()
{
	IMAGEMANAGER->addImage("gBaseball_shadow", "image/3_Enemy/baseball/gBaseball_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_gbShadow.img = IMAGEMANAGER->findImage("gBaseball_shadow");
}
