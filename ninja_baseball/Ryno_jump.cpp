#include "stdafx.h"
#include "Ryno_jump.h"
#include "player.h"
#include "Ryno_fall.h"
#include "Ryno_damage.h"
#include "Ryno_fly.h"
playerstate * Ryno_jump::handleInput(player * player)
{
	//�̺κе� ���߿� �ٲ���ҰͰ���..
	if (_jumpPower < 0 && player->getY() + (player->getImage()->getFrameHeight() / 2) > player->_shadow->getY())
	{
		player->_isGreenJumpAttack = false;
		return new Ryno_fall;
	}   
	if (KEYMANAGER->isOnceKeyDown('X')&&KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->_isGreenJumpAttack = false;
		return new Ryno_fly;
	}
	if (player->isdamage)
	{
		return new Ryno_damage;
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
		player->setX(player->getX() - 7);
		player->isRight = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + 7);
		player->isRight = true;
	} 
	//zŰ������ ���ݻ���
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		player->isattack = true;
		player->_isGreenJumpAttack = true;
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
 	if (player->isattack)
	{
		if (_count % 3 == 0)
		{
			_index++;
			//������Ͱ� ������ �ε��� ���ݷ�Ʈ�� ���κ�
			if (_index >= 4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
				_index = 6;
			}
			else if (_index > 5)
			{
				player->_attack_rc = RectMakeCenter(player->getX(), player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				_index = 5;
			}
			//�������
			if (_index < 4)
				player->_attack_rc = RectMakeCenter(player->getX(), player->getY(), 50, 50);
			if (_index == 5) {
				if (player->isRight)
				{
					player->_attack_rc = RectMakeCenter(player->getX() + 30, player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				}
				else
				{
					player->_attack_rc = RectMakeCenter(player->getX() - 30, player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				}
			}
			if (_index == 6) {
				if (player->isRight)
				{
					player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY()+80, 50, 50);
				}
				else
				{
					player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY()+80, 50, 50);
				}
			}
		}
	}
	player->getImage()->setFrameX(_index);
	//�׸��� ��ġ����
	//�׸��ڴ� ���������� x�θ� �����̰� �س����
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	
}

void Ryno_jump::enter(player * player)
{

	_count = _index = 0;
	
	_jumpPower = 10.0f;
	_gravity = 0.25f;

	player->isattack = false;
	//�÷��̾��� �̹���,��Ʈ,�׸��� �ʱ�ȭ
	player->setImage(IMAGEMANAGER->findImage("Ryno_jumpAttack"));
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90 );

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);

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

	player->setImageName("Ryno_jumpAttack");
}
