#include "stdafx.h"
#include "objectManager.h"
#include "player.h"
HRESULT objectManager::init()
{
	setTrahCan();
	setBaseBall();
	setBanana();
	setCereal();
	catchtime = 0;
	return S_OK;
}


void objectManager::release()
{

}

void objectManager::update()
{
	for (_vitrash = _vtrash.begin(); _vitrash != _vtrash.end();)
	{
		(*_vitrash)->update();
		if ((*_vitrash)->iscrush && (*_vitrash)->peice1->getCenterY() > (*_vitrash)->getShadowY())
		{
			_vitrash = _vtrash.erase(_vitrash);
		}
		else _vitrash++;
	}
	collsion();
	updateBall();
	updateBanana();
	updateCereal();
}


void objectManager::render()
{

	
	for (_vitrash = _vtrash.begin(); _vitrash != _vtrash.end(); _vitrash++)
	{
		(*_vitrash)->render();
		if ((*_vitrash)->_present == 0 && (*_vitrash)->iscrush && !(_ball->isrend))
		{
			_ball->isrend = true;
			_ball->isappear = true;
			_ball->addrendmanager();
			(*_vitrash)->deleteRender(0);
		}
		if ((*_vitrash)->_present == 1 && (*_vitrash)->iscrush && !(_banana->isrend))
		{
			_banana->isrend = true;
			_banana->isappear = true;
			_banana->addrendmanager();
			(*_vitrash)->deleteRender(0);
		}
		if ((*_vitrash)->_present == 2 && (*_vitrash)->iscrush && !(_cereal->isrend))
		{
			_cereal->isrend = true;
			_cereal->isappear = true;
			_cereal->addrendmanager();
			(*_vitrash)->deleteRender(0);
		}
	}
}

void objectManager::goldrender()
{
	if (_em->getBoss()->_isDeathState && !(_goldbat->isappear))
	{
		_goldbat->isappear = true;
		_goldbat->addrendmanager();
	}
}

void objectManager::setBaseBall()
{
	_ball = new baseball;
	_ball->init(PointMake((int)_vtrash[0]->getX(), (int)_vtrash[0]->getShadowRect().top));
}

void objectManager::setTrahCan()
{
	for (int i = 0; i < 3; i++)
	{
		trashCan* _trashCan = new trashCan;
		if (i == 0) 
		{
			_trashCan->init(PointMake(794, 408), i);
		}
		if (i == 1)
		{
			_trashCan->init(PointMake(1875, 408), i);
		}
		if (i == 2)
		{
			_trashCan->init(PointMake(3239, 408), i);
		}
		_vtrash.push_back(_trashCan);

	}
}

void objectManager::setBanana()
{
	_banana = new banana;
	_banana->init(PointMake((int)_vtrash[1]->getX(), (int)_vtrash[1]->getShadowRect().top-30));

}

void objectManager::setCereal()
{
	_cereal = new cereal;
	_cereal->init(PointMake((int)_vtrash[2]->getX(), (int)_vtrash[2]->getShadowRect().top - 30));
}

void objectManager::setgoldbat(float x , float y)
{
	_goldbat = new goldbat;
	_goldbat->init(PointMake(1520, 478));
}

