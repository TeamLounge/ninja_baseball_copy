#include "stdafx.h"
#include "greenBaseball.h"
#include "gbHangState.h"


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

HRESULT greenBaseball::init(POINT position)		//POINT : x, y를 같이 불러오는 것
{
	setImage();
	_greenBaseball.img = new image();

	_imgName = "gBaseball_damaged";

	setShadow();

	_gbState = new gbHangState();		
	_gbState->enter(this);

	_greenBaseball.x = position.x;
	_greenBaseball.y = position.y;		//포지션 입력값 받아올거고

	//이미지 좌표 셋
	_greenBaseball.img->setX(_greenBaseball.x);
	_greenBaseball.img->setY(_greenBaseball.y);	//이미지도 좌표에 맞게 뿌려줬고

	//등장 충돌 렉트
	_greenBaseball.rcStop = RectMakeCenter(_greenBaseball.x + 200, _greenBaseball.y + 750, 100, 50);

	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isJump = false;
	isXOverlap = false;
	isYOverlap = false;

	isLand = false;

	isattack = false;				//에너미가 공격했어??
	isdamage = false;				//에너미가 데미지 받았어??							
	iscatch = false;				//에저미가 잡혔어??
	isDeath = false;

	timeCount = 0;
	damagedCount = 0;

	RENDERMANAGER->addObj("greenBaseball", _imgName.c_str(), "gBaseball_shadow",
		&_greenBaseball.x, &_greenBaseball.y, &_gbShadow.x, &_gbShadow.y,
		&_currentFrameX, &_currentFrameY);

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



	//에너미
	_greenBaseball.rc = RectMakeCenter(_greenBaseball.x + 200, _greenBaseball.y + 200, 230, 190);

	if (!isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_gbShadow.rc = RectMakeCenter((_greenBaseball.rc.right + _greenBaseball.rc.left) / 2, _greenBaseball.rc.bottom, 215, 50);
		_gbShadow.x = (_greenBaseball.rc.right + _greenBaseball.rc.left) / 2;	//점프하기 전까지의 y값을 계속 저장중.
		_gbShadow.y = _greenBaseball.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.

	}
	else   //점프하면 그림자 분신술
	{
		//그림자
		_gbShadow.rc = RectMakeCenter((_greenBaseball.rc.right + _greenBaseball.rc.left) / 2, _gbShadow.y, 215, 50);	//점프하기 전의 y값을 사용
	}

	//if (KEYMANAGER->isOnceKeyDown('M') && !isCollisionDamaged)
	//{
	//	damagedCount++;
	//	if (damagedCount == 5)
	//	{
	//		isDeath = true;
	//	}

	//	isCollisionDamaged = true;
	//}
	//else
	//{
	//	isDeath = false;
	//	isCollisionDamaged = false;
	//}

	////충돌 여부에 따른 죽음 판정
	//if (KEYMANAGER->isOnceKeyDown('M') && !isCollisionDamaged)
	//{
	//	damageCount++;
	//	if (damageCount == 5)
	//	{
	//		isDeath = true;
	//	}

	//	isCollisionDamaged = true;
	//}
	//else
	//{
	//	isDeath = false;
	//	isCollisionDamaged = false;
	//}


}

void greenBaseball::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _greenBaseball.rcAttackRange);	//공격 범위 렉트
		Rectangle(getMemDC(), _greenBaseball.rc);				//에너미 렉트
		Rectangle(getMemDC(), _gbShadow.rc);					//그림자 렉트
	}

	//Rectangle(getMemDC(), _greenBaseball.rcStop);			//등장 충돌 렉트

	//_gbShadow.img->render(getMemDC(), _gbShadow.rc.left, _gbShadow.rc.top);
	//_greenBaseball.img->frameRender(getMemDC(), _greenBaseball.x, _greenBaseball.y, _currentFrameX, _currentFrameY);
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
