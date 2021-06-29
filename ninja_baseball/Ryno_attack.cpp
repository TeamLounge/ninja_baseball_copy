#include "stdafx.h"
#include "Ryno_attack.h"
#include "Ryno_idle.h"
#include "Ryno_frontCombo.h"
#include "player.h"
playerstate * Ryno_attack::handleInput(player * player)
{
	
	if (isend)
	{
		player->isattack = false;
		return new Ryno_idle;
	}

	if (isfront)
	{
		player->isattack = false;
		return new Ryno_frontCombo;
	}
	return nullptr;
}

void Ryno_attack::update(player * player)
{
	//ó�������Ҷ� �����ε����� 0�̰���?
	if (_index < 3) {
		//ī���͸� ������ �������ε����� �����б� �����ӱ��� ������ŵ�ϴ�
		_count++;
		if (_count % 3 == 0)
		{
			//�ε����� ó���� 0~2�������÷���
			if(_index<2) _index++;

			//�ε����� 2�϶� �������ݺб⸦ �����ؾߵǿ�
			//���� ���� _count������ ���������ε�, �б⸶�� �ð����� ���� ������� ���ٰ� �򰥸��� �� �־��.
			//��� �̺κ��� �ð�üũ�� ������ ���� ���� �� ������ 
			//if(_index==2) �϶� �ð�üũ����++ �������� �ð�üũ�� �ϼŵ��˴ϴ�.
		
			if (_index==2)
			{
				player->isattack = true;
				if (player->isRight) {
					player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY()-40, 50, 80);
				}
				else
					player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY()-40, 50, 80);
			}
			//���� �ε����� 2��
			if (_count < 30) {
				//zŰ�������鼭 ��Ű�� ������ ���ο� ������������ ���ϴ�.
				//�̰͵� ����Ŭ������ ���� �����ϴ°� ���Űǰ��� �̷ο��� ����  ���� ���޴µ�.. �̰� �����Ϸ�����
				if ((KEYMANAGER->isStayKeyDown(VK_RIGHT)||(KEYMANAGER->isStayKeyDown(VK_LEFT))) && KEYMANAGER->isOnceKeyDown('Z'))
				{

					isfront = true;
					//���ο� ���������� �ֱ����� �̹����� �����ְ� �ε���, ī���͵� ó������ �ǵ����ϴ�.
				
				}
				//�׳� zŰ�� ������ �⺻���ݸ�
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
					_count = 0;
					player->isattack = false;
				}
			}
			//������ �ð��� �����ٸ� ������ ���������� 
			else
				isend = true;
		}
	}
	//ó�����ݺκп��� �״�� �⺻�����������ߴٸ�
	//���� �⺻���� �б�� �ɴϴ�.
	//�� �б⿡ Ű�� �� �Է��ϸ� ��� ������ �����ؿ�.
	if (_index == 3)
	{
		_count++;
		player->isattack = true;
		if (player->isRight) {
			player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		}
		else
			player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		//���ݵ� ������ī��Ʈ�� �ð����� ��µ� ������ ���� ��Ȳ���� �����ӷ����� �ȵ������� �Ǽ�..
		if (_count < 30)
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_index++;
				player->isattack = false;
				//���� ������ī���͸� �ð����� ���� ������ �׻� ������ī���ʹ� 0���� �ʱ�ȭ
				_count = 0;
			}
		}
		//�ð��� ������ �������
		else
			isend = true;
	}

	//������ �б� 
	if (_index > 3)
	{
		//������ ī��Ʈ
		_count++;
		if (_index == 6) player->isattack = true;
		if (player->isRight) {
			player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		}
		else
			player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		if (_count % 8 == 0)
		{
			_index++;
			//��� �����ٰ� ���������� �ٱ����� �ε����� ������ ���� ��
			if (_index > 6)
				isend = true;
		}
	}

	
	player->getImage()->setFrameX(_index);
}

void Ryno_attack::enter(player * player)
{
	_count = _index = 0;
	//�� bool������ �����̳��������� üũ�մϴ�.
	isend = false;
	isfront = false;
	player->setImage(IMAGEMANAGER->findImage("Ryno_attack"));
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);

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