void objectManager::updateBall()
{
	RECT rc;
	if (_ball->ishold)
	{
		catchtime++;
		if (catchtime>10 &&KEYMANAGER->isOnceKeyDown('X'))
		{
			_ball->ishold = false;
			_ball->isattack = true;
			_ball->isfire = true;
			catchtime = 0;
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
		if(_player->gethp()!=5)
		_player->sethp(_player->gethp() + 1);
		_banana->ishold = false;
		_banana->iseat = true;
		_banana->isappear = false;
		_banana->deleteRendermanager();
	}
}

void objectManager::updateCereal()
{
	if (_cereal->ishold && !_cereal->iseat)
	{
		if (_player->gethp() != 5)
			_player->sethp(_player->gethp() + 1);
		_cereal->ishold = false;
		_cereal->iseat = true;
		_cereal->isappear = false;
		_cereal->deleteRendermanager();
	}
}

void objectManager::updategoldbat()
{
	RECT rc;
	if (!(_goldbat->isappear))
	{
		_goldbat->setX(_em->getBoss()->getCenterX());
		_goldbat->setY(_em->getBoss()->getCenterY());
		_goldbat->setShadowX(_em->getBoss()->getCenterX());
		_goldbat->setShadowY(_em->getBoss()->getCenterY() + 214);
	}
	if (_goldbat->isappear)
	{
		if (!_goldbat->ishold)
		{
			goldbatCollsion();
			_goldbat->update();
		}
		else
		{
			if (_player->isRight)
			{
				_goldbat->setX(_player->getX() + _player->_shadow->getWidth() - 20);
				_goldbat->setY(_player->getY());

				_goldbat->setShadowX(_goldbat->getX());
				_goldbat->setShadowY(_player->_shadow->getCenterY());

				_goldbat->getShadow()->setCenter(_goldbat->getShadowX(), _goldbat->getShadowY());

				_goldbat->getImage()->setCenter(_goldbat->getX(), _goldbat->getY());

				rc = RectMakeCenter(_goldbat->getX(), _goldbat->getY(), _goldbat->getImage()->getWidth(), _goldbat->getImage()->getHeight());
				_goldbat->setRect(rc);

				rc = RectMakeCenter(_goldbat->getShadowX(), _goldbat->getShadowY(), _goldbat->getShadow()->getWidth(), _goldbat->getShadow()->getHeight());
				_goldbat->setShadowRect(rc);


			}
			else
			{
				_goldbat->setX(_player->getX() - _player->_shadow->getWidth() + 20);
				_goldbat->setY(_player->getY());

				_goldbat->setShadowX(_goldbat->getX());
				_goldbat->setShadowY(_player->_shadow->getCenterY());
				
				_goldbat->getShadow()->setCenter(_goldbat->getShadowX(), _goldbat->getShadowY());

				_goldbat->getImage()->setCenter(_goldbat->getX(), _goldbat->getY());

				rc = RectMakeCenter(_goldbat->getX(), _goldbat->getY(), _goldbat->getImage()->getWidth(), _goldbat->getImage()->getHeight());
				_goldbat->setRect(rc);

				rc = RectMakeCenter(_goldbat->getShadowX(), _goldbat->getShadowY(), _goldbat->getShadow()->getWidth(), _goldbat->getShadow()->getHeight());
				_goldbat->setShadowRect(rc);


			}
		}
	}
}

void objectManager::collsion()
{
	RECT temp;
	
	if (KEYMANAGER->isStayKeyDown('X') && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_ball->isappear&&!(_ball->ishold)&& IntersectRect(&temp, &_player->getRect(), &_ball->getRect())) {
			if ( _ball->getShadowY() > _player->_shadow->getY() &&
				_ball->getShadowY() < _player->_shadow->getY() + _player->_shadow->getHeight());
			{
				_ball->ishold = true;
			}
		}
		if (_banana->isappear &&!(_banana->ishold)&& IntersectRect(&temp, &_player->getRect(), &_banana->getRect())) {
			if (_banana->getShadowY() > _player->_shadow->getY() &&
				_banana->getShadowY() < _player->_shadow->getY() + _player->_shadow->getHeight())
			{
				_banana->ishold = true;	
			}
		}
		if (_cereal->isappear &&!(_cereal->ishold) && IntersectRect(&temp, &_player->getRect(), &_cereal->getRect())) {
			if (_cereal->getShadowY() > _player->_shadow->getY() &&
				_cereal->getShadowY() < _player->_shadow->getY() + _player->_shadow->getHeight())
			{
				_cereal->ishold = true;
			}
		}
	}

	//ball ??????!
	if(_ball->isappear && _ball->isattack){
		//Whtie baseball
		for (int i = 0; i < _em->getVWb().size(); i++) {
			if (_ball->getShadowY() < _em->getVWb()[i]->_wbShadow.rc.bottom &&
				_ball->getShadowY() > _em->getVWb()[i]->_wbShadow.rc.top)
			{
				if (IntersectRect(&temp, &_em->getVWb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					_ball->isappear = false;
					_ball->deleteRendermanager();
					_em->getVWb()[i]->isCollisionDamaged = true;
				}
			}
		}
		//bule baseball
		for (int i = 0; i < _em->getVBb().size(); i++)
		{
			
			if (_ball->getShadowY() < _em->getVBb()[i]->_bbShadow.rc.bottom &&
				_ball->getShadowY() > _em->getVBb()[i]->_bbShadow.rc.top)
			{
				if (IntersectRect(&temp, &_em->getVBb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					_ball->isappear = false;
					_ball->deleteRendermanager();
					_em->getVBb()[i]->isCollisionDamaged = true;
				}
			}
	
		}
	
		//Green Baseball
		for (int i = 0; i < _em->getVGb().size(); i++)
		{
			if (_ball->getShadowY() < _em->getVGb()[i]->_gbShadow.rc.bottom &&
				_ball->getShadowY() > _em->getVGb()[i]->_gbShadow.rc.top)
			{
				if (IntersectRect(&temp, &_em->getVGb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					_ball->isappear = false;
					_ball->deleteRendermanager();
					_em->getVYb()[i]->isCollisionDamaged = true;
				}
			}
		
		}
	
		//Yello Baseball
		for (int i = 0; i < _em->getVYb().size(); i++)
		{
			if (_ball->getShadowY() < _em->getVYb()[i]->_ybShadow.rc.bottom &&
				_ball->getShadowY() > _em->getVYb()[i]->_ybShadow.rc.top)
			{
				if (IntersectRect(&temp, &_em->getVYb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					_ball->isappear = false;
					_ball->deleteRendermanager();
					_em->getVYb()[i]->isCollisionDamaged = true;
				}
			}
	
		}
	}

	
	for (_vitrash = _vtrash.begin(); _vitrash != _vtrash.end(); _vitrash++) {
		if ((*_vitrash)->getShadowY() > _player->getShadowY()-_player->_shadow->getHeight()/2 &&
			(*_vitrash)->getShadowY() < _player->getShadowY() + _player->_shadow->getHeight() / 2)
		{
			if (_player->isattack&&IntersectRect(&temp, &_player->_attack_rc, &(*_vitrash)->getRect()))
			{
				(*_vitrash)->presenty = _player->_attack_rc.top;
				if ((*_vitrash)->pasty != (*_vitrash)->presenty)
				{
					(*_vitrash)->pasty = (*_vitrash)->presenty;
					(*_vitrash)->isdamage = true;
				}
			}
			else (*_vitrash)->pasty = 0;
		}
	}

}

void objectManager::goldbatCollsion()
{
	RECT temp;

	if (KEYMANAGER->isStayKeyDown('X') && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_goldbat->isappear && !(_goldbat->ishold) && IntersectRect(&temp, &_player->getRect(), &_goldbat->getRect())) {
			if (_goldbat->getShadowY() > _player->_shadow->getY() &&
				_goldbat->getShadowY() < _player->_shadow->getY() + _player->_shadow->getHeight());
			{
				_goldbat->ishold = true;
			}
		}
	}
}
