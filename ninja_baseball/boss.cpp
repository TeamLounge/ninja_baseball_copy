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
	//_isPreWind = true; // 임시방편임
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


	if (!_isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_bossShadow.rc = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2, _boss.rc.bottom,
			_bossShadow.img->getWidth(), _bossShadow.img->getHeight());
		_jumpShadowY = (_bossShadow.rc.bottom + _bossShadow.rc.top) / 2;	//점프하기 전까지의 y값을 계속 저장중.

	}
	else   //점프하면
	{
		//그림자
		_bossShadow.rc = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2, _jumpShadowY,
			_bossShadow.img->getWidth(), _bossShadow.img->getHeight());	//점프하기 전의 y값을 사용
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
	//보스 상태마다 이미지크기가 달라서 위치를 조정하기 위해 만들었음
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
	//     ## 디버그용 렉트 ##        //
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
// ########## 보스 이미지 등록 ###########
/////////////////////////////////////////
void boss::setImage()
{
	////////////////////////////////////////////
	//  ###### 보스 움직임 이미지 ##########   //
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
	//  ###### 보스 기타 이미지(체력바, 파편, 쉐도우 등) ##########     //
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
	//  ###### 보스 이펙트 #########
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
// ########## 보스 초기설정값 ###########
/////////////////////////////////////////
void boss::setBoss()
{
	//형태 초기화
	_bossForm = DEFAULT;
	//현재 프레임 확인용 초기화
	_currentFrameX = _currentFrameY = 0;
	//보스 위치확인용
	_isLeft = _isUpper = false;
	//보스 스피드
	_speed = 0;
	//보스 형태 변환용
	_count = _stateCount = 0;
	//보스 핀조명 스위치
	_isPinLight = false;
	//알파 인덱스
	_alphaIdx = 255;
	_alphaCnt = 0;
	_isAlpha = false;
	//총질 넘버링
	_numAtkPattern = 0;
	//총쐇는지 여부와 총으로맞췄는지 여부
	_isTrigger = false;
	_isSucceedShootingAttack = false;
	//잽 여부와 잽 성공여부
	_isJabAttack = false;
	_isSucceedJabAttack = false;
	_isJabState = false;
	//잽 공격요건에 충족되었는지 확인
	_isCrash = false;
	_missCount = 0;
	//스트레이트 공격 여부와 성공여부
	_isStraightAttack = false;
	_isSucceedStraightAttack = false;
	_isStraightState = false;
	//어퍼컷 공격 여부와 성공여부
	_isUpperCut = false;
	_isSucceedUpperCut = false;
	_isUpperCutState = false;
	//데미지가 들어왔는지 여부
	_isDamaged = false;
	_isDamagedState = false;
	//연습용불값
	_isAttacked = false;
	//무브상태
	_isMoveState = false;
	//아이들상태
	_isIdleState = false;
	//슈팅상태
	_isShootingState = false;
	//죽음의 상태
	_isDeathState = false;
	_isNoWing = _isNoWingProp = _isNoOneArm = _isNoArm = false;
	_divideX = _divideY = _divideGravity = 0;
	//작은 공격 들어왔을때
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
// ########## 보스 그림자 ###########
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
// ########## 보스 위치실시간조정 ###########
///////////////////////////////////////////
void boss::renderAdjust()
{
	//나머지 특정조건일때는 이거다~

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
// ######## 상태에 따른 스모크효과 ########## 계속 상세하게 처리해해야됨;;;;개오바야
///////////////////////////////////////////
void boss::smokeEffect()
{
	//좌측을 바라볼때
	if (_isLeft)
	{
		//디폴트가 아니면, 즉 날개가 날라가면
		if (_bossForm != DEFAULT)
		{
			EFFECTMANAGER->play("boss_smoke_noWing", _boss.rc.right - 200, _boss.rc.top + 110, 45);
			EFFECTMANAGER->play("boss_smoke_noWing2", _boss.rc.right - 180, _boss.rc.top + 210, 45);

			EFFECTMANAGER->update("boss_smoke_noWing", 0, -4.8f);
			EFFECTMANAGER->update("boss_smoke_noWing2", 0, -4.8f);
		}

		//프로펠러도 없거나, 한쪽팔이 없거나, 두팔다 없을경우
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

		//한쪽팔이 없거나, 두팔 다 없을경우
		if (_bossForm == NO_ONE_ARM || _bossForm == NO_ARM)
		{
			EFFECTMANAGER->play("boss_smoke_noOneArm", (_boss.rc.left + _boss.rc.right) / 2,
				(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
			EFFECTMANAGER->update("boss_smoke_noOneArm", 0, -4.8f);
		}

		//두팔 없을경우
		if (_bossForm == NO_ARM)
		{
			//아이들 상태일때, 무브랑
			if (_isIdleState || _isMoveState)
			{
				EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2 - 40,
					_boss.rc.top - 30, 45);
			}

			//데미지를쳐 맞았을때
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

	//우측을 바라볼때
	else
	{
		//디폴트가 아니면, 즉 날개가 날라가면
		if (_bossForm != DEFAULT)
		{
			EFFECTMANAGER->play("boss_smoke_noWing", _boss.rc.left + 200, _boss.rc.top + 110, 45);
			EFFECTMANAGER->play("boss_smoke_noWing2", _boss.rc.left + 180, _boss.rc.top + 210, 45);

			EFFECTMANAGER->update("boss_smoke_noWing", 0, -4.8f);
			EFFECTMANAGER->update("boss_smoke_noWing2", 0, -4.8f);
		}

		//프로펠러도 없거나, 한쪽팔이 없거나, 두팔다 없을경우
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

		//한쪽팔이 없거나, 두팔 다 없을경우
		if (_bossForm == NO_ONE_ARM || _bossForm == NO_ARM)
		{
			EFFECTMANAGER->play("boss_smoke_noOneArm", (_boss.rc.left + _boss.rc.right) / 2,
				(_boss.rc.top + _boss.rc.bottom) / 2 - 100, 45);
			EFFECTMANAGER->update("boss_smoke_noOneArm", 0, -4.8f);
		}

		//두팔 없을경우
		if (_bossForm == NO_ARM)
		{
			//아이들 상태일때, 무브랑
			if (_isIdleState || _isMoveState)
			{
				EFFECTMANAGER->play("boss_smoke_noArm", (_boss.rc.left + _boss.rc.right) / 2 - 30,
					_boss.rc.top - 30, 45);
			}

			//데미지를쳐 맞았을때
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
// ####### 조각 떨어질때 배치해주기########
/////////////////////////////////////////
void boss::imgLocation()
{

	///////////////////////////////////////////////
	/////  ### 날개 날라가게 세트 #####
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
	/////  ### 프로펠러 날라가게 세트 #####
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
	/////  ### 첫번째 팔 날라가게 세트 #####
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
	/////  ### 두번째 팔 날라가게 세트 #####
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
	/////  ### 날개 날라가게 무브 #####
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
	/////  ### 프로펠러 날라가게 무브 #####
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
	/////  ### 첫번째 팔 날라가게 무브 #####
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
	/////  ### 두번쨰 팔 날라가게 무브 #####
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


