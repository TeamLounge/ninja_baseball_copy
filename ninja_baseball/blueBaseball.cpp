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

HRESULT blueBaseball::init(POINT position)		//POINT : x, y를 같이 불러오는 것
{
	setImage();
	_blueBaseball.img = new image();

	setShadow();

	_bbState = new bbIdleState();
	_bbState->enter(this);

	_blueBaseball.x = position.x;
	_blueBaseball.y = position.y;		//포지션 입력값 받아올거고

	//이미지 좌표 셋
	_blueBaseball.img->setX(_blueBaseball.x);
	_blueBaseball.img->setY(_blueBaseball.y);	//이미지도 좌표에 맞게 뿌려줬고

	//등장 충돌 렉트
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



	//에너미
	_blueBaseball.rc = RectMakeCenter(_blueBaseball.x + 200, _blueBaseball.y + 200, 300, 230);

	if (!isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_bbShadow.rc = RectMakeCenter((_blueBaseball.rc.right + _blueBaseball.rc.left) / 2, _blueBaseball.rc.bottom, 215, 50);
		_bbShadow.y = _blueBaseball.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.

	}
	else   //점프하면 그림자 분신술
	{
		//그림자
		_bbShadow.rc = RectMakeCenter((_blueBaseball.rc.right + _blueBaseball.rc.left) / 2, _bbShadow.y, 215, 50);	//점프하기 전의 y값을 사용
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

		Rectangle(getMemDC(), _blueBaseball.rcAttackRange);	//공격 범위 렉트
		Rectangle(getMemDC(), _blueBaseball.rc);				//에너미 렉트
		Rectangle(getMemDC(), _bbShadow.rc);					//그림자 렉트

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
	
	//Rectangle(getMemDC(), _blueBaseball.rcStop);			//등장 충돌 렉트

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
