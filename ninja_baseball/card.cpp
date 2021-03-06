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

	_imageName = "card_dashAttack";

	_cardState = new cardIdleState();
	_cardState->enter(this);

	_card.x = position.x;
	_card.y = position.y;
	
	_card.img->setX(_card.x);
	_card.img->setY(_card.y);

	_currentFrameX = _currentFrameY = 0;

	setCard();
	setCardShadow();

	isattack = false;             //에너미가 공격했어??
	isdamage = false;				//에너미가 데미지 받았어??							
	iscatch = false;				//에저미가 잡혔어??

	RENDERMANAGER->addObj("card", _imageName.c_str(), "card_shadow", &_card.x, &_card.y,
		&_cardShadow.x, &_cardShadow.y, &_currentFrameX, &_currentFrameY);

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
	//_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2, _card.rc.bottom,
	//	_cardShadow.img->getWidth(), _cardShadow.img->getHeight());
	//_cardShadow.x = (_cardShadow.rc.left + _cardShadow.rc.right) / 2;
	//_cardShadow.y = (_cardShadow.rc.top + _cardShadow.rc.bottom) / 2;
	_assultedRect = RectMakeCenter((_card.rc.left + _card.rc.right) / 2,
		(_card.rc.top + _card.rc.bottom) / 2, 100, 70);

	if (!_isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2, _card.rc.bottom,
			_cardShadow.img->getWidth(), _cardShadow.img->getHeight());
		_jumpShadowY = (_cardShadow.rc.bottom + _cardShadow.rc.top) / 2;	//점프하기 전까지의 y값을 계속 저장중.

	}
	else   //점프하면
	{
		//그림자
		_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2, _jumpShadowY,
			_cardShadow.img->getWidth(), _cardShadow.img->getHeight());  //점프하기 전의 y값을 사용
	}

	if (!_isLeft)
	{
		_atkRc = RectMake(_card.x + 600, _card.y + 70, 200, 40);
	}

	if (_isLeft)
	{
		_atkRc = RectMake(_card.x - 400, _card.y + 70, 200, 40);
	}
	
	_cardShadow.x = (_cardShadow.rc.left + _cardShadow.rc.right) / 2;
	_cardShadow.y = (_cardShadow.rc.top + _cardShadow.rc.bottom) / 2;

	updateBullet();
}

void card::render()
{
	//_cardShadow.img->render(getMemDC(), _cardShadow.rc.left, _cardShadow.rc.top);
	//_card.img->frameRender(getMemDC(), _card.x, _card.y, _currentFrameX, _currentFrameY);
	renderBullet();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _card.rc);
		Rectangle(getMemDC(), _cardShadow.rc);
		Rectangle(getMemDC(), _assultedRect);
		Rectangle(getMemDC(), _atkRc);

		for (_viPunchBullet = _vPunchBullet.begin(); _viPunchBullet != _vPunchBullet.end(); ++_viPunchBullet)
		{
			Rectangle(getMemDC(), _viPunchBullet->rc);
		}
	}
}

