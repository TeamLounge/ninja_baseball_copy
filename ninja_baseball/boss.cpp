#include "stdafx.h"
#include "boss.h"
#include "bossEntryState.h"
#include "bossIdleState.h"

HRESULT boss::init()
{
	return S_OK;
}

void boss::InputHandle()
{
	bossState* newState = _bossState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_bossState);
		_bossState = newState;
		_bossState->enter(this);
	}
}

HRESULT boss::init(POINT position)
{
	setImage();
	_boss.img = new image();

	_bossPinLight.img = IMAGEMANAGER->findImage("boss_pinLight");

	setBoss();

	_imageName = "noWingProp_oneTwoPunch";
	_shadowName = "boss_shadow";
	RENDERMANAGER->addObj("boss", _imageName.c_str(), _shadowName.c_str(), &_imageX, &_imageY,
		&_bossShadow.x, &_bossShadow.y, &_currentFrameX, &_currentFrameY);

	_bossState = new bossEntryState(); //new bossEntryState();
	//_isPreWind = true; // �ӽù�����
	_bossState->enter(this);

	_bossPinLight.img = new image;

	_boss.x = position.x;
	_boss.y = position.y;

	_imageX = _boss.x;
	_imageY = _boss.y;

	_boss.img->setX(_boss.x);
	_boss.img->setY(_boss.y);

	setBossShadow();

	return S_OK;
}



void boss::release()
{
	_bossState->exit(this);
}

void boss::update()
{
	InputHandle();
	_bossState->update(this);
	smokeEffect();
	renderAdjust();
	imgLocation();

	if (_count == 0) _bossForm = DEFAULT;
	if (_count == 3) _bossForm = NO_WING;
	if (_count == 6) _bossForm = NO_WING_PROP;
	if (_count == 9) _bossForm = NO_ONE_ARM;
	if (_count == 12) _bossForm = NO_ARM;

	_boss.rc = RectMake(_boss.x, _boss.y, 579, 429);
	_assultedRect = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2,
		(_boss.rc.top + _boss.rc.bottom) / 2 + 70, 150, 100);


	if (!_isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_bossShadow.rc = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2, _boss.rc.bottom,
			_bossShadow.img->getWidth(), _bossShadow.img->getHeight());
		_jumpShadowY = (_bossShadow.rc.bottom + _bossShadow.rc.top) / 2;	//�����ϱ� �������� y���� ��� ������.

	}
	else   //�����ϸ�
	{
		//�׸���
		_bossShadow.rc = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2, _jumpShadowY,
			_bossShadow.img->getWidth(), _bossShadow.img->getHeight());	//�����ϱ� ���� y���� ���
	}

	if (!_isLeft)
	{
		if (_isTrigger)
		{
			_longRangeAtkRc = RectMake(_boss.rc.right + 100, _bossShadow.rc.top, 400, 50);
		}

		else _longRangeAtkRc = RectMake(_boss.rc.right + 300, _bossShadow.rc.top, 200, 50);
	}

	if (_isLeft)
	{
		if (_isTrigger)
		{
			_longRangeAtkRc = RectMake(_boss.rc.left - 500, _bossShadow.rc.top, 400, 50);
		}

		else _longRangeAtkRc = RectMake(_boss.rc.left - 500, _bossShadow.rc.top, 200, 50);
	}

	_bossShadow.x = (_bossShadow.rc.left + _bossShadow.rc.right) / 2;
	_bossShadow.y = (_bossShadow.rc.top + _bossShadow.rc.bottom) / 2;

	if (_isPinLight)
	{
		_alphaCnt++;
		if (_alphaCnt >= 40)
		{
			_isAlpha = true;
			_alphaCnt = 0;
		}

		if (_isAlpha && _alphaCnt % 8 == 0)
		{
			_alphaIdx = 0;
		}
		if (_isAlpha && _alphaCnt % 8 != 0)
		{
			_alphaIdx = 255;
		}

		if (_alphaIdx == 255)
		{
			_shadowName = "";
		}
		else
		{
			_shadowName = "boss_shadow";
		}
	}
	else
	{
		_shadowName = "boss_shadow";
	}
}

