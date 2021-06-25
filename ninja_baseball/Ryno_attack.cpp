#include "stdafx.h"
#include "Ryno_attack.h"
#include "Ryno_idle.h"
#include "player.h"
playerstate * Ryno_attack::handleInput(player * player)
{
	
	if (isend)
	{
		return new Ryno_idle;
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
			
			//���� �ε����� 2��
			if (_count < 30) {
				//zŰ�������鼭 ��Ű�� ������ ���ο� ������������ ���ϴ�.
				//�̰͵� ����Ŭ������ ���� �����ϴ°� ���Űǰ��� �̷ο��� ����  ���� ���޴µ�.. �̰� �����Ϸ�����
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('Z'))
				{
					//���ο� ���������� �ֱ����� �̹����� �����ְ� �ε���, ī���͵� ó������ �ǵ����ϴ�.
					player->setImage(IMAGEMANAGER->findImage("Ryno_attack_front"));
					_index = 0;
					_count = 0;
				}
				//�׳� zŰ�� ������ �⺻���ݸ�
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
					_count = 0;
				}
			}
			//������ �ð��� �����ٸ� ������ ���������� 
			else
				isend = true;
		}
	}

	//�Ʊ� ���ߴ� ���ο� �������ϻ������� üũ�ϴ°ſ���
	//���� if������ó�� "���� �̹����� �� �̹����ΰ�?" �� �Ǵ��󱸿�
	//�� ���ݺκ��� ���� �̿��Դϴ�.
	if(player->getImage() == IMAGEMANAGER->findImage("Ryno_attack_front"))
	{
		//�׷��� ������ī���ͽ���
		_count++;
		if (_count%5==0) {

			//���������� �ε����� 0~4������������
			if (_index < 5) _index++;
			//���Ⱑ �ε��� 5�϶� �����ϴ� �ð��Դϴ�.
			//�̋��� ������ ī��Ʈ�� �ð����� �����ϴ�..
			if (_count < 30) {
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
				}
			}
			//�����ߴٸ� ������ ��� �̾���ϴ�.
			if (_index >= 6)
			{
				_index++;
				//�ε����� �������ӿ� �Ѿ�� ���ֹ����� 
				if (_index > 7)
					isend = true;
			}
		}

	}

	//ó�����ݺκп��� �״�� �⺻�����������ߴٸ�
	//���� �⺻���� �б�� �ɴϴ�.
	//�� �б⿡ Ű�� �� �Է��ϸ� ��� ������ �����ؿ�.
	if (_index == 3)
	{
		_count++;
		//���ݵ� ������ī��Ʈ�� �ð����� ��µ� ������ ���� ��Ȳ���� �����ӷ����� �ȵ������� �Ǽ�..
		if (_count < 30)
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_index++;
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
		if (_count % 5 == 0) 
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
	RECT rc;
	_count = _index = 0;
	//�� bool������ �����̳��������� üũ�մϴ�.
	isend = false;

	player->setImage(IMAGEMANAGER->findImage("Ryno_attack"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);

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