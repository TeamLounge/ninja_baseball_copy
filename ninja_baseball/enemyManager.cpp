#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	
	//setBlueBaseball();		
	setGreenBaseball();
	//setWhiteBaseball();			
	//setYellowBaseball();		//������ ������
	
	//setBat();					
	//setCard();
	//setGlove();				
	//setBoss();				

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	//updateBaseball();
	//baseballCollision();	//�÷��̾� vs ���̽���Ÿ�ݹ�����Ʈ


	updateBat();
	batCollision();

	//updateGlove();
	//gloveCollision();
	//
	//playerLocation();

	//updateCard();
	//WhereIsCard();	

	//updateBoss();
	//assultedCollisionBoss();
}

void enemyManager::render()
{

	renderBaseball();
	//renderGlove();
	renderCard();
	//renderBoss();

	char str1[126];
	sprintf_s(str1, "�¾ѽ�");
	char str2[125];
	sprintf_s(str2, "������");
	char str3[125];
	sprintf_s(str3, "Ǯ�Ⱦ�");

	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if ((*_viWb)->isdamage)
		{
			TextOut(getMemDC(), (*_viWb)->getRect().left - 100, (*_viWb)->getRect().top - 100, str1, strlen(str1));
		}
		if ((*_viWb)->iscatch)
		{
			TextOut(getMemDC(), (*_viWb)->getRect().left - 100, (*_viWb)->getRect().top - 100, str2, strlen(str2));
		}
	}
}

