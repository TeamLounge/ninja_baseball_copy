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

	//�� �ΰ� �̻󿡼� ���̴� �̹����� �̸� ���
	IMAGEMANAGER->addImage("tile_background", "image/6_UI/tile_background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_green", "image/6_UI/inGame/green.bmp", 63, 72, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_red", "image/6_UI/inGame/red.bmp", 63, 72, true, RGB(255, 0, 255), false);

	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("start", new startScene);
	SCENEMANAGER->addScene("playerSelect", new playerSelectScene);
	SCENEMANAGER->addScene("stage", new stageScene);
	SCENEMANAGER->addScene("stage1", new stageScene1);
	SCENEMANAGER->addScene("stage2", new stageScene2);
	SCENEMANAGER->addScene("stage3", new stageScene3);
	SCENEMANAGER->addScene("ending", new endingScene);

	SCENEMANAGER->changeScene("stage1");
	
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
	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();
	//==================================================
	//���⵵ �ǵ�������
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
	//this->getBackBuffer()->render(getHDC(), 0, 0);
}
