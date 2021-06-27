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

	//_Ryno = new player;
	//_Ryno->init(2);
	_red = new player;
	_red->init(1);

	_em = new enemyManager;
	_em->init();

	_red->setEmMemoryAddressLink(_em);
	_em->setPlayerMemoryAddressLink(_red);

	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("playerSelect", new playerSelectScene);
	SCENEMANAGER->addScene("stage", new stageScene);
	SCENEMANAGER->addScene("ending", new endingScene);

	SCENEMANAGER->changeScene("ending");
	
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
	//_Ryno->update();
	_red->update();
	_em->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();

	//_Ryno->render();
	_red->render();
	_em->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC());
	}

	//==================================================
	//���⵵ �ǵ�������
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
	//this->getBackBuffer()->render(getHDC(), 0, 0);
}
