#include "stdafx.h"
#include "Ryno_frontCombo.h"
#include "Ryno_idle.h"
#include "player.h"
playerstate * Ryno_frontCombo::handleInput(player * player)
{
	if (isend)
	{
		return new Ryno_idle;
	}

	return nullptr;
}

void Ryno_frontCombo::update(player * player)
{

	if (_index < 5) {
		
		_count++;
		if (_count % 5 == 0) {
			//���������� �ε����� 0~4������������
			if (_index < 4) _index++;
			//���Ⱑ �ε��� 5�϶� �����ϴ� �ð��Դϴ�.
			//�̋��� ������ ī��Ʈ�� �ð����� �����ϴ�..
			if (_count < 50) {
				if (_index==4 && KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
					_count = 0;
				}
			}
			else isend = true;
			//�����ߴٸ� ������ ��� �̾���ϴ�.
		}
	}
	if (_index == 5)
	{
		_count++;
		if (_count %  12== 0) {
			_index++;
			//�ε����� �������ӿ� �Ѿ�� ���ֹ����� 
			_count = 0;
		}
	}
	//�ε����� �������ӿ� �Ѿ�� ���ֹ����� 
	if (_index >= 6)
	{
		_count++;
		if (_count % 15 == 0)
		{
			_index++;
		}
		if(player->isRight) player->setX(player->getX() + 3);
		else player->setX(player->getX() - 3);
		if (_index > 7)
		isend = true;

	}

	player->getImage()->setFrameX(_index);
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
}

void Ryno_frontCombo::enter(player * player)
{

	_count = _index = 0;
	//�� bool������ �����̳��������� üũ�մϴ�.
	isend = false;

	player->setImage(IMAGEMANAGER->findImage("Ryno_attack_front"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
	//����player->setY�ض�
	player->setY(player->_shadow->getY() - 120);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 120);

	if (player->isRight)
	{
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);
	}
}
