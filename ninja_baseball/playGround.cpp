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

	//	����ؼ� �ٸ��� �ϽǼ� �����ϱ�
	//	���� ������ϼ̴ٸ� �ٸ��� new�Ҵ��� ���ֽø� �˴ϴ�.
	//	player = new (����� Ŭ����);

	IMAGEMANAGER->addImage("tile_background", "image/6_UI/tile_background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);

	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("start", new startScene);
	SCENEMANAGER->addScene("playerSelect", new playerSelectScene);
	SCENEMANAGER->addScene("stage", new stageScene);
	SCENEMANAGER->addScene("ending", new endingScene);


	SCENEMANAGER->changeScene("stage");
	
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