void boss::render()
{
	//���� ���¸��� �̹���ũ�Ⱑ �޶� ��ġ�� �����ϱ� ���� �������
	//_bossShadow.img->render(getMemDC(), _bossShadow.rc.left, _bossShadow.rc.top);
	if (_isPinLight) _bossPinLight.img->alphaRender(getMemDC(), _boss.x + 100, _boss.y - 150, _alphaIdx);
	
	if (_isLeft)
	{
		if (_isNoWing)
		{
			_isLeft_LeftNoWing->frameRender(getMemDC(), _isLeft_LeftNoWing->getX(), _isLeft_LeftNoWing->getY());
			_isLeft_RightNoWing->frameRender(getMemDC(), _isLeft_RightNoWing->getX(), _isLeft_RightNoWing->getY());
		}

		if (_isNoWingProp)
		{
			_isLeft_NoWingProp->frameRender(getMemDC(), _isLeft_NoWingProp->getX(), _isLeft_NoWingProp->getY());
		}

		if (_isNoOneArm)
		{
			_isLeft_RightArm->frameRender(getMemDC(), _isLeft_RightArm->getX(), _isLeft_RightArm->getY());
		}

		if (_isNoArm)
		{
			_isLeft_LeftArm->frameRender(getMemDC(), _isLeft_LeftArm->getX(), _isLeft_LeftArm->getY());
		}
	}

	else if (!_isLeft)
	{
		if (_isNoWing)
		{
			_isRight_LeftNoWing->frameRender(getMemDC(), _isRight_LeftNoWing->getX(), _isRight_LeftNoWing->getY());
			_isRight_RightNoWing->frameRender(getMemDC(), _isRight_RightNoWing->getX(), _isRight_RightNoWing->getY());
		}

		if (_isNoWingProp)
		{
			_isRight_NoWingProp->frameRender(getMemDC(), _isRight_NoWingProp->getX(), _isRight_NoWingProp->getY());
		}

		if (_isNoOneArm)
		{
			_isRight_LeftArm->frameRender(getMemDC(), _isRight_LeftArm->getX(), _isRight_LeftArm->getY());
		}

		if (_isNoArm)
		{
			_isRight_RightArm->frameRender(getMemDC(), _isRight_RightArm->getX(), _isRight_RightArm->getY());
		}
	}

	EFFECTMANAGER->render();

	///////////////////////////////////
	//     ## ����׿� ��Ʈ ##        //
	///////////////////////////////////
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _boss.rc);
		Rectangle(getMemDC(), _bossShadow.rc);
		Rectangle(getMemDC(), _longRangeAtkRc);
		Rectangle(getMemDC(), _assultedRect);

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}

}

