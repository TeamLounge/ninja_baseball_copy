#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybIdleState.h"

void yellowBaseball::InputHandle()
{
	ybState* newState = _ybState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_ybState);
		_ybState = newState;
		_ybState->enter(this);
	}
}

HRESULT yellowBaseball::init()
{
	
	return S_OK;
}

HRESULT yellowBaseball::init(POINT position)
{
	setImage();
	_yellowBaseball.img = new image();

	setShadow();

	_ybState = new ybIdleState();		//무브 모습으로 등장
	_ybState->enter(this);

	_yellowBaseball.x = position.x;
	_yellowBaseball.y = position.y;


	//이미지 좌표 뿌리기
	_yellowBaseball.img->setX(_yellowBaseball.x);
	_yellowBaseball.img->setY(_yellowBaseball.y);


	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isJump = false;
	isXOverlap == false;
	isYOverlap == false;

	return S_OK;
}

void yellowBaseball::release()
{
	_ybState->exit(this);
}

void yellowBaseball::update()
{
	InputHandle();
	_ybState->update(this);

	//에너미
	_yellowBaseball.rc = RectMakeCenter(_yellowBaseball.x + 200, _yellowBaseball.y + 200, 300, 230);

	if (!isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_ybShadow.rc = RectMakeCenter((_yellowBaseball.rc.right + _yellowBaseball.rc.left) / 2, _yellowBaseball.rc.bottom, 215, 50);
		_ybShadow.y = _yellowBaseball.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.

	}
	else   //점프하면 그림자 분신술
	{
		//그림자
		_ybShadow.rc = RectMakeCenter((_yellowBaseball.rc.right + _yellowBaseball.rc.left) / 2, _ybShadow.y, 215, 50);	//점프하기 전의 y값을 사용
	}
}

void yellowBaseball::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _yellowBaseball.rcAttackRange);	//공격 범위 렉트
		Rectangle(getMemDC(), _yellowBaseball.rc);				//에너미 렉트
		Rectangle(getMemDC(), _ybShadow.rc);					//그림자 렉트

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}

	_ybShadow.img->render(getMemDC(), _ybShadow.rc.left, _ybShadow.rc.top);
	_yellowBaseball.img->frameRender(getMemDC(), _yellowBaseball.x, _yellowBaseball.y, _ybState->getCurrentFrameX(), _ybState->getCurrentFrameY());
	//_yellowBaseball.img->frameRender(getMemDC(), _yellowBaseball.rc.left, _yellowBaseball.rc.top);
	//_yellowBaseball.img->frameRender(getMemDC(), _yellowBaseball.x, _yellowBaseball.y);
}

void yellowBaseball::setImage()
{
	IMAGEMANAGER->addFrameImage("yBaseball_move", "image/3_Enemy/baseball/yBaseball_move.bmp", 2880, 600, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_idle", "image/3_Enemy/baseball/yBaseball_idle.bmp", 1080, 600, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_damaged", "image/3_Enemy/baseball/yBaseball_damaged.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_hang", "image/3_Enemy/baseball/yBaseball_hang.bmp", 360, 600, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_kick", "image/3_Enemy/baseball/yBaseball_kick.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_land", "image/3_Enemy/baseball/yBaseball_land.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_punch", "image/3_Enemy/baseball/yBaseball_punch.bmp", 720, 600, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_roll", "image/3_Enemy/baseball/yBaseball_roll.bmp", 4320, 600, 12, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_spin", "image/3_Enemy/baseball/yBaseball_spin.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("yBaseball_stop", "image/3_Enemy/baseball/yBaseball_stop.bmp", 1440, 600, 4, 2, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("yBaseball_deathL", "image/3_Enemy/baseball/yBaseball_deathL.bmp", 360, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yBaseball_deathR", "image/3_Enemy/baseball/yBaseball_deathR.bmp", 360, 300, true, RGB(255, 0, 255), false);
}

void yellowBaseball::setShadow()
{
	IMAGEMANAGER->addImage("yBaseball_shadow", "image/3_Enemy/baseball/yBaseball_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_ybShadow.img = IMAGEMANAGER->findImage("yBaseball_shadow");
}
