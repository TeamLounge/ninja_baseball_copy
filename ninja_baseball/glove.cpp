#include "stdafx.h"
#include "glove.h"
#include "gloveJumpState.h"		//�ʱ� �����

void glove::InputHandle()
{
	gloveState* newState = _gloveState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_gloveState);
		_gloveState = newState;
		_gloveState->enter(this);
	}
}

HRESULT glove::init()
{
	return S_OK;
}

HRESULT glove::init(POINT position)
{
	setImage();
	_glove.img = new image();

	setShadow();

	isJump = true;	//true

	_gloveState = new gloveJumpState();		//������ ����
	_gloveState->enter(this);

	_glove.x = position.x;
	_glove.y = position.y;		//������ �Է°� �޾ƿðŰ�

	//�̹��� ��ǥ ��
	_glove.img->setX(_glove.x);
	_glove.img->setY(_glove.y);	//�̹����� ��ǥ�� �°� �ѷ����

	//���ʹ�
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 200, 300, 232);

	//�׸���
	_gloveShadow.y = _glove.rc.bottom;	//�����ϱ� �������� y���� ��� ������.

	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isXOverlap = false;
	isYOverlap = false;
	isLand = false;

	return S_OK;
}

void glove::release()
{
	_gloveState->exit(this);
}

void glove::update()
{

	InputHandle();

	//���ʹ�
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 200, 300, 232);

	if (!isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_gloveShadow.rc = RectMakeCenter((_glove.rc.right + _glove.rc.left) / 2, _glove.rc.bottom, 215, 50);
		_gloveShadow.y = _glove.rc.bottom;	//�����ϱ� �������� y���� ��� ������.
	}
	else   //�����ϸ�
	{
		//�׸���
		_gloveShadow.rc = RectMakeCenter((_glove.rc.right + _glove.rc.left) / 2, _gloveShadow.y, 215, 50);	//�����ϱ� ���� y���� ���
	}

	_gloveState->update(this);
}

void glove::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _glove.rcAttackRange);	//���� ���� ��Ʈ
		Rectangle(getMemDC(), _glove.rc);				//���ʹ� ��Ʈ
		Rectangle(getMemDC(), _gloveShadow.rc);					//�׸��� ��Ʈ

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}

	_gloveShadow.img->render(getMemDC(), _gloveShadow.rc.left, _gloveShadow.rc.top);
	
}

void glove::setImage()
{
	IMAGEMANAGER->addFrameImage("glove_attackTongue", "image/3_Enemy/glove/glove_attackTongue.bmp", 2320, 520, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_damaged", "image/3_Enemy/glove/glove_damaged.bmp", 2380, 510, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_jump", "image/3_Enemy/glove/glove_jump.bmp", 1440, 600, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_move", "image/3_Enemy/glove/glove_move.bmp", 1260, 510, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_deathRing", "image/3_Enemy/glove/glove_deathRing.bmp", 288, 96, 3, 1, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("glove_Death", "image/3_Enemy/glove/glove_Death.bmp", 240, 300, true, RGB(255, 0, 255), false);
}
void glove::setShadow()
{

	IMAGEMANAGER->addImage("glove_shadow", "image/3_Enemy/glove/glove_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_gloveShadow.img = IMAGEMANAGER->findImage("glove_shadow");
}

void glove::modifiedLocation()
{
	//���� �� �̹��� �̵���.... ��ǥ ���� ����
	if (isAttackTongueState)
	{
		if (!isRight)
		{
			_glove.img->frameRender(getMemDC(), _glove.x, _glove.y + 70, _currentFrameX, _currentFrameY);
		}
		if (isRight)
		{
			_glove.img->frameRender(getMemDC(), _glove.x + 100, _glove.y + 70, _currentFrameX, _currentFrameY);
		}
	}
	if (isJumpState)
	{
		_glove.img->frameRender(getMemDC(), _glove.x + 70, _glove.y + 30, _currentFrameX, _currentFrameY);
	}
	if (!isAttackTongueState && !isJumpState)
	{
		_glove.img->frameRender(getMemDC(), _glove.x + 100, _glove.y + 70, _currentFrameX, _currentFrameY);
	}
}