void card::setImage()
{
	//////////////////////////////////////////////////////
	//            카드 스테이트 프레임
	/////////////////////////////////////////////////////
	IMAGEMANAGER->addFrameImage("card_attack", "image/3_Enemy/card/card_attack.bmp", 1350, 428, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_damaged", "image/3_Enemy/card/card_damaged.bmp", 1800, 428, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_dashAttack", "image/3_Enemy/card/card_dashAttack.bmp", 900, 428, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_death", "image/3_Enemy/card/card_death.bmp", 2250, 428, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_idle", "image/3_Enemy/card/card_idle.bmp", 900, 428, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_move", "image/3_Enemy/card/card_move.bmp", 1800, 428, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_stun", "image/3_Enemy/card/card_stun.bmp", 1350, 428, 3, 2, true, RGB(255, 0, 255), false);


	/////////////////////////////////////////////////////
	//             카드 쉐도우 프레임
	////////////////////////////////////////////////////

	IMAGEMANAGER->addImage("card_shadow", "image/3_Enemy/card/card_shadow.bmp", 133, 39, true, RGB(255, 0, 255), false);
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
	//총알 발사하게하는 불값
	_isFire = false;
	//총알 몇번쐈는지 확인용
	_bulletCount = 0;

	//각종 상태 불값
	_isCardSmallDamagedState =_isCardSmallDamaged = false;
	_isCardHeavyDamagedState =_isCardHeavyDamaged = false;
	_isCardDeathState =_isCardDeath = false;
	_deathCount = 0;

	_isGreenAttack1 = _isGreenAttack2 = _isGreenAttack3 = _isGreenDashAttack = _isGreenJumpAttack = false;

	_isGreenCatchBackAttack = _isGreenCatchFrontCombo = false;

	_isGreenCatch = _isGreenCatchAttack = _isGreenCatchAttackPre = false;

	_isDone = false;

	_isCardLandState = false;

	_isDeathState = false;

	_isRedAttack1 = _isRedAttack2 = _isRedAttack3 = false; //레드 기본어택
	_isRedDownAttack = _isRedDynamiteDance = _isRedCatchAttack = _isRedHomeRunAttack = false;
	_isRedJumpAttack = _isRedCatch = _isRedGrip = _isRedLegKickAttack = isRedSliding = false;
	_isRedDynamiteOn = _isRedCatchAttackPre = _isRedThrow = false;
}

void card::setCardShadow()
{
	_cardShadow.img = IMAGEMANAGER->findImage("card_shadow");
	_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2, _card.rc.bottom,
		_cardShadow.img->getWidth(), _cardShadow.img->getHeight());
	_cardShadow.x = (_cardShadow.rc.left + _cardShadow.rc.right) / 2;
	_cardShadow.y = (_cardShadow.rc.top + _cardShadow.rc.bottom) / 2;
	_cardShadow.img->setX(_cardShadow.x);
	_cardShadow.img->setY(_cardShadow.y);
}

void card::setBullet(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	_isFire = true;
}

void card::updateBullet()
{
	moveBullet();
}

void card::renderBullet()
{
	for (_viPunchBullet = _vPunchBullet.begin(); _viPunchBullet != _vPunchBullet.end(); ++_viPunchBullet)
	{
		if (_isLeft) _viPunchBullet->currentFrameY = 1;
		if (!_isLeft) _viPunchBullet->currentFrameY = 0;

		_viPunchBullet->img->frameRender(getMemDC(), _viPunchBullet->rc.left, _viPunchBullet->rc.top,
			0, _viPunchBullet->currentFrameY);
	}
}

void card::fireBullet(float x, float y, float angle)
{
	if (_bulletMax < _vPunchBullet.size() || _isFire) return;

	tagPunchBullet bullet;
	ZeroMemory(&bullet, sizeof(tagPunchBullet));
	bullet.img = new image;
	bullet.img->init("image/3_Enemy/card/card_punch.bmp", 0, 0, 195, 390, 1, 2,
		true, RGB(255, 0, 255), false);
	bullet.speed = 15.0f;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(),
		bullet.img->getFrameHeight());

	_vPunchBullet.push_back(bullet);

}

void card::moveBullet()
{
	for (_viPunchBullet = _vPunchBullet.begin(); _viPunchBullet != _vPunchBullet.end();)
	{
		_viPunchBullet->x += cosf(_viPunchBullet->angle) * _viPunchBullet->speed;
		_viPunchBullet->y += -sinf(_viPunchBullet->angle) * _viPunchBullet->speed;

		_viPunchBullet->rc = RectMakeCenter(_viPunchBullet->x, _viPunchBullet->y,
			_viPunchBullet->img->getFrameWidth(),
			_viPunchBullet->img->getFrameHeight());

		//사거리보다 더 멀리 나가면(?)
		if (_range < getDistance(_viPunchBullet->x, _viPunchBullet->y, _viPunchBullet->fireX, _viPunchBullet->fireY))
		{
			SAFE_RELEASE(_viPunchBullet->img);
			SAFE_DELETE(_viPunchBullet->img);
			_viPunchBullet = _vPunchBullet.erase(_viPunchBullet);
			_isFire = false;
		}
		else ++_viPunchBullet;
	}
}
