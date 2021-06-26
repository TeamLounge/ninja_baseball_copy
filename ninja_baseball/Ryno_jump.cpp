#include "stdafx.h"
#include "Ryno_jump.h"
#include "player.h"
#include "Ryno_idle.h"
#include "Ryno_fly.h"
playerstate * Ryno_jump::handleInput(player * player)
{
	//�̺κе� ���߿� �ٲ���ҰͰ���..
	if (_jumpPower < -10)
	{
		return new Ryno_idle;
	}   
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&&KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new Ryno_fly;
	}
 	return nullptr;
}

void Ryno_jump::update(player * player)
{
	//���� ī����
	_count++;
	//�����߷�
	player->setY(player->getY() - _jumpPower);
	_jumpPower -= _gravity;

	//�����̱�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setX(player->getX() - 5);
		player->isRight = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + 5);
		player->isRight = true;
	} 
	//zŰ������ ���ݻ���
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		isattack = true;
	}
	//�¿� �����ϱ����ؼ�
	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else if(!player->isRight)
	{
		player->getImage()->setFrameY(1);
	}

	//����Ű�� �������� ���ݻ��·�  ���� ��Ʈ�� ����������
	//�����϶� �÷��̾��� ���ݷ�Ʈ�� ���� �������Դϴ�
	//�������ε����ϋ� ���ݷ�Ʈ�� ���°���
 	if (isattack)
	{
		if (_count % 4 == 0)
		{
			_index++;
			//������Ͱ� ������ �ε��� ���ݷ�Ʈ�� ���κ�
			if (_index >= 4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				_index = 6;
			}
			else if (_index > 5)
			{
				_index = 5;
			}
			//�������
			player->getImage()->setFrameX(_index);
		}
	}

	//�׸��� ��ġ����
	//�׸��ڴ� ���������� x�θ� �����̰� �س����
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	
	
}

void Ryno_jump::enter(player * player)
{

	_count = _index = 0;
	
	_jumpPower = 10.0f;
	_gravity = 0.2f;

	isattack = false;
	
	//�÷��̾��� �̹���,��Ʈ,�׸��� �ʱ�ȭ
	player->setImage(IMAGEMANAGER->findImage("Ryno_jumpAttack"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90 );

	//�¿챸��
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
