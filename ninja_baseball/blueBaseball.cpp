#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"


void blueBaseball::InputHandle()
{
	bbState* newState = _bbState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_bbState);
		_bbState = newState;
		_bbState->enter(this);
	}
}

HRESULT blueBaseball::init()
{

	return S_OK;
}

HRESULT blueBaseball::init(POINT position)		//POINT : x, y�� ���� �ҷ����� ��
{
	setImage();
	_blueBaseball.img = new image();

	setShadow();

	_bbState = new bbIdleState();
	_bbState->enter(this);

	_blueBaseball.x = position.x;
	_blueBaseball.y = position.y;		//������ �Է°� �޾ƿðŰ�

	//�̹��� ��ǥ ��
	_blueBaseball.img->setX(_blueBaseball.x);
	_blueBaseball.img->setY(_blueBaseball.y);	//�̹����� ��ǥ�� �°� �ѷ����

	//���� �浹 ��Ʈ
	_blueBaseball.rcStop = RectMakeCenter(_blueBaseball.x - RND->getFromIntTo(800, 900), _blueBaseball.y + 200, 50, 100);

	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isJump = false;
	isXOverlap == false;
	isYOverlap == false;

	return S_OK;
}


void blueBaseball::release()
{
	_bbState->exit(this);
}

void blueBaseball::update()
{
	InputHandle();
	_bbState->update(this);



	//���ʹ�
	_blueBaseball.rc = RectMakeCenter(_blueBaseball.x + 200, _blueBaseball.y + 200, 300, 230);

	if (!isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_bbShadow.rc = RectMakeCenter((_blueBaseball.rc.right + _blueBaseball.rc.left) / 2, _blueBaseball.rc.bottom, 215, 50);
		_bbShadow.y = _blueBaseball.rc.bottom;	//�����ϱ� �������� y���� ��� ������.

	}
	else   //�����ϸ� �׸��� �нż�
	{
		//�׸���
		_bbShadow.rc = RectMakeCenter((_blueBaseball.rc.right + _blueBaseball.rc.left) / 2, _bbShadow.y, 215, 50);	//�����ϱ� ���� y���� ���
	}



}

void blueBaseball::render()
{

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _blueBaseball.rcAttackRange);	//���� ���� ��Ʈ
		Rectangle(getMemDC(), _blueBaseball.rc);				//���ʹ� ��Ʈ
		Rectangle(getMemDC(), _bbShadow.rc);					//�׸��� ��Ʈ

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
	
	//Rectangle(getMemDC(), _blueBaseball.rcStop);			//���� �浹 ��Ʈ

	_bbShadow.img->render(getMemDC(), _bbShadow.rc.left, _bbShadow.rc.top);
	_blueBaseball.img->frameRender(getMemDC(), _blueBaseball.x, _blueBaseball.y, _bbState->getCurrentFrameX(), _bbState->getCurrentFrameY());
	//_blueBaseball.img->frameRender(getMemDC(), _blueBaseball.rc.left, _blueBaseball.rc.top);


}

void blueBaseball::setImage()
{
	IMAGEMANAGER->addFrameImage("bBaseball_move", "image/3_Enemy/baseball/bBaseball_move.bmp", 2880, 600, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_idle", "image/3_Enemy/baseball/bBaseball_idle.bmp", 1080, 600, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_damaged", "image/3_Enemy/baseball/bBaseball_damaged.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_hang", "image/3_Enemy/baseball/bBaseball_hang.bmp", 360, 600, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_kick", "image/3_Enemy/baseball/bBaseball_kick.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_land", "image/3_Enemy/baseball/bBaseball_land.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_punch", "image/3_Enemy/baseball/bBaseball_punch.bmp", 720, 600, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_roll", "image/3_Enemy/baseball/bBaseball_roll.bmp", 4320, 600, 12, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_spin", "image/3_Enemy/baseball/bBaseball_spin.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("bBaseball_stop", "image/3_Enemy/baseball/bBaseball_stop.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("bBaseball_deathL", "image/3_Enemy/baseball/bBaseball_deathL.bmp", 360, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("bBaseball_deathR", "image/3_Enemy/baseball/bBaseball_deathR.bmp", 360, 300, true, RGB(255, 0, 255), false);

}

void blueBaseball::setShadow()
{
	IMAGEMANAGER->addImage("bBaseball_shadow", "image/3_Enemy/baseball/bBaseball_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_bbShadow.img = IMAGEMANAGER->findImage("bBaseball_shadow");
}
