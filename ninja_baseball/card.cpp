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

	isattack = false;             //���ʹ̰� �����߾�??
	isdamage = false;				//���ʹ̰� ������ �޾Ҿ�??							
	iscatch = false;				//�����̰� ������??

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

	if (!_isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2, _card.rc.bottom,
			_cardShadow.img->getWidth(), _cardShadow.img->getHeight());
		_jumpShadowY = (_cardShadow.rc.bottom + _cardShadow.rc.top) / 2;	//�����ϱ� �������� y���� ��� ������.

	}
	else   //�����ϸ�
	{
		//�׸���
		_cardShadow.rc = RectMakeCenter((_card.rc.left + _card.rc.right) / 2, _jumpShadowY,
			_cardShadow.img->getWidth(), _cardShadow.img->getHeight());  //�����ϱ� ���� y���� ���
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
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _card.rc);
		Rectangle(getMemDC(), _cardShadow.rc);
		Rectangle(getMemDC(), _assultedRect);
		Rectangle(getMemDC(), _atkRc);

		for (_viPunchBullet = _vPunchBullet.begin(); _viPunchBullet != _vPunchBullet.end(); ++_viPunchBullet)
		{
			Rectangle(getMemDC(), _viPunchBullet->rc);
		}

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
}

void card::setImage()
{
	//////////////////////////////////////////////////////
	//            ī�� ������Ʈ ������
	/////////////////////////////////////////////////////
	IMAGEMANAGER->addFrameImage("card_attack", "image/3_Enemy/card/card_attack.bmp", 1350, 428, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_damaged", "image/3_Enemy/card/card_damaged.bmp", 1800, 428, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_dashAttack", "image/3_Enemy/card/card_dashAttack.bmp", 900, 428, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_death", "image/3_Enemy/card/card_death.bmp", 2250, 428, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_idle", "image/3_Enemy/card/card_idle.bmp", 900, 428, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_move", "image/3_Enemy/card/card_move.bmp", 1800, 428, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("card_stun", "image/3_Enemy/card/card_stun.bmp", 1350, 428, 3, 2, true, RGB(255, 0, 255), false);


	/////////////////////////////////////////////////////
	//             ī�� ������ ������
	////////////////////////////////////////////////////

	IMAGEMANAGER->addImage("card_shadow", "image/3_Enemy/card/card_shadow.bmp", 133, 39, true, RGB(255, 0, 255), false);
}

void card::setCard()
{
	_gravity = 0.4f;
	_jumpPower = 0;
	_speed = 5;
	_isJump = false;
	//false�� ������ ������.
	_isLeft = false;
	//�������� �־�����
	_isDamaged = false;
	//��ð����� �ϰ��ִ���
	_isDash = false;
	//�ָ��Ѿ� ������ �ϰ� �ִ���
	_isPunchBullet = false;
	//�޽��� �÷��̾�� �տ� �ִ°�.
	_isUpper = false;
	//�������� �����ߴ���
	_isApex = false;
	//�� ���� ��Ҵ��� Ȯ��
	_isRightWall = _isLeftWall = _isTopWall = _isBottomWall = false;
	//�Ѿ� �߻��ϰ��ϴ� �Ұ�
	_isFire = false;
	//�Ѿ� ��������� Ȯ�ο�
	_bulletCount = 0;

	//���� ���� �Ұ�
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

	_isRedAttack1 = _isRedAttack2 = _isRedAttack3 = false; //���� �⺻����
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

		//��Ÿ����� �� �ָ� ������(?)
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