void enemyManager::setBlueBaseball()
{
	//BLUE
	for (int i = 0; i < 2; i++)
	{
		blueBaseball* _bb = new blueBaseball;
		_bb->init(PointMake(300 + i * 100, -50 + i * 80));
		_vBb.push_back(_bb);

	}
}
void enemyManager::setGreenBaseball()
{
	//GREEN
	for (int i = 0; i < 3; i++)
	{
		greenBaseball* _gb = new greenBaseball;
		_gb->init(PointMake(400 + i * 140, -100 + i * 120));
		_vGb.push_back(_gb);

	}
}
void enemyManager::setWhiteBaseball()
{
	//WHITE
	for (int i = 0; i < 3; i++)
	{
		whiteBaseball* _wb = new whiteBaseball;	//�����Ҵ� ���ְ�
		_wb->init(PointMake(WINSIZEX + i * 220, BACKGROUNDY - 400 - 50 + i * 200));			//�̴����� ��ġ ����ְ�
		_vWb.push_back(_wb);					//��ġ ����� �ָ� ���Ϳ� ����
	}
	//�� ����ġ ���� �� �������� for�� �ۿ� ���� ���ִ� �͵� ���
	//whiteBaseball* _wb1 = new whiteBaseball;	//�����Ҵ� ���ְ�
	//_wb1->init(PointMake(500, 500));			//�̴����� ��ġ ����ְ�
	//_vWb.push_back(_wb1);					//��ġ ����� �ָ� ���Ϳ� ����
}
void enemyManager::setYellowBaseball()
{
	//YELLOW
	for (int i = 0; i < 2; i++)
	{
		yellowBaseball* _yb = new yellowBaseball;
		_yb->init(PointMake(500 + i * 180, -50 + i * 160));		//x��ǥ �����ϰ� ���� ����!!!!! ���ĺ��δ�!! 0���� ����δ�!!!
		_vYb.push_back(_yb);
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
	////////////////
   //   white    //
   ///////////////
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
	////////////////
   //   yellow   //
   ///////////////
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
	////////////////
   //    green   //
   ///////////////
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
	////////////////
   //    blue    //
   ///////////////
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
	////////////////
	//     bat   //
	///////////////
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		if (!(*_viBat)->isJump)	//���� = true
		{
			//���ʹ̰� �÷��̾��� ������?

			if (_player->getX() > (*_viBat)->getCenterX())
			{
				(*_viBat)->setIsRight(true);
			}
			//���ʹ̰� �÷��̾��� ����?
			if (_player->getX() < (*_viBat)->getCenterX())
			{
				(*_viBat)->setIsRight(false);
			}
			//���ʹ̰� �÷��̾��� ��?
			if (_player->getY() > (*_viBat)->getCenterY())
			{
				(*_viBat)->setIsDown(true);
			}
			//���ʹ̰� �÷��̾��� �Ʒ�?
			if (_player->getY() < (*_viBat)->getCenterY())
			{
				(*_viBat)->setIsDown(false);
			}
		}
		//Y��������
		if ((*_viBat)->getCenterY() < _player->getY() + 3 && (*_viBat)->getCenterY() > _player->getY() - 3)
		{
			(*_viBat)->setIsYOverlap(true);
		}
		if (!((*_viBat)->getCenterY() < _player->getY() + 3 && (*_viBat)->getCenterY() > _player->getY() - 3))
		{
			(*_viBat)->setIsYOverlap(false);
		}
		//X��������
		if ((*_viBat)->getCenterX() < _player->getX() + 3 && (*_viBat)->getCenterX() > _player->getX() - 3)
		{
			(*_viBat)->setIsXOverlap(true);
		}
		if (!((*_viBat)->getCenterX() < _player->getX() + 3 && (*_viBat)->getCenterX() > _player->getX() - 3))
		{
			(*_viBat)->setIsXOverlap(false);
		}
	}
	//////////////////
	//    glove   ///
	/////////////////
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		if (!(*_viGlove)->isJump)	//���� = true
		{
			//���ʹ̰� �÷��̾��� ������?

			if (_player->getX() > (*_viGlove)->getCenterX())
			{
				(*_viGlove)->setIsRight(true);
			}
			//���ʹ̰� �÷��̾��� ����?
			if (_player->getX() < (*_viGlove)->getCenterX())
			{
				(*_viGlove)->setIsRight(false);
			}
			//���ʹ̰� �÷��̾��� ��?
			if (_player->getY() > (*_viGlove)->getCenterY())
			{
				(*_viGlove)->setIsDown(true);
			}
			//���ʹ̰� �÷��̾��� �Ʒ�?
			if (_player->getY() < (*_viGlove)->getCenterY())
			{
				(*_viGlove)->setIsDown(false);
			}
		}
		//Y��������
		if ((*_viGlove)->getCenterY() < _player->getY() + 3 && (*_viGlove)->getCenterY() > _player->getY() - 3)
		{
			(*_viGlove)->setIsYOverlap(true);
		}
		if (!((*_viGlove)->getCenterY() < _player->getY() + 3 && (*_viGlove)->getCenterY() > _player->getY() - 3))
		{
			(*_viGlove)->setIsYOverlap(false);
		}
		//X��������
		if ((*_viGlove)->getCenterX() < _player->getX() + 3 && (*_viGlove)->getCenterX() > _player->getX() - 3)
		{
			(*_viGlove)->setIsXOverlap(true);
		}
		if (!((*_viGlove)->getCenterX() < _player->getX() + 3 && (*_viGlove)->getCenterX() > _player->getX() - 3))
		{
			(*_viGlove)->setIsXOverlap(false);
		}
	}
}

