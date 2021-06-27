#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "time.h"

HRESULT enemyManager::init()
{
	setBaseball();
	setCard();
	

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	updateBaseball();
	playerLocation();

	baseballCollision();	//�÷��̾� vs wbŸ�ݹ�����Ʈ

	updateCard();
	WhereIsCard();	
}

void enemyManager::render()
{

	renderBaseball();
	renderCard();
}


void enemyManager::setBaseball()
{
	//whiteBaseball
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

	//yellowBaseball
	for (int i = 0; i < 2; i++)
	{
		yellowBaseball* _yb = new yellowBaseball;
		_yb->init(PointMake(500 + i * 180, -50 + i * 160));		//x��ǥ �����ϰ� ���� ����!!!!! ���ĺ��δ�!! 0���� ����δ�!!!
		_vYb.push_back(_yb);
	}
	//greenBaseball
	for (int i = 0; i < 2; i++)
	{
		greenBaseball* _gb = new greenBaseball;
		_gb->init(PointMake(400 + i * 140, -50 + i * 120));
		_vGb.push_back(_gb);					

	}
	//blueBaseball
	for (int i = 0; i < 2; i++)
	{
		blueBaseball* _bb = new blueBaseball;
		_bb->init(PointMake(300 + i * 100, -50 + i * 80));
		_vBb.push_back(_bb);

	}
}

void enemyManager::updateBaseball()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->update();		//�� ������Ʈ�� ��
	}
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		(*_viYb)->update();
	}
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		(*_viGb)->update();
	}
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		(*_viBb)->update();
	}

}

void enemyManager::renderBaseball()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->render();		//�� ������ ��
	}
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		(*_viYb)->render();
	}
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		(*_viGb)->render();
	}
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		(*_viBb)->render();
	}
}

void enemyManager::playerLocation()
{
	//white
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if (!(*_viWb)->isJump)	//���� = true
		{
			//���ʹ̰� �÷��̾��� ������?
			if (_player->getX() > (*_viWb)->getCenterX())
			{
				(*_viWb)->setIsRight(true);
			}
			//���ʹ̰� �÷��̾��� ����?
			if (_player->getX() < (*_viWb)->getCenterX())
			{
				(*_viWb)->setIsRight(false);
			}
			//���ʹ̰� �÷��̾��� ��?
			if (_player->getY() > (*_viWb)->getCenterY())
			{
				(*_viWb)->setIsDown(true);
			}
			//���ʹ̰� �÷��̾��� �Ʒ�?
			if (_player->getY() < (*_viWb)->getCenterY())
			{
				(*_viWb)->setIsDown(false);
			}
		}
		//Y��������
		if ((*_viWb)->getCenterY() < _player->getY() + 3 && (*_viWb)->getCenterY() > _player->getY() - 3)
		{
			(*_viWb)->setIsYOverlap(true);
		}
		if (!((*_viWb)->getCenterY() < _player->getY() + 3 && (*_viWb)->getCenterY() > _player->getY() - 3))
		{
			(*_viWb)->setIsYOverlap(false);
		}
		//X��������
		if ((*_viWb)->getCenterX() < _player->getX() + 3 && (*_viWb)->getCenterX() > _player->getX() - 3)
		{
			(*_viWb)->setIsXOverlap(true);
		}
		if (!((*_viWb)->getCenterX() < _player->getX() + 3 && (*_viWb)->getCenterX() > _player->getX() - 3))
		{
			(*_viWb)->setIsXOverlap(false);
		}

	}
	//yellow
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		//���ʹ̰� �÷��̾��� ������?
		if (_player->getX() > (*_viYb)->getCenterX())
		{
			(*_viYb)->setIsRight(true);
		}
		//���ʹ̰� �÷��̾��� ����?
		if (_player->getX() < (*_viYb)->getCenterX())
		{
			(*_viYb)->setIsRight(false);
		}
		//���ʹ̰� �÷��̾��� ��?
		if (_player->getY() > (*_viYb)->getCenterY())
		{
			(*_viYb)->setIsDown(true);
		}
		//���ʹ̰� �÷��̾��� �Ʒ�?
		if (_player->getY() < (*_viYb)->getCenterY())
		{
			(*_viYb)->setIsDown(false);
		}
		//Y��������
		if ((*_viYb)->getCenterY() < _player->getY() + 3 && (*_viYb)->getCenterY() > _player->getY() - 3)
		{
			(*_viYb)->setIsYOverlap(true);
		}
		if (!((*_viYb)->getCenterY() < _player->getY() + 3 && (*_viYb)->getCenterY() > _player->getY() - 3))
		{
			(*_viYb)->setIsYOverlap(false);
		}
		//X��������
		if ((*_viYb)->getCenterX() < _player->getX() + 3 && (*_viYb)->getCenterX() > _player->getX() - 3)
		{
			(*_viYb)->setIsXOverlap(true);
		}
		if (!((*_viYb)->getCenterX() < _player->getX() + 3 && (*_viYb)->getCenterX() > _player->getX() - 3))
		{
			(*_viYb)->setIsXOverlap(false);
		}
	}
	//green
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		//���ʹ̰� �÷��̾��� ������?
		if (_player->getX() > (*_viGb)->getCenterX())
		{
			(*_viGb)->setIsRight(true);
		}
		//���ʹ̰� �÷��̾��� ����?
		if (_player->getX() < (*_viGb)->getCenterX())
		{
			(*_viGb)->setIsRight(false);
		}
		//���ʹ̰� �÷��̾��� ��?
		if (_player->getY() > (*_viGb)->getCenterY())
		{
			(*_viGb)->setIsDown(true);
		}
		//���ʹ̰� �÷��̾��� �Ʒ�?
		if (_player->getY() < (*_viGb)->getCenterY())
		{
			(*_viGb)->setIsDown(false);
		}
		//Y��������
		if ((*_viGb)->getCenterY() < _player->getY() + 3 && (*_viGb)->getCenterY() > _player->getY() - 3)
		{
			(*_viGb)->setIsYOverlap(true);
		}
		if (!((*_viGb)->getCenterY() < _player->getY() + 3 && (*_viGb)->getCenterY() > _player->getY() - 3))
		{
			(*_viGb)->setIsYOverlap(false);
		}
		//X��������
		if ((*_viGb)->getCenterX() < _player->getX() + 3 && (*_viGb)->getCenterX() > _player->getX() - 3)
		{
			(*_viGb)->setIsXOverlap(true);
		}
		if (!((*_viGb)->getCenterX() < _player->getX() + 3 && (*_viGb)->getCenterX() > _player->getX() - 3))
		{
			(*_viGb)->setIsXOverlap(false);
		}
	}
	//blue
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		//���ʹ̰� �÷��̾��� ������?
		if (_player->getX() > (*_viBb)->getCenterX())
		{
			(*_viBb)->setIsRight(true);
		}
		//���ʹ̰� �÷��̾��� ����?
		if (_player->getX() < (*_viBb)->getCenterX())
		{
			(*_viBb)->setIsRight(false);
		}
		//���ʹ̰� �÷��̾��� ��?
		if (_player->getY() > (*_viBb)->getCenterY())
		{
			(*_viBb)->setIsDown(true);
		}
		//���ʹ̰� �÷��̾��� �Ʒ�?
		if (_player->getY() < (*_viBb)->getCenterY())
		{
			(*_viBb)->setIsDown(false);
		}
		//Y��������
		if ((*_viBb)->getCenterY() < _player->getY() + 3 && (*_viBb)->getCenterY() > _player->getY() - 3)
		{
			(*_viBb)->setIsYOverlap(true);
		}
		if (!((*_viBb)->getCenterY() < _player->getY() + 3 && (*_viBb)->getCenterY() > _player->getY() - 3))
		{
			(*_viBb)->setIsYOverlap(false);
		}
		//X��������
		if ((*_viBb)->getCenterX() < _player->getX() + 3 && (*_viBb)->getCenterX() > _player->getX() - 3)
		{
			(*_viBb)->setIsXOverlap(true);
		}
		if (!((*_viBb)->getCenterX() < _player->getX() + 3 && (*_viBb)->getCenterX() > _player->getX() - 3))
		{
			(*_viBb)->setIsXOverlap(false);
		}
	}
}

