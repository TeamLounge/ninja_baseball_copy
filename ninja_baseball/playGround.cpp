#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);

	

	//����ؼ� �ٸ��� �ϽǼ� �����ϱ�
	//���� ������ϼ̴ٸ� �ٸ��� new�Ҵ��� ���ֽø� �˴ϴ�.
	// player = new (����� Ŭ����);

	_Ryno = new player;
	_Ryno->init(2);
	_red = new player;
	_red->init(1);

	//_redShadow = new redShadow; //������ �׸��� �Ҵ�?
	//_redShadow->init(2);
		
	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();
	
}


void playGround::update()
{
	gameNode::update();
	_Ryno->update();
	_red->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	TIMEMANAGER->render(getMemDC());

	
	_red->render();
	_Ryno->render();
	
	//==================================================
	//���⵵ �ǵ�������
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
