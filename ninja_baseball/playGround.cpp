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

	//�÷��̾�(����) ������ �̹���
	IMAGEMANAGER->addFrameImage("red_idle", "image/2_player/red/red_idle.bmp", 0, 0, 240, 462, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_walk", "image/2_player/red/red_walk.bmp", 0, 0, 1440, 522, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_jump", "image/2_player/red/red_jump.bmp", 0, 0, 231, 498, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack", "image/2_player/red/red_attack.bmp", 0, 0, 7344, 630, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_run", "image/2_player/red/red_run.bmp", 0, 0, 768, 480, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_grip2", "image/2_player/red/red_grip2.bmp", 0, 0, 666, 444, 3, 2, true, RGB(255, 0, 255));
	//�׸��� �̹���
	IMAGEMANAGER->addImage("shadow", "image/2_player/green/shadow.bmp", 145, 30, true, RGB(255, 0, 255));

	//����ؼ� �ٸ��� �ϽǼ� �����ϱ�
	//���� ������ϼ̴ٸ� �ٸ��� new�Ҵ��� ���ֽø� �˴ϴ�.
	// player = new (����� Ŭ����);

	_red = new player;
	_red->init();
		
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
		
	_red->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	TIMEMANAGER->render(getMemDC());

	_red->render();
	
	//==================================================
	//���⵵ �ǵ�������
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
