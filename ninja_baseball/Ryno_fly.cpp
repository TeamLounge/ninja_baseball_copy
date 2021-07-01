#include "stdafx.h"
#include "Ryno_fly.h"
#include "Ryno_fall.h"
playerstate * Ryno_fly::handleInput(player * player)
{
	if (isend)
	{
		player->isattack = false;
		return new Ryno_fall;
	}
	return nullptr;
}

void Ryno_fly::update(player * player)
{

	//���ٰ�
	if (_index < 2)
	{
		_count++;
		_commandTime++;
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 1) _index = 0;
			//Ŀ�ǵ� �ð��ȿ� ����Ű������ ���! �ٵ� ���� ��Ʈ�� �ȶ���f�� ����..
			if (_commandTime < 50)
			{
				if (KEYMANAGER->isOnceKeyDown('X')&& (player->getY() < _top))
				{
					player->isattack = true;
				}
			}
			//Ŀ�ǵ� �ð��ȿ� ����Ű �ȴ����� ��!
			else if (_commandTime > 50 && !next)
				isend = true;
			_count = 0;

		}
		//�� �ൿ�ȿ� �����ص� õ����� ��� �ö󰡰� õ�� ������ �׸��ڷ� ��Ҿ�� 
		if (player->getY() >= _top)
		{
			if (player->isRight) {
				player->setY(player->getY() - 20);
				player->setX(player->getX() - 2);
			}
			else
			{
				player->setY(player->getY() - 20);
				player->setX(player->getX() + 2);
			}

		}
	}

	//�̰Ŵ� �����ߴٸ� ���ݷ�Ʈ�� ��̴ϴ�
	if (_index<2 && player->isattack)
	{
		player->effect = IMAGEMANAGER->findImage("effect");
		player->effect1 = IMAGEMANAGER->findImage("effect1");
		player->effect2 = IMAGEMANAGER->findImage("effect2");
		player->effect3 = IMAGEMANAGER->findImage("effect3");
		_actiontime++;
		next = true;
		if(player->isRight)
		player->_attack_rc = RectMakeCenter(player->getX() + cosf(0.75)*300, player->getY() + sinf(0.75)*440, 150, 150);
		
		else
			player->_attack_rc = RectMakeCenter(player->getX() + cosf(2.32) * 300, player->getY() + sinf(2.32) * 400, 150, 150);
		//���ݷ�Ʈ�� ������ �ð����� ����  �ð��� ������ ���� �ൿ���� �Ѿ�� �մϴ�. ������ �Ⱦ��͵� �� 0���� �ʱ�ȭ ���ֱ���
		if (_actiontime > 50)
		{
			_index++;
			_actiontime = 0;
			_commandTime = 0;
			_count = 0;
		}
	}

	//�״��� �������κ�
	if (_index == 2)
	{
		if(player->isRight)
			player->_attack_rc = RectMakeCenter(player->getX()+90, player->getY() + (player->getImage()->getFrameHeight() / 2), 80, 50);
		else
			player->_attack_rc = RectMakeCenter(player->getX() - 90, player->getY() + (player->getImage()->getFrameHeight() / 2), 80, 50);

		//����� ī��Ʈ�� �� �ʿ䰡 ������� �ٴڿ� ���������� �����մϴ�
		//������ �Ƹ� ���ݷ�Ʈ�κ��� �� ���鲮�ϴ�.
		if (player->getY()+(player->getImage()->getFrameHeight()/2) < player->_shadow->getY())
		{
			if (player->isRight) 
			{
				player->setX(player->getX() + cosf(0.75) * 30);
				player->setY(player->getY() + sinf(0.75) * 40);
			}
			else
			{
				player->setX(player->getX() + cosf(0.75) * -30);
				player->setY(player->getY() + sinf(0.75) * 40);
			}
		}
		else
		{
			//�ٴ������� �����ܰ��
			_index++;
		}
	}


	//�������ܰ�  
	if (_index == 3)
	{
		player->isattack = false;
		_actiontime++;
		//�������� �ϴ� �׼ǽð����� ���� �߾�� �̴����� ��� �ؾ������𸣰ٳ׿�
		//���Ӱ� falling ���¸� ���� �������� �Ϸ�����
		if(_actiontime < 30)
		{
			if (player->isRight)
			{
				player->setX(player->getX() + 2);
				player->setY(player->getY() - 5);
			}
			else
			{
				player->setX(player->getX() - 2);
				player->setY(player->getY() - 5);
			}
		}
		//�ٴڿ� ������ ��
		else if (player->getY() + (player->getImage()->getFrameHeight() / 2) < player->_shadow->getY())
		{
			if (player->isRight)
			{
				player->setX(player->getX() + 2);
				player->setY(player->getY() + 10);
			}
			else
			{
				player->setX(player->getX() - 2);
				player->setY(player->getY() + 10);
			}
		}
		else
			isend = true;
	}



	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameY(1);
	}


	player->getImage()->setFrameX(_index);

	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
}

void Ryno_fly::enter(player * player)
{
	_count = _index = 0;
	_actiontime = _commandTime =  0;

	next = false;
	player->isattack = false;
	isend = false;
	//�÷��̾��� �̹���,��Ʈ,�׸��� �ʱ�ȭ
	player->setImage(IMAGEMANAGER->findImage("Ryno_fly"));
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX()  - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);

	//������ �ö󰡴��� �׻� �����ϰ� �ϱ�����  xx õ�� ������ ��������ϴ�
	_top = player->_shadow->getY()-350;
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

	player->setImageName("Ryno_fly");
}