void enemyManager::baseballCollision()
{
	////////////////
   //   white    //
   ///////////////

	//ATTACK//
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
	//DAMAGED//
	//for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getRect()) &&
	//		KEYMANAGER->isOnceKeyDown('M'))												//���ʹ� ���� �浹�ϸ�.. �ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
	//	{
	//		(*_viWb)->setIsCollisionDamaged(true);		//�浹������ bool �� true�� ��ȯ
	//		(*_viWb)->damageCount++;

	//		if ((*_viWb)->damageCount > 5)
	//		{
	//			(*_viWb)->damageCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		(*_viWb)->setIsCollisionDamaged(false);		//�ƴϸ� false�� ��ȯ
	//	}
	//}

		////DAMAGED_(�������� ����� ��)
		//if (_player->isattack) {
		//	if (_player->_shadow->getCenterY() >= (*_viWb)->_wbShadow.rc.top && 
		//		_player->_shadow->getCenterY() <= (*_viWb)->_wbShadow.rc.bottom) {
		//		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viWb)->getRect()))
		//		{
		//			(*_viWb)->isdamage= true;
		//		}
		//	}
		//}
		//if (_player->iscrawl && !_player->isattack)
		//{
		//	if (_player->_shadow->getCenterY() >= (*_viWb)->_wbShadow.rc.top &&
		//		_player->_shadow->getCenterY() <= (*_viWb)->_wbShadow.rc.bottom) {
		//		if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getRect()))
		//		{
		//			(*_viWb)->iscatch = true;
		//		}
		//	}
		//}
	

	////////////////
   //   yellow   //
   ///////////////
	//ATTACK//
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
	//DAMAGED//
	//for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_player->getRect(), &(*_viYb)->getRect()) &&
	//		KEYMANAGER->isOnceKeyDown('M'))												//���ʹ� ���� �浹�ϸ�.. �ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
	//	{
	//		(*_viYb)->setIsCollisionDamaged(true);		//�浹������ bool �� true�� ��ȯ
	//		(*_viYb)->damageCount++;

	//		if ((*_viYb)->damageCount > 5)
	//		{
	//			(*_viYb)->damageCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		(*_viYb)->setIsCollisionDamaged(false);		//�ƴϸ� false�� ��ȯ
	//	}
	//}
	////////////////
   //   green    //
   ///////////////
	//ATTACK//
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
	//DAMAGED//
	//for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_player->getRect(), &(*_viGb)->getRect()) &&
	//		KEYMANAGER->isOnceKeyDown('M'))												//���ʹ� ���� �浹�ϸ�.. �ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
	//	{
	//		(*_viGb)->setIsCollisionDamaged(true);		//�浹������ bool �� true�� ��ȯ
	//		(*_viGb)->damageCount++;

	//		if ((*_viGb)->damageCount > 5)
	//		{
	//			(*_viGb)->damageCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		(*_viGb)->setIsCollisionDamaged(false);		//�ƴϸ� false�� ��ȯ
	//	}
	//}
	////////////////
   //   blue     //
   ///////////////
	//ATTACK//
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
	//DAMAGED//
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viBb)->getRect())) //�÷��̾� ��Ÿ��� ���ʹ� ���� �浹�ϸ�.. �ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
		{
			(*_viBb)->setIsCollisionDamaged(true);		//�浹������ bool �� true�� ��ȯ
				(*_viBb)->damageCount++;
		
				if ((*_viBb)->damageCount > 5)
				{
					(*_viBb)->damageCount = 0;
				}
		}
		else (*_viBb)->setIsCollisionDamaged(false);		//�ƴϸ� false�� ��ȯ


		if (!_player->isattack) (*_viBb)->isCrash = false;
	}
}
void enemyManager::batCollision()
{
	////////////////
   //     bat    //
   ///////////////
	//Attack//
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viBat)->getAttackRect()))		//���ʹ� ��Ÿ��� ������.. �ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
		{
			(*_viBat)->setIsCollisionAttack(true);		//�浹������ bool �� true�� ��ȯ
		}
		else
		{
			(*_viBat)->setIsCollisionAttack(false);		//�ƴϸ� false�� ��ȯ
		}
	}
	//Damaged//
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viBat)->getRect())
			&& !(*_viBat)->isCollisionDamaged && _player->isattack && !(*_viBat)->isCrash)												//���ʹ� ���� �浹�ϸ�.. �ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
		{
			(*_viBat)->setIsCollisionDamaged(true);		//�浹������ bool �� true�� ��ȯ
			(*_viBat)->isCrash = true;
			//(*_viBat)->damageCount++;				
		}
			
		if (!_player->isattack) (*_viBat)->isCrash = false;

		//else if (!(IntersectRect(&temp, &_player->getRect(), &(*_viBat)->getRect())))
		//{
		//	(*_viBat)->setIsCollisionDamaged(false);		//�ƴϸ� false�� ��ȯ
		//}
	}
}
void enemyManager::gloveCollision()
{
	////////////////
   //    glove   //
   ///////////////
    //Attack glove�� �����ϸ�//
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viGlove)->getAttackRect()))		//�浹�ϸ�..	�ٸ� ���¿��� �浹 ���� �Ǻ��Ͽ� ���� �����ϱ� ����
		{
			(*_viGlove)->setIsCollisionAttack(true);		//�浹������ bool �� true�� ��ȯ
		}
		else
		{
			(*_viGlove)->setIsCollisionAttack(false);		//�ƴϸ� false�� ��ȯ
		}
	}
	//Damaged glove�� ������//
	
}

