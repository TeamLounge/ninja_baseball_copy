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

HRESULT whiteBaseball::init(POINT position)		//POINT : x, y를 같이 불러오는 것
{
	setImage();
	_whiteBaseball.img = new image();

	setShadow();

	_wbState = new wbRollState();		//롤 모습으로 등장
	_wbState->enter(this);

	_whiteBaseball.x = position.x;
	_whiteBaseball.y = position.y;		//포지션 입력값 받아올거고

	//이미지 좌표 셋
	_whiteBaseball.img->setX(_whiteBaseball.x);
	_whiteBaseball.img->setY(_whiteBaseball.y);	//이미지도 좌표에 맞게 뿌려줬고

	//등장 충돌 렉트
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

	

	//에너미
	_whiteBaseball.rc = RectMakeCenter(_whiteBaseball.x + 200 , _whiteBaseball.y + 200, 300, 232);

	if (!isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_wbShadow.y = _whiteBaseball.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.
		_wbShadow.x = (_whiteBaseball.rc.right + _whiteBaseball.rc.left) / 2;
		_wbShadow.rc = RectMakeCenter(_wbShadow.x, _wbShadow.y, 215, 50);

	}
	else   //점프하면
	{
		//그림자
		_wbShadow.x = (_whiteBaseball.rc.right + _whiteBaseball.rc.left) / 2;
		_wbShadow.rc = RectMakeCenter(_wbShadow.x, _wbShadow.y, 215, 50);	//점프하기 전의 y값을 사용
		
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

		Rectangle(getMemDC(), _whiteBaseball.rcAttackRange);	//공격 범위 렉트
		Rectangle(getMemDC(), _whiteBaseball.rc);				//에너미 렉트
		Rectangle(getMemDC(), _wbShadow.rc);					//그림자 렉트

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
	//Rectangle(getMemDC(), _whiteBaseball.rcStop);			//등장 충돌 렉트

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
																																		//마지막 인자 : 알파렌더 유무

	IMAGEMANAGER->addImage("wBaseball_deathL", "image/3_Enemy/baseball/wBaseball_deathL.bmp", 360, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("wBaseball_deathR", "image/3_Enemy/baseball/wBaseball_deathR.bmp", 360, 300, true, RGB(255, 0, 255), false);

}

void whiteBaseball::setShadow()
{
	IMAGEMANAGER->addImage("wBaseball_shadow", "image/3_Enemy/baseball/wBaseball_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_wbShadow.img = IMAGEMANAGER->findImage("wBaseball_shadow");
}
