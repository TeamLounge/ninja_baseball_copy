#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbRollState.h"

//#include "red.h"

void whiteBaseball::InputHandle()
{
	wbState* newState = _wbState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_wbState);
		_wbState = newState;
		_wbState->enter(this);
	}
}

HRESULT whiteBaseball::init()
{
	return S_OK;
}

HRESULT whiteBaseball::init(POINT position)		//POINT : x, y�� ���� �ҷ����� ��
{
	setImage();
	_whiteBaseball.img = new image();

	setShadow();

	_wbState = new wbRollState();		//�� ������� ����
	_wbState->enter(this);

	_whiteBaseball.x = position.x;
	_whiteBaseball.y = position.y;		//������ �Է°� �޾ƿðŰ�

	//�̹��� ��ǥ ��
	_whiteBaseball.img->setX(_whiteBaseball.x);
	_whiteBaseball.img->setY(_whiteBaseball.y);	//�̹����� ��ǥ�� �°� �ѷ����

	//���� �浹 ��Ʈ
	_whiteBaseball.rcStop = RectMakeCenter(_whiteBaseball.x - RND->getFromIntTo(800, 900), _whiteBaseball.y + 200, 50, 100);

	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isJump = false;
	isXOverlap = false;
	isYOverlap = false;

	
	RENDERMANAGER->addObj("whiteBaseball", _imgName.c_str(), "wBaseball_shadow", 
		&_whiteBaseball.x, &_whiteBaseball.y, &_wbShadow.x, &_wbShadow.y, 
		&_currentFrameX, &_currentFrameY);
	
	
	isattack = false;
	isdamage = false;
	iscatch = false;

	return S_OK;
}


void whiteBaseball::release()
{
	_wbState->exit(this);
}

void whiteBaseball::update()
{
	InputHandle();
	_wbState->update(this);

	

	//���ʹ�
	_whiteBaseball.rc = RectMakeCenter(_whiteBaseball.x + 200 , _whiteBaseball.y + 200, 300, 232);

	if (!isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_wbShadow.y = _whiteBaseball.rc.bottom;	//�����ϱ� �������� y���� ��� ������.
		_wbShadow.x = (_whiteBaseball.rc.right + _whiteBaseball.rc.left) / 2;
		_wbShadow.rc = RectMakeCenter(_wbShadow.x, _wbShadow.y, 215, 50);

	}
	else   //�����ϸ�
	{
		//�׸���
		_wbShadow.x = (_whiteBaseball.rc.right + _whiteBaseball.rc.left) / 2;
		_wbShadow.rc = RectMakeCenter(_wbShadow.x, _wbShadow.y, 215, 50);	//�����ϱ� ���� y���� ���
		
	}
}

void whiteBaseball::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _whiteBaseball.rcAttackRange);	//���� ���� ��Ʈ
		Rectangle(getMemDC(), _whiteBaseball.rc);				//���ʹ� ��Ʈ
		Rectangle(getMemDC(), _wbShadow.rc);					//�׸��� ��Ʈ

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
	//Rectangle(getMemDC(), _whiteBaseball.rcStop);			//���� �浹 ��Ʈ

	//_wbShadow.img->render(getMemDC(), _wbShadow.rc.left, _wbShadow.rc.top);	
	//_whiteBaseball.img->frameRender(getMemDC(), _whiteBaseball.x, _whiteBaseball.y, _wbState->getCurrentFrameX(), _wbState->getCurrentFrameY());
	//_whiteBaseball.img->frameRender(getMemDC(), _whiteBaseball.rc.left, _whiteBaseball.rc.top);
	
}

void whiteBaseball::setImage()
{
	IMAGEMANAGER->addFrameImage("wBaseball_move", "image/3_Enemy/baseball/wBaseball_move.bmp", 2880, 600, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_idle", "image/3_Enemy/baseball/wBaseball_idle.bmp", 1080, 600, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_damaged", "image/3_Enemy/baseball/wBaseball_damaged.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_hang", "image/3_Enemy/baseball/wBaseball_hang.bmp", 360, 600, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_kick", "image/3_Enemy/baseball/wBaseball_kick.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_land", "image/3_Enemy/baseball/wBaseball_land.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_punch", "image/3_Enemy/baseball/wBaseball_punch.bmp", 720, 600, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_roll", "image/3_Enemy/baseball/wBaseball_roll.bmp", 4320, 600, 12, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("wBaseball_spin", "image/3_Enemy/baseball/wBaseball_spin.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addFrameImage("wBaseball_stop", "image/3_Enemy/baseball/wBaseball_stop.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);	
																																		//������ ���� : ���ķ��� ����

	IMAGEMANAGER->addImage("wBaseball_deathL", "image/3_Enemy/baseball/wBaseball_deathL.bmp", 360, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("wBaseball_deathR", "image/3_Enemy/baseball/wBaseball_deathR.bmp", 360, 300, true, RGB(255, 0, 255), false);

}

void whiteBaseball::setShadow()
{
	IMAGEMANAGER->addImage("wBaseball_shadow", "image/3_Enemy/baseball/wBaseball_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_wbShadow.img = IMAGEMANAGER->findImage("wBaseball_shadow");
}
