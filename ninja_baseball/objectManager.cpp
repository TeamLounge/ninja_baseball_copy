#include "stdafx.h"
#include "objectManager.h"
#include "player.h"
HRESULT objectManager::init()
{
	setTrahCan();
	setBaseBall();
	setBanana();
	return S_OK;
}


void objectManager::release()
{

}

void objectManager::update()
{
	for (_vitrash = _vtrash.begin(); _vitrash != _vtrash.end(); _vitrash++)
	{
		(*_vitrash)->update();
	}
	collsion();
	updateBall();
	updateBanana();
}

void objectManager::render()
{
	char str[128];
	char str1[128];
	
	for (_vitrash = _vtrash.begin(); _vitrash != _vtrash.end(); _vitrash++)
	{
		(*_vitrash)->render();
	}
	_ball->render();
	if (!_banana->iseat) {
		_banana->render();
	}

	if (_ball->ishold)
	{
		sprintf_s(str, " 잡혓쏘히잉");
		TextOut(getMemDC(), _ball->getX()-10, _ball->getY()-10,str, strlen(str));
	}
	if (_banana->iseat)
	{
		sprintf_s(str1, " 먹혔어히잉");
		TextOut(getMemDC(), _banana->getX() +100, _banana->getY() - 100, str1, strlen(str1));
	}
}

void objectManager::setBaseBall()
{
	_ball = new baseball;
	_ball->init(PointMake((int)_vtrash[0]->getX(), (int)_vtrash[0]->getShadowRect().top));
}

void objectManager::setTrahCan()
{
	for (int i = 0; i < 2; i++)
	{
		trashCan* _trashCan = new trashCan;
		if (i == 0) 
		{
			_trashCan->init(PointMake(794, 408), i);
		}
		if (i == 1)
		{
			_trashCan->init(PointMake(794, 578), i);
		}
		_vtrash.push_back(_trashCan);
	}
}

void objectManager::setBanana()
{
	_banana = new banana;
	_banana->init(PointMake((int)_vtrash[1]->getX(), (int)_vtrash[1]->getShadowRect().top));

}

void objectManager::updateBall()
{
	RECT rc;
	if (_ball->ishold)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_ball->ishold = false;
			_ball->isattack = true;
		}
		if (_player->isRight)
		{
			_ball->setX(_player->getX() + _player->_shadow->getWidth() - 20);
			_ball->setY(_player->getY());

			_ball->setShadowX(_ball->getX());
			_ball->setShadowY(_player->_shadow->getCenterY());

			_ball->getShadow()->setCenter(_ball->getShadowX(), _ball->getShadowY());

			_ball->getImage()->setCenter(_ball->getX(), _ball->getY());

			rc = RectMakeCenter(_ball->getX(), _ball->getY(), _ball->getImage()->getWidth(), _ball->getImage()->getHeight());
			_ball->setRect(rc);

			rc = RectMakeCenter(_ball->getShadowX(), _ball->getShadowY(), _ball->getShadow()->getWidth(), _ball->getShadow()->getHeight());
			_ball->setShadowRect(rc);


		}
		else
		{
			_ball->setX(_player->getX() - _player->_shadow->getWidth() + 20);
			_ball->setY(_player->getY());

			_ball->setShadowX(_ball->getX());
			_ball->setShadowY(_player->_shadow->getCenterY());

			_ball->getShadow()->setCenter(_ball->getShadowX(), _ball->getShadowY());

			_ball->getImage()->setCenter(_ball->getX(), _ball->getY());

			rc = RectMakeCenter(_ball->getX(), _ball->getY(), _ball->getImage()->getWidth(), _ball->getImage()->getHeight());
			_ball->setRect(rc);

			rc = RectMakeCenter(_ball->getShadowX(), _ball->getShadowY(), _ball->getShadow()->getWidth(), _ball->getShadow()->getHeight());
			_ball->setShadowRect(rc);


		}
	}
	if (_ball->isattack)
	{
		_ball->update(_player->isRight);
	}
}

void objectManager::updateBanana()
{
	if (_banana->ishold && !_banana->iseat)
	{
		_player->sethp(_player->gethp() + 1);
		_banana->ishold = false;
		_banana->iseat = true;
	}
}