void enemyManager::setBat()
{
	for (int i = 0; i < 3; i++)
	{
		bat* _bat = new bat;
		_bat->init(PointMake(470 + i * 130, WINSIZEY - 300 - i * 150));
		_vBat.push_back(_bat);
	}
}
void enemyManager::updateBat()
{
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		(*_viBat)->update();
	}
}
void enemyManager::renderBat()
{
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		(*_viBat)->render();
	}
}

void enemyManager::setGlove()	//�¾�� ��ǥ
{
	for (int i = 0; i < 2; i++)
	{
		glove* _glove = new glove;
		_glove->init(PointMake(470 + i * 30, WINSIZEY - 500 - i * 150));
		_vGlove.push_back(_glove);
	}
}
void enemyManager::updateGlove()
{
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		(*_viGlove)->update();
	}
}
void enemyManager::renderGlove()
{
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		(*_viGlove)->render();
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
			if (IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc())
				&& !(*_viCard)->_isCrash)
			{
				(*_viCard)->numPattern = rand() % 3;
				(*_viCard)->setIsDash(false);
				(*_viCard)->setIsBullet(false);
				(*_viCard)->_isCrash = true;

				if ((*_viCard)->numPattern == 1)
				{
					(*_viCard)->setIsDash(true);
				}

				if ((*_viCard)->numPattern == 2)
				{
					(*_viCard)->setIsBullet(true);
				}
			}

			if (!IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc()))
			{
				(*_viCard)->_isCrash = false;
			}
		}
	}
}


//////////////////////////////////////////////////
//			ī�� �ǰ� �浹
/////////////////////////////////////////////////
void enemyManager::assultedCollisionCard()
{
	/*for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if ((*_viCard)->_isMoveState && _player->isattack)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
			{
				if (_player->_isGreenAttack1 || _player->_isGreenAttack2 ||
					_player->_isGreenAttack3 || _player->_isGreenDashAttack ||
					_player->_isGreenJumpAttack)
				{
					_boss->_isSmallDamaged = true;
				}

				if (_player->_isGreenDashAlt || _player->_isGreenJumpPowerAttack)
				{
					_boss->_isDamaged = true;
				}
			}
		}

		if (_boss->_isSmallDamagedState && _player->isattack)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
			{
				if (_player->_isGreenAttack1)
				{
					_boss->_isSmallDamaged = true;
				}

				if (_player->_isGreenAttack2 || _player->_isGreenAttackFrontCombo1)
				{
					_boss->_isGreenAttack12 = true;
				}

				if (_player->_isGreenAttack3 || _player->_isGreenAttackFrontCombo2)
				{
					_boss->_isGreenAttack3 = true;
				}
			}
		}

		if (_boss->_isMoveState && _player->iscrawl)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boss->_assultedRect, &_player->getRect()))
			{
				_player->iscatch = true;
				_boss->_isGreenCatch = true;
				_boss->_isSmallDamaged = true;
			}
		}

		if (!_player->iscatch)
		{
			_boss->_isGreenCatch = false;
		}

		if (_player->_isGreenCatchAttack && _player->iscatch)
		{
			_boss->_isGreenCatchAttack = true;
			_player->_isGreenCatchAttack = false;
			_player->_isGreenCatchBackAttack = false;
		}

		if (_player->_isGreenCatchBackAttack && _player->iscatch)
		{
			_boss->_isGreenCatchBackAttack = true;
			_player->_isGreenCatchAttack = false;
		}

		if (_player->_isGreenCatchFrontCombo && _player->iscatch)
		{
			_boss->_isGreenCatchFrontCombo = true;
			_player->_isGreenCatchFrontCombo = false;
		}
	}*/

}