/////////////////////////////////////////
// ########## ���� �̹��� ��� ###########
/////////////////////////////////////////
void boss::setImage()
{
	////////////////////////////////////////////
	//  ###### ���� ������ �̹��� ##########   //
	///////////////////////////////////////////
	IMAGEMANAGER->addFrameImage("boss_entry", "image/4_Boss/boss_idle(entry).bmp", 2316, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_attacked", "image/4_Boss/boss_attacked.bmp", 2416, 1182, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_shooting", "image/4_Boss/boss_gun.bmp", 2376, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_shootingP", "image/4_Boss/boss_gun_prop.bmp", 1188, 858, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_shootingR", "image/4_Boss/boss_gun_ready.bmp", 7722, 858, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_idle", "image/4_Boss/boss_idle(basic).bmp", 2316, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_oneTwoPunch", "image/4_Boss/boss_onetwo.bmp", 11840, 1182, 16, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_straight", "image/4_Boss/boss_straight.bmp", 27900, 1240, 31, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_upperCut", "image/4_Boss/boss_upper_cut.bmp", 6600, 1302, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_wind", "image/4_Boss/boss_wind.bmp", 3462, 860, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_attacked", "image/4_Boss/boss_attacked(no_wing).bmp", 2500, 1176, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_straight", "image/4_Boss/boss_straight(no_wing).bmp", 11700, 1240, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_shooting", "image/4_Boss/boss_gun(no_wing).bmp", 2016, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_shootingProp", "image/4_Boss/boss_gun_prop(no_wing).bmp", 1002, 858, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_shootingReady", "image/4_Boss/boss_gun_ready(no_wing).bmp", 6513, 858, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_idle", "image/4_Boss/boss_idle(no_wing).bmp", 1956, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_upperCut", "image/4_Boss/boss_upper_cut(no_wing).bmp", 6380, 1302, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_oneTwoPunch", "image/4_Boss/sboss_onetwo.bmp", 11100, 1182, 15, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_attacked", "image/4_Boss/boss_attacked(no_wing_prop).bmp", 2500, 1176, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_straight", "image/4_Boss/boss_straight(no_wing_prop).bmp", 11700, 1240, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_idle", "image/4_Boss/boss_idle(no_wing_Prop).bmp", 1956, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_upperCut", "image/4_Boss/boss_upper_cut(no_wing_prop).bmp", 5270, 1302, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_oneTwoPunch", "image/4_Boss/tboss_onetwo.bmp", 11840, 1182, 16, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noOneArm_idle", "image/4_Boss/boss_idle(no_one_arm).bmp", 1956, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noOneArm_attacked", "image/4_Boss/boss_attacked(no_one_arm).bmp", 2225, 1092, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noOneArm_straight", "image/4_Boss/boss_straight(no_one_arm).bmp", 11700, 1240, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noArm_attacked", "image/4_Boss/boss_attacked(no_arm).bmp", 2225, 1092, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noArm_idle", "image/4_Boss/boss_final.bmp", 742, 1068, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noArm_death", "image/4_Boss/boss_death.bmp", 2681, 1168, 7, 2, true, RGB(255, 0, 255), false);

	///////////////////////////////////////////////////////////////////
	//  ###### ���� ��Ÿ �̹���(ü�¹�, ����, ������ ��) ##########     //
	///////////////////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("boss_greenBar", "image/4_Boss/boss_greenBar.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_redBar", "image/4_Boss/boss_redBar.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_yellowBar", "image/4_Boss/boss_yellowBar.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_yellowBarAttack", "image/4_Boss/boss_yellowBarAttack.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_shadow", "image/4_Boss/boss_shadow.bmp", 300, 85, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_pinLight", "image/4_Boss/boss_pin_light.bmp", 384, 624, true, RGB(255, 0, 255), true);
	_isLeft_LeftNoWing = IMAGEMANAGER->addFrameImage("boss_left_leftWing", "image/4_Boss/isLeft_leftWing.bmp", 462, 216, 2, 1, true, RGB(255, 0, 255), false);
	_isLeft_RightNoWing = IMAGEMANAGER->addFrameImage("boss_left_rightWing", "image/4_Boss/isLeft_rightWing.bmp", 270, 150, 2, 1, true, RGB(255, 0, 255), false);
	_isRight_LeftNoWing = IMAGEMANAGER->addFrameImage("boss_right_leftWing", "image/4_Boss/isRight_leftWing.bmp", 270, 150, 2, 1, true, RGB(255, 0, 255), false);
	_isRight_RightNoWing = IMAGEMANAGER->addFrameImage("boss_right_rightWing", "image/4_Boss/isRight_rightWing.bmp", 462, 216, 2, 1, true, RGB(255, 0, 255), false);
	_isLeft_LeftArm = IMAGEMANAGER->addFrameImage("boss_left_leftArm", "image/4_Boss/isLeft_arm.bmp", 504, 258, 2, 1, true, RGB(255, 0, 255), false);
	_isLeft_RightArm = IMAGEMANAGER->addFrameImage("boss_left_rightArm", "image/4_Boss/isLeft_arm.bmp", 504, 258, 2, 1, true, RGB(255, 0, 255), false);
	_isRight_LeftArm = IMAGEMANAGER->addFrameImage("boss_right_leftArm", "image/4_Boss/isRight_arm.bmp", 504, 258, 2, 1, true, RGB(255, 0, 255), false);
	_isRight_RightArm = IMAGEMANAGER->addFrameImage("boss_right_rightArm", "image/4_Boss/isRight_arm.bmp", 504, 258, 2, 1, true, RGB(255, 0, 255), false);
	_isRight_NoWingProp = IMAGEMANAGER->addFrameImage("boss_left_prop", "image/4_Boss/isRight_prop.bmp", 144, 201, 2, 1, true, RGB(255, 0, 255), false);
	_isLeft_NoWingProp = IMAGEMANAGER->addFrameImage("boss_right_prop", "image/4_Boss/isLeft_prop.bmp", 144, 201, 2, 1, true, RGB(255, 0, 255), false);

	//////////////////////////////////////////
	//  ###### ���� ����Ʈ #########
	/////////////////////////////////////////
	EFFECTMANAGER->addEffect("boss_windEffect", "image/4_Boss/boss_windEffect.bmp", 1070, 101, 107, 101, 1.1f, 0.35f, 6);
	EFFECTMANAGER->addEffect("boss_windEffect2", "image/4_Boss/boss_windEffect.bmp", 1070, 101, 107, 101, 1.1f, 0.35f, 6);
	EFFECTMANAGER->addEffect("boss_bullet", "image/4_Boss/boss_bullet_effect.bmp", 384, 192, 48, 192, 1.35f, 0.15f, 20);
	EFFECTMANAGER->addEffect("boss_smoke_noWing", "image/4_Boss/boss_smoke_effect.bmp", 399, 64, 57, 64, 1.13f, 0.15f, 50);
	EFFECTMANAGER->addEffect("boss_smoke_noWing2", "image/4_Boss/boss_smoke_effect.bmp", 399, 64, 57, 64, 1.13f, 0.15f, 50);
	EFFECTMANAGER->addEffect("boss_smoke_noWingProp", "image/4_Boss/boss_smoke_effect.bmp", 399, 64, 57, 64, 1.13f, 0.15f, 50);
	EFFECTMANAGER->addEffect("boss_smoke_noOneArm", "image/4_Boss/boss_smoke_effect.bmp", 399, 64, 57, 64, 1.13f, 0.15f, 50);
	EFFECTMANAGER->addEffect("boss_smoke_noArm", "image/4_Boss/boss_smoke_effect.bmp", 399, 64, 57, 64, 1.13f, 0.15f, 50);
}


