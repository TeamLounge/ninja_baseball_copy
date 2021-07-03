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

	_imgName = "glove_attackTongue";

	_gloveState = new gloveJumpState();		//점프로 등장
	_gloveState->enter(this);

	_glove.x = position.x;
	_glove.y = position.y;		//포지션 입력값 받아올거고

	//이미지 좌표 셋
	_glove.img->setX(_glove.x);
	_glove.img->setY(_glove.y);	//이미지도 좌표에 맞게 뿌려줬고

	//에너미
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 200, 300, 232);
	//그림자
	_gloveShadow.y = _glove.rc.bottom;	//점프하기 전까지의 y값을 계속 저장중.				//배트엔 없는데.. 없애도 되나..? 있어야 함. 왜지........

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

	isattack = false;              //에너미가 공격했어??
	isdamage = false;				//에너미가 데미지 받았어??							
	iscatch = false;				//에저미가 잡혔어??

	RENDERMANAGER->addObj("glove", _imgName.c_str(), "glove_shadow",
		&_glove.x, &_glove.y, &_gloveShadow.x, &_gloveShadow.y,
		&_currentFrameX, &_currentFrameY);

	return S_OK;
}

void glove::release()
{
	_gloveState->exit(this);
}

void glove::update()
{
	//에너미
	_glove.rc = RectMakeCenter(_glove.x + 200, _glove.y + 200, 150, 232);

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
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
		SelectObject(getMemDC(), myPen);

		Rectangle(getMemDC(), _glove.rcAttackRange);	//공격 범위 렉트
		Rectangle(getMemDC(), _glove.rc);				//에너미 렉트
		Rectangle(getMemDC(), _gloveShadow.rc);			//그림자 렉트

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}

	//_gloveShadow.img->render(getMemDC(), _gloveShadow.rc.left, _gloveShadow.rc.top);
	//_glove.img->frameRender(getMemDC(), _glove.x, _glove.y + 50, _currentFrameX, _currentFrameY);
	
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
	//공격 중일 때의 이미지
	if (isAttackTongueState)
	{
		if (!isRight)	//좌
		{
			_glove.img->frameRender(getMemDC(), _glove.x, _glove.y + 70, _currentFrameX, _currentFrameY);
		}
		if (isRight)	//우
		{
			_glove.img->frameRender(getMemDC(), _glove.x + 100, _glove.y + 70, _currentFrameX, _currentFrameY);
		}
	}
	//점프일 때의 이미지
	if (isJumpState)
	{
		_glove.img->frameRender(getMemDC(), _glove.x + 70, _glove.y + 30, _currentFrameX, _currentFrameY);
	}
	/*if (!isAttackTongueState && !isJumpState)
	{
		_glove.img->frameRender(getMemDC(), _glove.x + 100, _glove.y + 70, _currentFrameX, _currentFrameY);
	}*/

	//움직일 때의 이미지
	if (isMoveState)
	{
		if (!isRight)	//왼쪽 보면
		{
			_glove.img->frameRender(getMemDC(), _glove.x, _glove.y + 70, _currentFrameX, _currentFrameY);
		}
		if (isRight)	//오른쪽 보면
		{
			_glove.img->frameRender(getMemDC(), _glove.x + 150, _glove.y + 70, _currentFrameX, _currentFrameY);
		}
	}
}