void enemyManager::baseballCollision()
{
	//white
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getAttackRect()))		//�浹�ϸ�..	�ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
		{
			(*_viWb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viWb)->setIsCollisionAttack(false);
		}
	}
	//yellow
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viYb)->getAttackRect()))
		{
			(*_viYb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viYb)->setIsCollisionAttack(false);
		}
	}
	//green
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viGb)->getAttackRect()))
		{
			(*_viGb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viGb)->setIsCollisionAttack(false);
		}
	}
	//blue
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viBb)->getAttackRect()))
		{
			(*_viBb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viBb)->setIsCollisionAttack(false);
		}
	}
}


//////////////////////////////////////////////////
//			ī�� ���ʹ� ����
/////////////////////////////////////////////////
void enemyManager::setCard()
{
	for (int i = 0; i < 2; i++)
	{
		card* _cd;
		_cd = new card;
		_cd->init(PointMake(-50 + i * 700, 300));
		_vCard.push_back(_cd);
	}
}


//////////////////////////////////////////////////
//			ī�� ���ʹ� ������Ʈ
/////////////////////////////////////////////////
void enemyManager::updateCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->update();
	}
}


//////////////////////////////////////////////////
//			ī�� ���ʹ� ����
/////////////////////////////////////////////////
void enemyManager::renderCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->render();
	}
}


//////////////////////////////////////////////////
//			ī�� ��ġ Ž����
/////////////////////////////////////////////////
void enemyManager::WhereIsCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if (!(*_viCard)->getIsDash() && !(*_viCard)->getIsBullet())
		{
			//�÷��̾�� ���ʿ� ������
			if (_player->getX() > (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(false);
			}

			//�÷��̾�� �����ʿ� ������
			if (_player->getX() < (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(true);
			}

			//�÷��̾�� ���� ������
			if (_player->getY() > (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(true);
			}

			//�÷��̾�� �Ʒ��� ������
			if (_player->getY() < (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(false);
			}

			RECT temp;
			if (IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc()))
			{
				srand(time(NULL));
				int Num = 0;
				Num = rand() % 3;

				if (Num == 1)
				{
					(*_viCard)->setIsDash(true);
				}

				if (Num == 2)
				{
					(*_viCard)->setIsBullet(true);
				}
			}
		}
	}
}