/////////////////////////////////////////
// ########## ���� �ʱ⼳���� ###########
/////////////////////////////////////////
void boss::setBoss()
{
	//���� �ʱ�ȭ
	_bossForm = DEFAULT;
	//���� ������ Ȯ�ο� �ʱ�ȭ
	_currentFrameX = _currentFrameY = 0;
	//���� ��ġȮ�ο�
	_isLeft = _isUpper = false;
	//���� ���ǵ�
	_speed = 0;
	//���� ���� ��ȯ��
	_count = _stateCount = 0;
	//���� ������ ����ġ
	_isPinLight = false;
	//���� �ε���
	_alphaIdx = 255;
	_alphaCnt = 0;
	_isAlpha = false;
	//���� �ѹ���
	_numAtkPattern = 0;
	//�ќi���� ���ο� �����θ������ ����
	_isTrigger = false;
	_isSucceedShootingAttack = false;
	//�� ���ο� �� ��������
	_isJabAttack = false;
	_isSucceedJabAttack = false;
	_isJabState = false;
	//�� ���ݿ�ǿ� �����Ǿ����� Ȯ��
	_isCrash = false;
	_missCount = 0;
	//��Ʈ����Ʈ ���� ���ο� ��������
	_isStraightAttack = false;
	_isSucceedStraightAttack = false;
	_isStraightState = false;
	//������ ���� ���ο� ��������
	_isUpperCut = false;
	_isSucceedUpperCut = false;
	_isUpperCutState = false;
	//�������� ���Դ��� ����
	_isDamaged = false;
	_isDamagedState = false;
	//������Ұ�
	_isAttacked = false;
	//�������
	_isMoveState = false;
	//���̵����
	_isIdleState = false;
	//���û���
	_isShootingState = false;
	//������ ����
	_isDeathState = false;
	_isNoWing = _isNoWingProp = _isNoOneArm = _isNoArm = false;
	_divideX = _divideY = _divideGravity = 0;
	//���� ���� ��������
	_isSmallDamagedState = false;
	_isSmallDamaged = false;
	_isGreenAttack12 = false;
	_isGreenAttack3 = false;
	_isGreenCatch = false;
	_isGreenCatchAttack = false;
	_isGreenCatchBackAttack = false;
	_isGreenCatchFrontCombo = false;
}


/////////////////////////////////////////
// ########## ���� �׸��� ###########
/////////////////////////////////////////
void boss::setBossShadow()
{
	_bossShadow.img = IMAGEMANAGER->findImage("boss_shadow");
	_bossShadow.rc = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2, _boss.rc.bottom,
		_bossShadow.img->getWidth(), _bossShadow.img->getHeight());
	_bossShadow.x = (_bossShadow.rc.left + _bossShadow.rc.right) / 2;
	_bossShadow.y = (_bossShadow.rc.top + _bossShadow.rc.bottom) / 2;
	_bossShadow.img->setX(_bossShadow.x);
	_bossShadow.img->setY(_bossShadow.y);
}


