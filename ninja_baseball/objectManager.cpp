#include "stdafx.h"
#include "objectManager.h"
#include "player.h"
HRESULT objectManager::init()
{
	setBaseBall();
	return S_OK;
}


void objectManager::release()
{

}

void objectManager::update()
{
	RECT rc;
	collsion();

	if (_ball->ishold)
		{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_ball->ishold = false;
			_ball->isattack = true;
		}
		if (_player->isRight)
		{
			_ball->setX(_player->getX() + _player->_shadow->getWidth()-20);
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

void objectManager::render()
{
	char str[128];
	sprintf_s(str, " 잡혓쏘히잉ajkdjfljekflsjklejklfajdsklfjekl");

	_ball->render();
	if (_ball->ishold)
	{
		TextOut(getMemDC(), _ball->getX()-10, _ball->getY()-10,str, strlen(str));
	}
}

void objectManager::setBaseBall()
{
	_ball = new baseball;
	_ball->init(PointMake(WINSIZEX/2, WINSIZEY/2));
}

void objectManager::setTrahCan()
{

}

void objectManager::setBanana()
{


}

void objectManager::collsion()
{
	RECT temp;
	
	if (KEYMANAGER->isStayKeyDown('X') && KEYMANAGER->isStayKeyDown(VK_DOWN) && !(_ball->ishold))
	{
		if (_ball->getShadowRect().top<_player->_shadow->getCenterY() &&
			_ball->getShadowRect().bottom>_player->_shadow->getCenterY())
		{
			if (IntersectRect(&temp, &_player->getRect(), &_ball->getRect()))
			{
				_ball->ishold = true;
			}
		}
	}

	//ball 던진다!
	if(_ball->isattack){
		//Whtie baseball
		for (int i = 0; i < _em->getVWb().size(); i++) {
			if (_ball->getShadowY() < _em->getVWb()[i]->getRect().bottom &&
				_ball->getShadowY() > _em->getVWb()[i]->getRect().top)
			{
				if (IntersectRect(&temp, &_em->getVWb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					_em->getVWb()[i]->isdamage = true;
				}
			}
		}
		//bule baseball
		for (int i = 0; i < _em->getVBb().size(); i++)
		{
			
			if (_ball->getShadowY() < _em->getVBb()[i]->getRect().bottom &&
				_ball->getShadowY() > _em->getVBb()[i]->getRect().top)
			{
				if (IntersectRect(&temp, &_em->getVBb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					//_em->getVBb()[i]->isdamage = true;  isdamage변수추가하면 주석풀어주세용
				}
			}

		}

		//Green Baseball
		for (int i = 0; i < _em->getVGb().size(); i++)
		{
			if (_ball->getShadowY() < _em->getVBb()[i]->getRect().bottom &&
				_ball->getShadowY() > _em->getVBb()[i]->getRect().top)
			{
				if (IntersectRect(&temp, &_em->getVBb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					//_em->getVBb()[i]->isdamage = true;   isdamage변수추가하면 주석풀어주세용
				}
			}
		
		}

		//Yello Baseball
		for (int i = 0; i < _em->getVYb().size(); i++)
		{
			if (_ball->getShadowY() < _em->getVYb()[i]->getRect().bottom &&
				_ball->getShadowY() > _em->getVYb()[i]->getRect().top)
			{
				if (IntersectRect(&temp, &_em->getVYb()[i]->getRect(), &_ball->getRect()))
				{
					_ball->isattack = false;
					//_em->getVBb()[i]->isdamage = true;  isdamage변수추가하면 주석풀어주세용
				}
			}

		}
	}


}
