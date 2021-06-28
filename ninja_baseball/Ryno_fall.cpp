#include "stdafx.h"
#include "Ryno_fall.h"
#include "Ryno_idle.h"
playerstate * Ryno_fall::handleInput(player * player)
{
	if (player->getY() + (player->getImage()->getFrameHeight() / 2) > player->_shadow->getY())
	{
		player->isattack = false;
		return new Ryno_idle;
	}
	return nullptr;
}

void Ryno_fall::update(player * player)
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
		player->isattack = true;
	}
	//�¿� �����ϱ����ؼ�
	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else if (!player->isRight)
	{
		player->getImage()->setFrameY(1);
	}

	//����Ű�� �������� ���ݻ��·�  ���� ��Ʈ�� ����������
	//�����϶� �÷��̾��� ���ݷ�Ʈ�� ���� �������Դϴ�
	//�������ε����ϋ� ���ݷ�Ʈ�� ���°���
	if (player->isattack)
	{
		if (player->jumpindex < 4)
			player->_attack_rc = RectMakeCenter(player->getX() , player->getY(), 50, 50);
		if (_count % 4 == 0)
		{
			player->jumpindex++;
			//������Ͱ� ������ �ε��� ���ݷ�Ʈ�� ���κ�
			if (player->jumpindex >= 4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
				player->jumpindex = 6;
			}
			else if (player->jumpindex > 5)
			{
				player->_attack_rc = RectMakeCenter(player->getX(), player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				player->jumpindex = 5;
			}
			//�������
			if (player->jumpindex == 5) {
				if (player->isRight)
				{
					player->_attack_rc = RectMakeCenter(player->getX() + 30, player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				}
				else
				{
					player->_attack_rc = RectMakeCenter(player->getX() - 30, player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				}
			}
			if (player->jumpindex == 6) {
				if (player->isRight)
				{
					player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY() + 80, 50, 50);
				}
				else
				{
					player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY() + 80, 50, 50);
				}
			}
		}
	}
	player->getImage()->setFrameX(player->jumpindex);
	//�׸��� ��ġ����
	//�׸��ڴ� ���������� x�θ� �����̰� �س����
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

}

void Ryno_fall::enter(player * player)
{
	_count = _index = 0;

	_jumpPower = 0.0f;
	_gravity = 0.2f;
	
	//�÷��̾��� �̹���,��Ʈ,�׸��� �ʱ�ȭ
	player->setImage(IMAGEMANAGER->findImage("Ryno_jumpAttack"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

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