///////////////////////////////////////////
// ########## ���� ��ġ�ǽð����� ###########
///////////////////////////////////////////
void boss::renderAdjust()
{
	//������ Ư�������϶��� �̰Ŵ�~

	if (_isLeft)
	{
		switch (_bossForm)
		{
		case DEFAULT:
			if (_isJabState)
			{
				_imageX = _boss.x - 65;
				_imageY = _boss.y - 162;
			}
			else if (_isStraightState)
			{
				_imageX = _boss.x - 160;
				_imageY = _boss.y - 192;
			}
			else if (_isDamagedState)
			{
				_imageX = _boss.x + 51;
				_imageY = _boss.y - 150;
			}
			else if (_isUpperCutState)
			{
				_imageX = _boss.x;
				_imageY = _boss.y - 222;
			}

			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 51;
				_imageY = _boss.y - 150;
			}

			else
			{
				_imageX = _boss.x;
				_imageY = _boss.y;
			}

			break;

		case NO_WING:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 55;
				_imageY = _boss.y - 150;
			}

			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 55;
				_imageY = _boss.y - 150;
			}
			else if (_isJabState)
			{
				_imageX = _boss.x - 80;
				_imageY = _boss.y - 164;
			}
			else if (_isStraightState)
			{
				_imageX = _boss.x - 165;
				_imageY = _boss.y - 190;
			}
			else if (_isUpperCutState)
			{
				_imageX = _boss.x;
				_imageY = _boss.y - 222;
			}

			else
			{
				_imageX = _boss.x;
				_imageY = _boss.y;
			}
			break;

		case NO_WING_PROP:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 20;
				_imageY = _boss.y - 152;
			}

			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 20;
				_imageY = _boss.y - 152;
			}

			else if (_isJabState)
			{
				_imageX = _boss.x - 80;
				_imageY = _boss.y - 164;
			}
			else if (_isStraightState)
			{
				_imageX = _boss.x - 165;
				_imageY = _boss.y - 190;
			}
			else if (_isUpperCutState)
			{
				_imageX = _boss.x;
				_imageY = _boss.y - 222;
			}

			else
			{
				_imageX = _boss.x;
				_imageY = _boss.y;
			}
			break;

		case NO_ONE_ARM:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 103;
				_imageY = _boss.y - 104;
			}

			if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 103;
				_imageY = _boss.y - 104;
			}

			else if (_isStraightState)
			{
				_imageX = _boss.x - 165;
				_imageY = _boss.y - 190;
			}

			else
			{
				_imageX = _boss.x;
				_imageY = _boss.y;
			}
			break;

		case NO_ARM:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 103;
				_imageY = _boss.y - 104;
			}

			if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 103;
				_imageY = _boss.y - 104;
			}

			else
			{
				_imageX = _boss.x + 105;
				_imageY = _boss.y - 105;
			}
			break;
		}
	}

	else
	{
		switch (_bossForm)
		{
		case DEFAULT:
			if (_isJabState)
			{
				_imageX = _boss.x - 100;
				_imageY = _boss.y - 162;
			}
			else if (_isStraightState)
			{
				_imageX = _boss.x - 167;
				_imageY = _boss.y - 191;
			}
			else if (_isDamagedState)
			{
				_imageX = _boss.x - 72;
				_imageY = _boss.y - 149;
			}
			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x - 72;
				_imageY = _boss.y - 149;
			}
			else if (_isUpperCutState)
			{
				_imageX = _boss.x - 70;
				_imageY = _boss.y - 222;
			}

			else
			{
				_imageX = _boss.x;
				_imageY = _boss.y;
			}
			break;

		case NO_WING:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 30;
				_imageY = _boss.y - 150;
			}

			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 30;
				_imageY = _boss.y - 150;
			}

			else if (_isJabState)
			{
				_imageX = _boss.x - 90;
				_imageY = _boss.y - 163;
			}
			else if (_isStraightState)
			{
				_imageX = _boss.x - 165;
				_imageY = _boss.y - 190;
			}
			else if (_isUpperCutState)
			{
				_imageX = _boss.x - 30;
				_imageY = _boss.y - 222;
			}

			else
			{
				_imageX = _boss.x + 85;
				_imageY = _boss.y;
			}
			break;

		case NO_WING_PROP:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 18;
				_imageY = _boss.y - 152;
			}
			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 18;
				_imageY = _boss.y - 152;
			}
			else if (_isJabState)
			{
				_imageX = _boss.x - 90;
				_imageY = _boss.y - 163;
			}
			else if (_isStraightState)
			{
				_imageX = _boss.x - 165;
				_imageY = _boss.y - 190;
			}
			else if (_isUpperCutState)
			{
				_imageX = _boss.x;
				_imageY = _boss.y - 222;
			}

			else
			{
				_imageX = _boss.x + 85;
				_imageY = _boss.y;
			}
			break;

		case NO_ONE_ARM:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 20;
				_imageY = _boss.y - 104;
			}

			if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 20;
				_imageY = _boss.y - 104;
			}

			else if (_isStraightState)
			{
				_imageX = _boss.x - 165;
				_imageY = _boss.y - 190;
			}

			else
			{
				_imageX = _boss.x + 85;
				_imageY = _boss.y;
			}
			break;

		case NO_ARM:
			if (_isDamagedState)
			{
				_imageX = _boss.x + 20;
				_imageY = _boss.y - 104;
			}

			else if (_isSmallDamagedState)
			{
				_imageX = _boss.x + 20;
				_imageY = _boss.y - 104;
			}

			else
			{
				_imageX = _boss.x + 85;
				_imageY = _boss.y - 105;
			}
			break;
		}
	}
}