void objectManager::collsion()
{
	RECT temp;
	
	if (KEYMANAGER->isStayKeyDown('X') && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (!(_ball->ishold)&& IntersectRect(&temp, &_player->getRect(), &_ball->getRect())) {
			if (_ball->getShadowRect().top < _player->_shadow->getCenterY() &&
				_ball->getShadowRect().bottom > _player->_shadow->getCenterY())
			{
				_ball->ishold = true;
			}
		}
		if (!(_banana->ishold)&& IntersectRect(&temp, &_player->getRect(), &_banana->getRect())) {
			if (_banana->getShadowY() < _player->_shadow->getY() &&
				_banana->getShadowY() < _player->_shadow->getY() + _player->_shadow->getHeight())
			{
				_banana->ishold = true;	
			}
		}
	}

	//ball 던진다!
	//if(_ball->isattack){
	//	//Whtie baseball
	//	for (int i = 0; i < _em->getVWb().size(); i++) {
	//		if (_ball->getShadowY() < _em->getVWb()[i]->getRect().bottom &&
	//			_ball->getShadowY() > _em->getVWb()[i]->getRect().top)
	//		{
	//			if (IntersectRect(&temp, &_em->getVWb()[i]->getRect(), &_ball->getRect()))
	//			{
	//				_ball->isattack = false;
	//				_em->getVWb()[i]->isdamage = true;
	//			}
	//		}
	//	}
	//	//bule baseball
	//	for (int i = 0; i < _em->getVBb().size(); i++)
	//	{
	//		
	//		if (_ball->getShadowY() < _em->getVBb()[i]->getRect().bottom &&
	//			_ball->getShadowY() > _em->getVBb()[i]->getRect().top)
	//		{
	//			if (IntersectRect(&temp, &_em->getVBb()[i]->getRect(), &_ball->getRect()))
	//			{
	//				_ball->isattack = false;
	//				//_em->getVBb()[i]->isdamage = true;  isdamage변수추가하면 주석풀어주세용
	//			}
	//		}
	//
	//	}
	//
	//	//Green Baseball
	//	for (int i = 0; i < _em->getVGb().size(); i++)
	//	{
	//		if (_ball->getShadowY() < _em->getVBb()[i]->getRect().bottom &&
	//			_ball->getShadowY() > _em->getVBb()[i]->getRect().top)
	//		{
	//			if (IntersectRect(&temp, &_em->getVBb()[i]->getRect(), &_ball->getRect()))
	//			{
	//				_ball->isattack = false;
	//				//_em->getVBb()[i]->isdamage = true;   isdamage변수추가하면 주석풀어주세용
	//			}
	//		}
	//	
	//	}
	//
	//	//Yello Baseball
	//	for (int i = 0; i < _em->getVYb().size(); i++)
	//	{
	//		if (_ball->getShadowY() < _em->getVYb()[i]->getRect().bottom &&
	//			_ball->getShadowY() > _em->getVYb()[i]->getRect().top)
	//		{
	//			if (IntersectRect(&temp, &_em->getVYb()[i]->getRect(), &_ball->getRect()))
	//			{
	//				_ball->isattack = false;
	//				//_em->getVBb()[i]->isdamage = true;  isdamage변수추가하면 주석풀어주세용
	//			}
	//		}
	//
	//	}
	//}

	if (_player->isattack)
	{
		for (_vitrash = _vtrash.begin(); _vitrash != _vtrash.end(); _vitrash++) {
			if ((*_vitrash)->getShadowY() > _player->_shadow->getY() &&
				(*_vitrash)->getShadowY() < _player->_shadow->getY() + _player->_shadow->getHeight())
			{
				if (IntersectRect(&temp, &_player->_attack_rc, &(*_vitrash)->getRect()))
				{
					(*_vitrash)->presenty = _player->_attack_rc.top;
					if ((*_vitrash)->pasty != (*_vitrash)->presenty)
					{
						(*_vitrash)->pasty = (*_vitrash)->presenty;
						(*_vitrash)->isdamage = true;
					}
				}
			}
		}
	}
	else
		(*_vitrash)->pasty = 0;

}
