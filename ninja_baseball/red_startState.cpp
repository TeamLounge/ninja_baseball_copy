#include "stdafx.h"
#include "red_startState.h"
#include "red_idleState.h"

playerstate * red_startState::handleInput(player * _player)
{
	if (_time > 10)
	{
		return new red_idleState;
	}

	return nullptr;
}

void red_startState::update(player * _player)
{
	if (_index > _player->getImage()->getMaxFrameX())
	{
		_time++;
	}
	
	_count++;

	if (_count % 5 == 0)
	{
		_player->getImage()->setFrameX(_index);
		_index++;
		_count = 0;
	}
	_player->invincibility = true;
}

void red_startState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_set"));
	_player->setImageName("red_set");
	
	_player->invincibility = true;
	//체력 풀로 채움
	_player->sethp(5);
	
	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_time = _count =_index = 0;

	_player->setX(_player->getX());
	_player->setY(_player->getY());

	_player->getImage()->setFrameX(_index);
	_player->getImage()->setFrameY(_index);
}
