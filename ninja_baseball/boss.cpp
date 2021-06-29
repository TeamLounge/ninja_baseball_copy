#include "stdafx.h"
#include "boss.h"
#include "bossEntryState.h"

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

	setBoss();

	_bossState = new bossEntryState();
	_bossState->enter(this);

	_boss.x = position.x;
	_boss.y = position.y;

	_boss.img->setX(_boss.x);
	_boss.img->setY(_boss.y);

	_bossPinLight.img = new image;

	setBossShadow();
	return S_OK;
}



void boss::release()
{
	_bossState->exit(this);
}

void boss::update()
{
	//Ÿ�� �����ϱ� ���� ���Դϴ�^^//
	if (KEYMANAGER->isOnceKeyDown('A') && !_isAttacked)
	{
		_count++;
		if (_count >= 15)
		{
			_count = 0;
		}

		_isAttacked = true;
	}

	if (_count == 0) _bossForm = DEFAULT;
	if (_count == 3) _bossForm = NO_WING;
	if (_count == 6) _bossForm = NO_WING_PROP;
	if (_count == 9) _bossForm = NO_ONE_ARM;
	if (_count == 12) _bossForm = NO_ARM;

	//������� Ÿ�ݿ����� ���� ���Դϴ�.//

	InputHandle();
	_bossState->update(this);


	_boss.rc = RectMake(_boss.x, _boss.y, 579, 429);


	if (!_isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_bossShadow.rc = RectMakeCenter((_boss.rc.left + _boss.rc.right) / 2, _boss.rc.bottom,
			_bossShadow.img->getWidth(), _bossShadow.img->getHeight());
		_jumpShadowY = _bossShadow.rc.bottom;	//�����ϱ� �������� y���� ��� ������.

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

		if (_isAlpha && _alphaCnt % 8 == 0) _alphaIdx = 0;
		if (_isAlpha && _alphaCnt % 8 != 0) _alphaIdx = 255;
	}
}

void boss::render()
{
	_bossShadow.img->render(getMemDC(), _bossShadow.rc.left, _bossShadow.rc.top);
	if (_isPinLight) _bossPinLight.img->alphaRender(getMemDC(), _boss.x + 100, _boss.y - 150, _alphaIdx);

	if (_isJabState) _boss.img->frameRender(getMemDC(), _boss.x - 100, _boss.y - 162, _currentFrameX, _currentFrameY);
	if (_isStraightState) _boss.img->frameRender(getMemDC(), _boss.x - 167, _boss.y - 191, _currentFrameX, _currentFrameY);

	if (!_isJabState && !_isStraightState) 	_boss.img->frameRender(getMemDC(), _boss.x, _boss.y, _currentFrameX, _currentFrameY);

	
	
	EFFECTMANAGER->render();

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
	IMAGEMANAGER->addFrameImage("boss_shootingProp", "image/4_Boss/boss_gun_prop.bmp", 1188, 858, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_shootingReady", "image/4_Boss/boss_gun_ready.bmp", 7722, 858, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_idle", "image/4_Boss/boss_idle(basic).bmp", 2316, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_oneTwoPunch", "image/4_Boss/boss_onetwo.bmp", 11840, 1182, 16, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_straight", "image/4_Boss/boss_straight.bmp", 27900, 1240, 31, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_upperCut", "image/4_Boss/boss_upper_cut.bmp", 6600, 1302, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("boss_wind", "image/4_Boss/boss_wind.bmp", 3462, 860, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_attacked", "image/4_Boss/boss_attacked(no_wing).bmp", 2500, 1176, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_shooting", "image/4_Boss/boss_gun(no_wing).bmp", 2016, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_shootingProp", "image/4_Boss/boss_gun_prop(no_wing).bmp", 1002, 858, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_shootingReady", "image/4_Boss/boss_gun_ready(no_wing).bmp", 6513, 858, 13, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_idle", "image/4_Boss/boss_idle(no_wing).bmp", 1956, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_upperCut", "image/4_Boss/boss_upper_cut(no_wing).bmp", 6380, 1302, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWing_oneTwoPunch", "image/4_Boss/sboss_onetwo.bmp", 11100, 1182, 15, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_attacked", "image/4_Boss/boss_attacked(no_wing_prop).bmp", 2500, 1176, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_idle", "image/4_Boss/boss_idle(no_wing_Prop).bmp", 1956, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_upperCut", "image/4_Boss/boss_upper_cut(no_wing_prop).bmp", 5270, 1302, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noWingProp_oneTwoPunch", "image/4_Boss/tboss_onetwo.bmp", 11840, 1182, 16, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noOneArm_idle", "image/4_Boss/boss_idle(no_one_arm).bmp", 1956, 858, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noOneArm_attacked", "image/4_Boss/boss_attacked(no_one_arm).bmp", 2225, 1092, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noArm_attacked", "image/4_Boss/boss_attacked(no_arm).bmp", 2225, 1092, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("noArm_move", "image/4_Boss/boss_final.bmp", 742, 1068, 2, 2, true, RGB(255, 0, 255), false);

	///////////////////////////////////////////////////////////////////
	//  ###### ���� ��Ÿ �̹���(ü�¹�, ����, ������ ��) ##########     //
	///////////////////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("boss_greenBar", "image/4_Boss/boss_greenBar.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_redBar", "image/4_Boss/boss_redBar.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_yellowBar", "image/4_Boss/boss_yellowBar.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_yellowBarAttack", "image/4_Boss/boss_yellowBarAttack.bmp", 192, 8, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_leftWing", "image/4_Boss/boss_left_wing.bmp", 231, 216, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_rightWing", "image/4_Boss/boss_right_wing.bmp", 135, 150, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_shadow", "image/4_Boss/boss_shadow.bmp", 300, 85, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("boss_pinLight", "image/4_Boss/boss_pin_light.bmp", 384, 624, true, RGB(255, 0, 255), true);

	//////////////////////////////////////////
	//  ###### ���� ����Ʈ #########
	/////////////////////////////////////////
	EFFECTMANAGER->addEffect("boss_windEffect", "image/4_Boss/boss_windEffect.bmp", 1070, 101, 107, 101, 1.1f, 0.35f, 6);
	EFFECTMANAGER->addEffect("boss_windEffect2", "image/4_Boss/boss_windEffect.bmp", 1070, 101, 107, 101, 1.1f, 0.35f, 6);
	EFFECTMANAGER->addEffect("boss_bullet", "image/4_Boss/boss_bullet_effect.bmp", 384, 192, 48, 192, 1.0f, 0.12f, 20);
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


