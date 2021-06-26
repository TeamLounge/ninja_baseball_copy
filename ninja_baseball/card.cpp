#include "stdafx.h"
#include "card.h"
#include "cardIdleState.h"

card::card()
{
}

card::~card()
{
}

void card::InputHandle()
{
	cardState* newState = _cardState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_cardState);
		_cardState = newState;
		_cardState->enter(this);
	}
}


HRESULT card::init()
{
	return S_OK;
}

HRESULT card::init(POINT position)
{
	setImage();
	_card.img = new image();

	_cardState = new cardIdleState();
	_cardState->enter(this);

	_card.x = position.x;
	_card.y = position.y;
	
	_card.img->setX(_card.x);
	_card.img->setY(_card.y);

	setCard();
	setCardShadow();
	return S_OK;
}

void card::release()
{
	_cardState->exit(this);	
}

void card::update()
{
	InputHandle();

	_cardState->update(this);
	
	_card.rc = RectMake(_card.x + 120, _card.y + 15, 200, 200);

	if (!_isLeft)
	{
		_atkRc = RectMake(_card.x + 600, _card.y + 70, 200, 40);
	}

	if (_isLeft)
	{
		_atkRc = RectMake(_card.x - 400, _card.y + 70, 200, 40);
	}
	

	getGravity();
}

void card::render()
{
	_cardShadow.img->render(getMemDC(), _cardShadow.rc.left, _cardShadow.rc.top);
	_card.img->frameRender(getMemDC(), _card.x, _card.y);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _card.rc);
		Rectangle(getMemDC(), _cardShadow.rc);
		Rectangle(getMemDC(), _atkRc);

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
}

void card::setImage()
{
	//////////////////////////////////////////////////////
	//            카드 스테이트 프레임
	/////////////////////////////////////////////////////
	IMAGEMANAGER->addFrameImage("card_attack", "image/card/card_attack.bmp", 1350, 428, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("card_damaged", "image/card/card_damaged.bmp", 1800, 428, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("card_dashAttack", "image/card/card_dashAttack.bmp", 900, 428, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("card_death", "image/card/card_death.bmp", 2250, 428, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("card_idle", "image/card/card_idle.bmp", 900, 428, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("card_move", "image/card/card_move.bmp", 1800, 428, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("card_stun", "image/card/card_stun.bmp", 1350, 428, 3, 2, true, RGB(255, 0, 255));


	/////////////////////////////////////////////////////
	//             카드 쉐도우 프레임
	////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("card_shadow", "image/card/card_shadow.bmp", 133, 39, true, RGB(255, 0, 255));
}

void card::setCard()
{
	_gravity = 0.4f;
	_jumpPower = 0;
	_speed = 5;
	_isJump = false;
	//false가 오른쪽 방향임.
	_isLeft = false;
	//데미지를 주었는지
	_isDamaged = false;
	//대시공격을 하고있는지
	_isDash = false;
	//주먹총알 공격을 하고 있는지
	_isPunchBullet = false;
	//펄스면 플레이어보다 앞에 있는것.
	_isUpper = false;
	//꼭지점에 도달했는지
	_isApex = false;
	//각 벽에 닿았는지 확인
	_isRightWall = _isLeftWall = _isTopWall = _isBottomWall = false;
}

void card::setCardShadow()
{
	_cardShadow.img = IMAGEMANAGER->findImage("card_shadow");
	_cardShadow.x = _card.x + 20;
	_cardShadow.y = _card.rc.bottom;
	_cardShadow.rc = RectMakeCenter(_cardShadow.x, _cardShadow.y, _cardShadow.img->getWidth(), _cardShadow.img->getHeight());
}

void card::getGravity()
{
	if (_isJump)
	{
		_card.y -= _jumpPower;
		_jumpPower -= _gravity;
		_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2 + 20, _cardShadow.y, _cardShadow.img->getWidth(), _cardShadow.img->getHeight());
	}

	if (!_isJump)
	{
		_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2 + 20, _card.rc.bottom, _cardShadow.img->getWidth(), _cardShadow.img->getHeight());
	}

	RECT temp;
	if (IntersectRect(&temp, &_card.rc, &_cardShadow.rc))
	{
		_isJump = false;
		_jumpPower = 0;
		//_card.y = _card.y - (temp.bottom - temp.top);
		_cardShadow.y = _card.rc.bottom;
	}

	if (!(IntersectRect(&temp, &_card.rc, &_cardShadow.rc)))
	{
		_isJump = true;
	}
	
}
