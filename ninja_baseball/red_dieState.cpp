#include "stdafx.h"
#include "red_dieState.h"

playerstate * red_dieState::handleInput(player * _player)
{
	return nullptr;
}

void red_dieState::update(player * _player)
{
	_time++;
	
	if (_rotation < 7)
	{
		_count++;

		if (_count % 6 == 0)
		{
			if (_player->isRight == true)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(0);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_rotation++;
					_index = 0;
				}
			}
			if (_player->isRight == false)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(1);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_rotation++;
					_index = 0;
				}
			}

			_count = 0;
		}
	}
	
	else // 4�� ������ �÷��̾ ������ �̹���
	{
		_player->setImage(IMAGEMANAGER->findImage("red_die"));
		_player->setImageName("red_die");

		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(0);
			_player->getImage()->setFrameY(0);
		}
		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(0);
			_player->getImage()->setFrameY(1);
		}
	}
	
	if (!_isLie)
	{
		_jumpPower -= _gravity;
		_player->setY(_player->getY() - _jumpPower);

		if (_player->isRight == true)
		{
			_player->setX(_player->getX() - 3);
		}
		if (_player->isRight == false)
		{
			_player->setX(_player->getX() + 3);
		}
	}
	
	if (_time > 125) //�ϴ� �����ð��� ������ ���»��·� ����
	{
		_isLie = true;
	}

	//�׸��� ��ġ
	if (_player->isRight == true)
	{
		/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5);
		_player->_shadow->setY(_player->getY() + 90);*/
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		/*_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);*/
	}
	if (_player->isRight == false)
	{
		/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
		_player->_shadow->setY(_player->getY() + 90);*/
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		/*_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);*/
	}
}

void red_dieState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_damage3"));
	_player->setImageName("red_damage3");

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = _time = 0;
	_rotation = 0;
	_jumpPower = 12.5f;
	_gravity = 0.2f;
	_isLie = false; //�ٴڿ� ��Ҵ��� Ȯ��
	
	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(1);
	}
}