/////////////////////////////////
//  ######���� ��ġ ���� ########
/////////////////////////////////
void enemyManager::setBoss()
{
	_boss = new boss;
	_boss->init(PointMake(700, WINSIZEY / 2 - 200));
}


/////////////////////////////////
// ######���� ������Ʈ �׸� ########
/////////////////////////////////
void enemyManager::updateBoss()
{
	_boss->update();
	WhereIsBoss();				//����<->�÷��̾� ��ġ Ȯ�ο�
	attackCollision();
}


/////////////////////////////////
//  ######���� �׸��� ########
/////////////////////////////////
void enemyManager::renderBoss()
{
	_boss->render();
}


/////////////////////////////////
//  ######���� ��ġ��� ########
/////////////////////////////////
void enemyManager::WhereIsBoss()
{
	//�÷��̾�� ���ʿ� ������
	if (_player->_shadow->getCenterX() > _boss->_bossShadow.x)
	{
		_boss->_isLeft = false;
	}

	//�÷��̾�� �����ʿ� ������
	if (_player->_shadow->getCenterX() < _boss->_bossShadow.x)
	{
		_boss->_isLeft = true;
	}

	//�÷��̾�� ���� ������
	if (_player->_shadow->getCenterY() > _boss->_bossShadow.y)
	{
		_boss->_isUpper = true;
	}

	//�÷��̾�� �Ʒ��� ������
	if (_player->_shadow->getCenterY() < _boss->_bossShadow.y)
	{
		_boss->_isUpper = false;
	}
	
	//���� �ȿ� ������ ��鸲 ��ž��

	if (_player->_shadow->getCenterX() + 150 > _boss->_bossShadow.x && _player->_shadow->getCenterX() - 150 < _boss->_bossShadow.x)
	{
		_boss->_isMoveStopRangeX = true;
	}

	if (!(_player->_shadow->getCenterX() + 150 > _boss->_bossShadow.x && _player->_shadow->getCenterX() - 150 < _boss->_bossShadow.x))
	{
		_boss->_isMoveStopRangeX = false;
	}

	if (_player->_shadow->getCenterY() + 10 > _boss->_bossShadow.y && _player->_shadow->getCenterY() - 10 < _boss->_bossShadow.y)
	{
		_boss->_isMoveStopRangeY = true;
	}

	if (!(_player->_shadow->getCenterY() + 10 > _boss->_bossShadow.y &&_player->_shadow->getCenterY() - 10 < _boss->_bossShadow.y))
	{
		_boss->_isMoveStopRangeY = false;
	}
}



