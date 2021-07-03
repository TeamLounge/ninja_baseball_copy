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

	_imgName = "glove_attackTongue";		//�ʱ� ũ�� ����ֱ� ���� ��� �̸��̵� �� ���� �� �ִ� ���� ū�� ����
	_shadowName = "glove_shadow";

	RENDERMANAGER->addObj("glove", _imgName.c_str(), _shadowName.c_str(), &_imageX, &_imageY,
		&_gloveShadow.x, &_gloveShadow.y, &_currentFrameX, &_currentFrameY);

	_gloveState = new gloveJumpState();		//������ ����
	_gloveState->enter(this);

	_glove.x = position.x;
	_glove.y = position.y;		//������ �Է°� �޾ƿðŰ�

	//�̹����±׿�
	_imageX = _glove.x;
	_imageY = _glove.y;

	//�̹��� ��ǥ ��
	_glove.img->setX(_glove.x);
	_glove.img->setY(_glove.y);	//�̹����� ��ǥ�� �°� �ѷ����

	//���ʹ�
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 200, 300, 232);
	//�׸���
	_gloveShadow.y = _glove.rc.bottom;	//�����ϱ� �������� y���� ��� ������.

	isJump = true;	//true
	isRight = false;
	isDown = false;
	isCollisionAttack = false;
	isCollisionDamaged = false;
	isXOverlap = false;
	isYOverlap = false;
	isLand = false;
	isDamaged = false;
	isDeath = false;

	//���� ��ȭ�� ���� �̹��� bool��
	isAttackTongueState = false;
	isJumpState = false;
	isMoveState = false;

	damagedCount = 0;

	isattack = false;               //���ʹ̰� �����߾�??
	isdamage = false;				//���ʹ̰� ������ �޾Ҿ�??							
	iscatch = false;				//�����̰� ������??

	

	return S_OK;
}

void glove::release()
{
	_gloveState->exit(this);
}

void glove::update()
{
	//���ʹ�
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 140, 200, 232);

	if (!isJump)	//jump�� false�̸� �׸��ڰ� ����ٴѴ�. => ���� �ƴ� ��
	{
		//�׸���
		_gloveShadow.y = _glove.rc.bottom;	//�����ϱ� �������� y���� ��� ������.
		_gloveShadow.x = (_glove.rc.right + _glove.rc.left) / 2;	//�����ϱ� �������� y���� ��� ������.
		_gloveShadow.rc = RectMakeCenter(_gloveShadow.x, _gloveShadow.y, 215, 50);
	}
	else   //�����ϸ�
	{
		//�׸���
		_gloveShadow.x = (_glove.rc.right + _glove.rc.left) / 2;	//�����ϱ� �������� y���� ��� ������.
		_gloveShadow.rc = RectMakeCenter(_gloveShadow.x, _gloveShadow.y, 215, 50);	//�����ϱ� ���� y���� ���
	}

	//GLOVE ���¸��� ���ϴ� �̹��� ����ֱ�
	modifiedLocation();

	InputHandle();
	_gloveState->update(this);
}

void glove::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _glove.rcAttackRange);	//���� ���� ��Ʈ
		Rectangle(getMemDC(), _glove.rc);				//���ʹ� ��Ʈ
		Rectangle(getMemDC(), _gloveShadow.rc);			//�׸��� ��Ʈ
	}
}

void glove::setImage()
{
	IMAGEMANAGER->addFrameImage("glove_attackTongue", "image/3_Enemy/glove/glove_attackTongue.bmp", 2320, 520, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_damaged", "image/3_Enemy/glove/glove_damaged.bmp", 1360, 510, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_death", "image/3_Enemy/glove/glove_death.bmp", 1020, 510, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_jump", "image/3_Enemy/glove/glove_jump.bmp", 1440, 600, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_move", "image/3_Enemy/glove/glove_move.bmp", 1260, 510, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("glove_deathRing", "image/3_Enemy/glove/glove_deathRing.bmp", 288, 96, 3, 1, true, RGB(255, 0, 255), false);
}
void glove::setShadow()
{

	IMAGEMANAGER->addImage("glove_shadow", "image/3_Enemy/glove/glove_shadow.bmp", 215, 50, true, RGB(255, 0, 255), false);
	_gloveShadow.img = IMAGEMANAGER->findImage("glove_shadow");
}

//���� �� �̹��� �̵���.... ��ǥ ���� ����
void glove::modifiedLocation()
{
	if (isRight)//������ �� ��
	{
		if (isAttackTongueState)	//�������� ��
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 200;
		}
		else if (isJumpState)		//���� ����
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 200;
		}
		else if (isMoveState)		//�̵� ����
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 500;
		}
		else
		{
			_imageX = _glove.x;
		}	_imageY = _glove.y;
	}
	else //���� �� ��
	{
		if (isAttackTongueState)	//�������� ��
		{
			_imageX = _glove.x;
			_imageY = _glove.y;
		}
		else if (isJumpState)		//���� ����
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 200;
		}
		else if (isMoveState)		//�̵� ����
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 500;
		}
		else
		{
			_imageX = _glove.x;
		}	_imageY = _glove.y;
	}
}