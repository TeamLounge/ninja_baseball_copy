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

	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("playerSelect", new playerSelectScene);
	SCENEMANAGER->addScene("stage", new stageScene);
	SCENEMANAGER->addScene("ending", new endingScene);

	SCENEMANAGER->changeScene("title");

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
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC());
	}
	//==================================================
	//���⵵ �ǵ�������
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
	//this->getBackBuffer()->render(getHDC(), 0, 0);
}