/////////////////////////////////
//  ######���� �����浹 ########
/////////////////////////////////
void enemyManager::attackCollision()
{
	///////////////////////////////////////////
	// #######   ���� ���Ÿ� ����   ##########
	/////////////////////////////////////////// ���Ÿ� ���� ������ȣ��  isSucceedShootingAttack �Դϴ�.

	_boss->_numAtkPattern = RND->getFromIntTo(0, 4);

	if (PtInRect(&_boss->_longRangeAtkRc,
		PointMake(_player->getX(), _player->getRect().bottom)) &&
		!_boss->_isLongRangeCrash && !_boss->_isShootingAttack &&
		!_boss->_isJabAttack)
	{

		int Num = _boss->_numAtkPattern;

		_boss->_isLongRangeCrash = true;

		if (Num == 3)
		{
			_boss->_isShootingAttack = true; //�̰� �׳� ���¸� ���������� ����ġ 
		}
	}

	if (!PtInRect(&_boss->_longRangeAtkRc,
		PointMake(_player->getX(), _player->getRect().bottom)))
	{
		_boss->_isLongRangeCrash = false;
	}

	//���Ÿ� ���� ������������
	if (_boss->_isTrigger && (PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->getX(), _player->_shadow->getY() + _player->_shadow->getHeight())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY() + _player->_shadow->getHeight()))))
	{
		_boss->_isSucceedShootingAttack = true;
	}

	//���Ÿ� ���� ������������~
	if (!(_boss->_isTrigger && (PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->getX(), _player->_shadow->getY() + _player->_shadow->getHeight())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY() + _player->_shadow->getHeight())))))
	{
		_boss->_isSucceedShootingAttack = false;
	}

	///////////////////////////////////////////
	// #######   ���� jab ����, straight ����   ##########
	/////////////////////////////////////////// ����� ������ȣ�� _isSucceedJabAttack �Դϴ�. ��Ʈ����Ʈ���� ������ȣ�� _isSucceedStraightAttack �Դϴ�.

	RECT temp;
	if (IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect()) && _boss->_isMoveState &&
		!_boss->_isCrash)
	{
		int randNum = rand() % 6;
		if (randNum != 1) _boss->_missCount++;
		_boss->_isCrash = true;

		if (randNum == 1 || _boss->_missCount > 3)
		{
			_boss->_missCount = 0;
			_boss->_isJabAttack = true;
		}

		if (randNum == 2)
		{
			_boss->_isStraightAttack = true;
		}
	}

	if (!(IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect())))
	{
		_boss->_isCrash = false;
	}

	RECT rc = RectMake(_player->_shadow->getX(), _player->_shadow->getY(),
		_player->_shadow->getWidth(), _player->_shadow->getHeight());

	//�� ���� ������������~
	if (_boss->_isJabAttack && IntersectRect(&temp, &_boss->_boss.rc, &rc))
	{
		_boss->_isSucceedJabAttack = true;
	}
	//�� ���� ������������~
	if (!(_boss->_isJabAttack && IntersectRect(&temp, &_boss->_boss.rc, &rc)))
	{
		_boss->_isSucceedJabAttack = false;
	}

	/////////////////////////////////////////////
	// #######  ���� ������ ���� ##########     //
	/////////////////////////////////////////////
	if (_boss->_isDamagedState)
	{
		if (IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect()))
		{
			_boss->_isUpperCut = true;
			_boss->_isCrash = false;
		}

		if (!(IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect())))
		{
			_boss->_isUpperCut = false;
		}
	}
}

/////////////////////////////////
//  ######���� �ǰ��浹 ########
///////////////////////////////// ���� �������� //
void enemyManager::assultedCollisionBoss()
{
	//Ÿ�� z�����ϱ�zzz ���� ���Դϴ�^^//
	if (_boss->_isMoveState && _player->isattack)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
		{
			if (_player->_isGreenAttack1 ||	_player->_isGreenAttack2 ||
				_player->_isGreenAttack3 || _player->_isGreenDashAttack ||
				_player->_isGreenJumpAttack)
			{
				_boss->_isSmallDamaged = true;
			}

			if (_player->_isGreenDashAlt || _player->_isGreenJumpPowerAttack)
			{
				_boss->_isDamaged = true;
			}
		}
	}

	if (_boss->_isSmallDamagedState && _player->isattack)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
		{
			if (_player->_isGreenAttack1)
			{
				_boss->_isSmallDamaged = true;
			}

			if (_player->_isGreenAttack2 || _player->_isGreenAttackFrontCombo1)
			{
				_boss->_isGreenAttack12 = true;
			}

			if (_player->_isGreenAttack3 || _player->_isGreenAttackFrontCombo2)
			{
				_boss->_isGreenAttack3 = true;
			}
		}
	}

	if (_boss->_isMoveState && _player->iscrawl)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->getRect()))
		{
			_player->iscatch = true;
			_boss->_isGreenCatch = true;
			_boss->_isSmallDamaged = true;
		}
	}

	if (!_player->iscatch)
	{
		_boss->_isGreenCatch = false;
	}

	if (_player->_isGreenCatchAttack && _player->iscatch)
	{
		_boss->_isGreenCatchAttack = true;
		_player->_isGreenCatchAttack = false;
		_player->_isGreenCatchBackAttack = false;
	}

	if (_player->_isGreenCatchBackAttack && _player->iscatch)
	{
		_boss->_isGreenCatchBackAttack = true;
		_player->_isGreenCatchAttack = false;
	}

	if (_player->_isGreenCatchFrontCombo && _player->iscatch)
	{
		_boss->_isGreenCatchFrontCombo = true;
		_player->_isGreenCatchFrontCombo = false;
	}
}
