#include "stdafx.h"
#include "glove.h"
#include "gloveJumpState.h"		//초기 등장씬

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

	_imgName = "glove_attackTongue";		//초기 크기 잡아주기 위해 어떠한 이름이든 다 담을 수 있는 제일 큰거 쓰자
	_shadowName = "glove_shadow";

	RENDERMANAGER->addObj("glove", _imgName.c_str(), _shadowName.c_str(), &_imageX, &_imageY,
		&_gloveShadow.x, &_gloveShadow.y, &_currentFrameX, &_currentFrameY);

	_gloveState = new gloveJumpState();		//점프로 등장
	_gloveState->enter(this);

	_glove.x = position.x;
	_glove.y = position.y;		//포지션 입력값 받아올거고

	//이미지태그용
	_imageX = _glove.x;
	_imageY = _glove.y;

	//이미지 좌표 셋
	_glove.img->setX(_glove.x);
	_glove.img->setY(_glove.y);	//이미지도 좌표에 맞게 뿌려줬고

	//에너미
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 200, 300, 232);
	//그림자
	_gloveShadow.y = _glove.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.

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

	//상태 변화에 따른 이미지 bool값
	isAttackTongueState = false;
	isJumpState = false;
	isMoveState = false;

	damagedCount = 0;

	isattack = false;               //에너미가 공격했어??
	isdamage = false;				//에너미가 데미지 받았어??							
	iscatch = false;				//에저미가 잡혔어??

	

	return S_OK;
}

void glove::release()
{
	_gloveState->exit(this);
}

void glove::update()
{
	//에너미
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 140, 200, 232);

	if (!isJump)	//jump가 false이면 그림자가 따라다닌다. => 점프 아닐 떄
	{
		//그림자
		_gloveShadow.y = _glove.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.
		_gloveShadow.x = (_glove.rc.right + _glove.rc.left) / 2;	//점프하기 전까지의 y값을 계속 저장중.
		_gloveShadow.rc = RectMakeCenter(_gloveShadow.x, _gloveShadow.y, 215, 50);
	}
	else   //점프하면
	{
		//그림자
		_gloveShadow.x = (_glove.rc.right + _glove.rc.left) / 2;	//점프하기 전까지의 y값을 계속 저장중.
		_gloveShadow.rc = RectMakeCenter(_gloveShadow.x, _gloveShadow.y, 215, 50);	//점프하기 전의 y값을 사용
	}

	//GLOVE 상태마다 변하는 이미지 잡아주기
	modifiedLocation();

	InputHandle();
	_gloveState->update(this);
}

void glove::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _glove.rcAttackRange);	//공격 범위 렉트
		Rectangle(getMemDC(), _glove.rc);				//에너미 렉트
		Rectangle(getMemDC(), _gloveShadow.rc);			//그림자 렉트
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

//공격 시 이미지 이동됨.... 좌표 수정 위함
void glove::modifiedLocation()
{
	if (isRight)//오른쪽 볼 때
	{
		if (isAttackTongueState)	//공격중일 때
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 200;
		}
		else if (isJumpState)		//점프 상태
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 200;
		}
		else if (isMoveState)		//이동 상태
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 500;
		}
		else
		{
			_imageX = _glove.x;
		}	_imageY = _glove.y;
	}
	else //왼쪽 볼 때
	{
		if (isAttackTongueState)	//공격중일 때
		{
			_imageX = _glove.x;
			_imageY = _glove.y;
		}
		else if (isJumpState)		//점프 상태
		{
			_imageX = _glove.x + 100;
			_imageY = _glove.y + 200;
		}
		else if (isMoveState)		//이동 상태
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