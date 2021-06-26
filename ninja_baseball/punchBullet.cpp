#include "stdafx.h"
#include "punchBullet.h"

HRESULT punchBullet::init()
{
	return S_OK;
}

HRESULT punchBullet::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void punchBullet::release()
{
}

void punchBullet::update()
{
	move();
}

void punchBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->Bulletimg->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void punchBullet::fire(float x, float y, float angle, float speed)
{

}

void punchBullet::move()
{
}