////////////////////////////////////////////
// ######## ���¿� ���� ����ũȿ�� ########## ��� ���ϰ� ó�����ؾߵ�;;;;�����پ�
///////////////////////////////////////////
void boss::smokeEffect()
{
	//������ �ٶ󺼶�
	if (_isLeft)
	{
		//����Ʈ�� �ƴϸ�, �� ������ ���󰡸�
		if (_bossForm != DEFAULT)
		{
			EFFECTMANAGER->play("boss_smoke_noWing", _boss.rc.right - 200, _boss.rc.top + 110, 45);
			EFFECTMANAGER->play("boss_smoke_noWing2", _boss.rc.right - 180, _boss.rc.top + 210, 45);

			EFFECTMANAGER->update("boss_smoke_noWing", 0, -4.8f);
			EFFECTMANAGER->update("boss_smoke_noWing2", 0, -4.8f);
		}

		//�����緯�� ���ų�, �������� ���ų�, ���ȴ� �������
		if (_bossForm == NO_WING_PROP || _bossForm == NO_ONE_ARM || _bossForm == NO_ARM)
		{
			if (_bossForm == NO_ARM)
			{
				EFFECTMANAGER->play("boss_smoke_noWingProp", _boss.rc.left + 150, _boss.rc.top - 35, 45);
				EFFECTMANAGER->update("boss_smoke_noWingProp", 0, -4.8f);
			}

			else
			{
				if (_isJabState || _isDamagedState)
				{
					EFFECTMANAGER->play("boss_smoke_noWingProp", _boss.rc.left + 150, _boss.rc.top - 35, 45);
					EFFECTMANAGER->update("boss_smoke_noWingProp", 0, -4.8f);
				}

				else
				{
					EFFECTMANAGER->play("boss_smoke_noWingProp", _boss.rc.left + 85, _boss.rc.top + 180, 45);
					EFFECTMANAGER->update("boss_smoke_noWingProp", 0, -4.8f);
				}
			}
		}

		//�������� ���ų�, ���� �� �������
		if (_bossForm == NO_ONE_ARM || _bossForm == NO_ARM)
		{
			EFFECTMANAGER->play("boss_smoke_noOneArm", (_boss.rc.left + _boss.rc.right) / 2,
				(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
			EFFECTMANAGER->update("boss_smoke_noOneArm", 0, -4.8f);
		}

		//���� �������
		if (_bossForm == NO_ARM)
		{
			//���̵� �����϶�, �����
			if (_isIdleState || _isMoveState)
			{
				EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2 - 40,
					_boss.rc.top - 30, 45);
			}

			//���������� �¾�����
			if (_isDamagedState)
			{
				if (_currentFrameX == _boss.img->getMaxFrameX())
				{
					EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2 + 35,
						(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
				}

				else
				{
					EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2,
					(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
				}
			}

			EFFECTMANAGER->update("boss_smoke_noArm", 0, -4.8f);
		}
	}

	//������ �ٶ󺼶�
	else
	{
		//����Ʈ�� �ƴϸ�, �� ������ ���󰡸�
		if (_bossForm != DEFAULT)
		{
			EFFECTMANAGER->play("boss_smoke_noWing", _boss.rc.left + 200, _boss.rc.top + 110, 45);
			EFFECTMANAGER->play("boss_smoke_noWing2", _boss.rc.left + 180, _boss.rc.top + 210, 45);

			EFFECTMANAGER->update("boss_smoke_noWing", 0, -4.8f);
			EFFECTMANAGER->update("boss_smoke_noWing2", 0, -4.8f);
		}

		//�����緯�� ���ų�, �������� ���ų�, ���ȴ� �������
		if (_bossForm == NO_WING_PROP || _bossForm == NO_ONE_ARM || _bossForm == NO_ARM)
		{
			if (_bossForm == NO_ARM)
			{
				EFFECTMANAGER->play("boss_smoke_noWingProp", _boss.rc.right - 165, _boss.rc.top - 35, 45);
				EFFECTMANAGER->update("boss_smoke_noWingProp", 0, -4.8f);
			}

			else
			{
				if (_isJabState || _isDamagedState)
				{
					EFFECTMANAGER->play("boss_smoke_noWingProp", _boss.rc.right - 165, _boss.rc.top - 35, 45);
					EFFECTMANAGER->update("boss_smoke_noWingProp", 0, -4.8f);
				}

				else
				{
					EFFECTMANAGER->play("boss_smoke_noWingProp", _boss.rc.right - 85, _boss.rc.top + 180, 45);
					EFFECTMANAGER->update("boss_smoke_noWingProp", 0, -4.8f);
				}

			}
			
		}

		//�������� ���ų�, ���� �� �������
		if (_bossForm == NO_ONE_ARM || _bossForm == NO_ARM)
		{
			EFFECTMANAGER->play("boss_smoke_noOneArm", (_boss.rc.left + _boss.rc.right) / 2,
				(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
			EFFECTMANAGER->update("boss_smoke_noOneArm", 0, -4.8f);
		}

		//���� �������
		if (_bossForm == NO_ARM)
		{
			//���̵� �����϶�, �����
			if (_isIdleState || _isMoveState)
			{
				EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2 - 30,
					_boss.rc.top - 30, 45);
			}

			//���������� �¾�����
			if (_isDamagedState)
			{
				if (_currentFrameX >= _boss.img->getMaxFrameX())
				{
					EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2,
						(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
				}

				else
				{
					EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2,
						(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
				}
			}

			EFFECTMANAGER->update("boss_smoke_noArm", 0, -4.8f);
		}
	}
}


//////////////////////////////////////////
// ####### ���� �������� ��ġ���ֱ�########
/////////////////////////////////////////
void boss::imgLocation()
{

	///////////////////////////////////////////////
	/////  ### ���� ���󰡰� ��Ʈ #####
	//////////////////////////////////////////////
	if (_bossForm == NO_WING && _isNoWing == false)
	{
		_isNoWing = true;
		_divideX = 0;
		_divideY = 0;
		_divideGravity = 0.75f;

		if (_isLeft)
		{
			_isLeft_LeftNoWing->setX((_boss.rc.right + _boss.rc.left) / 2 + 200);
			_isLeft_LeftNoWing->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 100);
			_isLeft_RightNoWing->setX((_boss.rc.right + _boss.rc.left) / 2);
			_isLeft_RightNoWing->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 300);
			_divideX = 3.f;
			_divideY = 8.f;
		}

		else
		{
			_isRight_LeftNoWing->setX((_boss.rc.right + _boss.rc.left) / 2 );
			_isRight_LeftNoWing->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 300);
			_isRight_RightNoWing->setX((_boss.rc.right + _boss.rc.left) / 2 - 200);
			_isRight_RightNoWing->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 100);
			_divideX = -3.f;
			_divideY = 8.f;
		}
	}
	
	///////////////////////////////////////////////
	/////  ### �����緯 ���󰡰� ��Ʈ #####
	//////////////////////////////////////////////
	if (_bossForm == NO_WING_PROP && !_isNoWingProp)
	{
		_isNoWingProp = true;
		_divideX = 0;
		_divideY = 0;
		_divideGravity = 0.75f;

		if (_isLeft)
		{
			_isLeft_NoWingProp->setX((_boss.rc.right + _boss.rc.left) / 2 - 150);
			_isLeft_NoWingProp->setY(_boss.rc.top - 150);
			_divideX = -3.f;
			_divideY = 8.f;
		}

		else
		{
			_isRight_NoWingProp->setX((_boss.rc.right + _boss.rc.left) / 2 + 100);
			_isRight_NoWingProp->setY(_boss.rc.top - 150);
			_divideX = 3.f;
			_divideY = 8.f;
		}
	}

	///////////////////////////////////////////////
	/////  ### ù��° �� ���󰡰� ��Ʈ #####
	//////////////////////////////////////////////
	if (_bossForm == NO_ONE_ARM && !_isNoOneArm)
	{
		_isNoOneArm = true;
		_divideX = 0;
		_divideY = 0;
		_divideGravity = 0.75f;

		if (_isLeft)
		{
			_isLeft_RightArm->setX((_boss.rc.right + _boss.rc.left) / 2);
			_isLeft_RightArm->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 200);
			_divideX = 3.f;
			_divideY = 8.f;
		}

		else
		{
			_isRight_LeftArm->setX((_boss.rc.right + _boss.rc.left) / 2);
			_isRight_LeftArm->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 200);
			_divideX = -3.f;
			_divideY = 8.f;
		}
	}

	///////////////////////////////////////////////
	/////  ### �ι�° �� ���󰡰� ��Ʈ #####
	//////////////////////////////////////////////
	if (_bossForm == NO_ARM && !_isNoArm)
	{
		_isNoArm = true;
		_divideX = 0;
		_divideY = 0;
		_divideGravity = 0.75f;

		if (_isLeft)
		{
			_isLeft_LeftArm->setX((_boss.rc.right + _boss.rc.left) / 2);
			_isLeft_LeftArm->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 200);
			_divideX = 3.f;
			_divideY = 8.f;
		}

		else
		{
			_isRight_RightArm->setX((_boss.rc.right + _boss.rc.left) / 2);
			_isRight_RightArm->setY((_boss.rc.top + _boss.rc.bottom) / 2 - 200);
			_divideX = -3.f;
			_divideY = 8.f;
		}
	}

	///////////////////////////////////////////////
	/////  ### ���� ���󰡰� ���� #####
	//////////////////////////////////////////////
	if (_isNoWing)
	{

		_divideY -= _divideGravity;
		_isLeft_LeftNoWing->setX(_isLeft_LeftNoWing->getX() + _divideX);
		_isLeft_LeftNoWing->setY(_isLeft_LeftNoWing->getY() - _divideY);
		_isLeft_RightNoWing->setX(_isLeft_RightNoWing->getX() + _divideX);
		_isLeft_RightNoWing->setY(_isLeft_RightNoWing->getY() - _divideY);

		_isRight_LeftNoWing->setX(_isRight_LeftNoWing->getX() + _divideX);
		_isRight_LeftNoWing->setY(_isRight_LeftNoWing->getY() - _divideY);
		_isRight_RightNoWing->setX(_isRight_RightNoWing->getX() + _divideX);
		_isRight_RightNoWing->setY(_isRight_RightNoWing->getY() - _divideY);
	}

	///////////////////////////////////////////////
	/////  ### �����緯 ���󰡰� ���� #####
	//////////////////////////////////////////////
	if (_isNoWingProp)
	{
		_divideY -= _divideGravity;
		_isLeft_NoWingProp->setX(_isLeft_NoWingProp->getX() + _divideX);
		_isLeft_NoWingProp->setY(_isLeft_NoWingProp->getY() - _divideY);
		_isRight_NoWingProp->setX(_isRight_NoWingProp->getX() + _divideX);
		_isRight_NoWingProp->setY(_isRight_NoWingProp->getY() - _divideY);
	}


	///////////////////////////////////////////////
	/////  ### ù��° �� ���󰡰� ���� #####
	//////////////////////////////////////////////
	if (_isNoOneArm)
	{
		_divideY -= _divideGravity;
		_isLeft_RightArm->setX(_isLeft_RightArm->getX() + _divideX);
		_isLeft_RightArm->setY(_isLeft_RightArm->getY() - _divideY);
		_isRight_LeftArm->setX(_isRight_LeftArm->getX() + _divideX);
		_isRight_LeftArm->setY(_isRight_LeftArm->getY() - _divideY);
	}


	///////////////////////////////////////////////
	/////  ### �ι��� �� ���󰡰� ���� #####
	//////////////////////////////////////////////
	if (_isNoArm)
	{
		_divideY -= _divideGravity;
		_isLeft_LeftArm->setX(_isLeft_LeftArm->getX() + _divideX);
		_isLeft_LeftArm->setY(_isLeft_LeftArm->getY() - _divideY);
		_isRight_RightArm->setX(_isRight_RightArm->getX() + _divideX);
		_isRight_RightArm->setY(_isRight_RightArm->getY() - _divideY);
	}
}


