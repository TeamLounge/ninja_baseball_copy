#include "stdafx.h"
#include "red_throw.h"
#include "red_idleState.h"

playerstate * red_throw::handleInput(player * _player)
{
	return nullptr;
}

void red_throw::update(player * _player)
{
}

void red_throw::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_throw"));
}
