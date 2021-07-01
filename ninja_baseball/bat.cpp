#include "stdafx.h"
#include "bat.h"
#include "batMoveState.h"

void bat::InputHandle()
{
	batState* newState = _batState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_batState);
		_batState = newState;
		_batState->enter(this);
	}
}

HRESULT bat::init()
{
	return S_OK;
}

HRESULT bat::init(POINT position)
{
	setImage();
	_bat.img = new image();

	setShadow();

	_batState = new batMoveState();		//����� ����
	_batState->enter(this);

	_bat.x = position.x;
	_bat.y = position.y;

	_bat.img->setX(_bat.x);
	_bat.img->setY(_bat.y);

	//���� �浹 ��Ʈ
	//_bat.rcStop = RectMakeCenter(_bat.x - RND->getFromIntTo(800, 900), _bat.y + 200, 50, 100);

	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isJump = false;

	isDeath = false;

	_batMode = NORMAL;		//�ʱ� ��� set

	damageCount = 0;		//���� Ƚ��

	isXOverlap = false;
	isYOverlap = false;
	isAttack = false;				//�ƾ�?
	isDamaged = false;				//�¾Ҿ�?
	iscatch = false;				//������?
	isCrash = false;

	RENDERMANAGER->addObj("bat", _imgName.c_str(), "bat_shadow",
		&_bat.x, &_bat.y, &_batShadow.x, &_batShadow.y,
		&_currentFrameX, &_currentFrameY);

	return S_OK;
}

void bat::release()
{
	_batState->exit(this);
}

void bat::update()
{
	//���ʹ�
	_bat.rc = RectMakeCenter(_bat.x + 310, _bat.y + 185, 200, 250);	//bat.x, bat.y�� ������ǥ

	if (!isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_batShadow.rc = RectMakeCenter((_bat.rc.right + _bat.rc.left) / 2, _bat.rc.bottom, 120, 50);
		_batShadow.x = (_bat.rc.right + _bat.rc.left) / 2;
		_batShadow.y = _bat.rc.bottom;	//�����ϱ� �������� y���� ��� ������.

	}
	else   //�����ϸ�(������ ������ �°� ���ư� �� �� �� �ִ�)
	{
		//�׸���
		_batShadow.rc = RectMakeCenter((_bat.rc.right + _bat.rc.left) / 2, _batShadow.y, 120, 50);	//�����ϱ� ���� y���� ���
	}

	//////////////////////////
	//		3�� ����			//
	//////////////////////////
	//if (KEYMANAGER->isOnceKeyDown('M') && !isCollisionDamaged)
	//{
	//	damageCount++;
	//	if (damageCount == 3) _batMode = NO_CAP;
	//	else if (damageCount == 4) _batMode = NO_BAT;
	//	else if (damageCount == 5)
	//	{
	//		_batMode = DEATH;
	//		isDeath = true;
	//	}

	//	isCollisionDamaged = true;
	//}


	if (damageCount == 3) _batMode = NO_CAP;
	else if (damageCount == 4) _batMode = NO_BAT;
	else if (damageCount == 5)
	{
		_batMode = DEATH;
		isDeath = true;
	}

	InputHandle();
	_batState->update(this);
}

void bat::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _bat.rcAttackRange);	//���� ���� ��Ʈ
		Rectangle(getMemDC(), _bat.rc);				//���ʹ� ��Ʈ
		Rectangle(getMemDC(), _batShadow.rc);		//�׸��� ��Ʈ

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}

	//_batShadow.img->render(getMemDC(), _batShadow.rc.left, _batShadow.rc.top);
	//_bat.img->frameRender(getMemDC(), _bat.x, _bat.y, _currentFrameX, _currentFrameY);

}

void bat::setImage()
{
		IMAGEMANAGER->addFrameImage("fBat_idle", "image/3_Enemy/bat/fBat_idle.bmp", 1200, 600, 2, 2, true, RGB(255, 0, 255), false);//������ 900*2�ε�, 600 *2�� ¥�εż��� ����� �ǳ�..���ű��ϳ�.......
		IMAGEMANAGER->addFrameImage("sBat_idle", "image/3_Enemy/bat/sBat_idle.bmp", 1200, 600, 2, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("tBat_idle", "image/3_Enemy/bat/tBat_idle.bmp", 1200, 600, 2, 2, true, RGB(255, 0, 255), false);

		IMAGEMANAGER->addFrameImage("fBat_move", "image/3_Enemy/bat/fBat_move.bmp", 1800, 600, 3, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("sBat_move", "image/3_Enemy/bat/sBat_move.bmp", 1800, 600, 3, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("tBat_move", "image/3_Enemy/bat/tBat_move.bmp", 1800, 600, 3, 2, true, RGB(255, 0, 255), false);

		IMAGEMANAGER->addFrameImage("fBat_attack", "image/3_Enemy/bat/fBat_attack.bmp", 9000, 600, 15, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("sBat_attack", "image/3_Enemy/bat/sBat_attack.bmp", 9000, 600, 15, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("tBat_attack", "image/3_Enemy/bat/tBat_attack.bmp", 9000, 600, 15, 2, true, RGB(255, 0, 255), false);

		IMAGEMANAGER->addFrameImage("fBat_damaged", "image/3_Enemy/bat/fBat_damaged.bmp", 2400, 600, 4, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("sBat_damaged", "image/3_Enemy/bat/sBat_damaged.bmp", 2400, 600, 4, 2, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addFrameImage("tBat_damaged", "image/3_Enemy/bat/tBat_damaged.bmp", 2400, 600, 4, 2, true, RGB(255, 0, 255), false);

		IMAGEMANAGER->addFrameImage("bat_burn", "image/3_Enemy/bat/bat_burn.bmp", 3600, 600, 6, 2, true, RGB(255, 0, 255), false);
		
		IMAGEMANAGER->addImage("bat_cap", "image/3_Enemy/bat/bat_cap.bmp", 90, 90, true, RGB(255, 0, 255), false);
		IMAGEMANAGER->addImage("bat_bat", "image/3_Enemy/bat/bat_bat.bmp", 165, 255, true, RGB(255, 0, 255), false);
}

void bat::setShadow()
{
	IMAGEMANAGER->addImage("bat_shadow", "image/3_Enemy/bat/bat_shadow.bmp", 120, 28, true, RGB(255, 0, 255), false);
	_batShadow.img = IMAGEMANAGER->findImage("bat_shadow");
}
