#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
//�̰� �������� 

HRESULT enemyManager::init()
{
	setWB();

	

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	updateWB();
	playerLocation();

	collision();	//���� vs wbŸ�ݹ�����Ʈ
}

void enemyManager::render()
{
	renderWB();
}


void enemyManager::setWB()
{
	for (int i = 0; i < 3; i++)
	{
		whiteBaseball* _wb = new whiteBaseball;	//�����Ҵ� ���ְ�
		_wb->init(PointMake(WINSIZEX + i * 220, -50 + i * 200));			//�̴����� ��ġ ����ְ�
		_vWb.push_back(_wb);					//��ġ ����� �ָ� ���Ϳ� ����

	}
	//�� ����ġ ���� �� �������� for�� �ۿ� ���� ���ִ� �͵� ���
	//whiteBaseball* _wb1 = new whiteBaseball;	//�����Ҵ� ���ְ�
	//_wb1->init(PointMake(500, 500));			//�̴����� ��ġ ����ְ�
	//_vWb.push_back(_wb1);					//��ġ ����� �ָ� ���Ϳ� ����
}

void enemyManager::updateWB()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->update();		//�� ������Ʈ�� ��
	}
}

void enemyManager::renderWB()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->render();		//�� ������ ��
	}
}

void enemyManager::playerLocation()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if (!(*_viWb)->isJump)	//���� = true
		{
			//���ʹ̰� �÷��̾��� ������?
			if (_red->getRect().right > (*_viWb)->getRect().right)
			{
				(*_viWb)->setIsRight(true);
			}
			//���ʹ̰� �÷��̾��� ����?
			if (_red->getRect().left < (*_viWb)->getRect().left)
			{
				(*_viWb)->setIsRight(false);
			}

			//���ʹ̰� �÷��̾��� ��?
			if (_red->getRect().top > (*_viWb)->getRect().top)
			{
				(*_viWb)->setIsDown(false);
			}
			//���ʹ̰� �÷��̾��� �Ʒ�?
			if (_red->getRect().bottom > (*_viWb)->getRect().bottom)
			{
				(*_viWb)->setIsDown(true);
			}
		}
	}
}

void enemyManager::collision()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_red->getRect(), &(*_viWb)->getAttackRect()))
		{
			(*_viWb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viWb)->setIsCollisionAttack(false);
		}

	}
}

