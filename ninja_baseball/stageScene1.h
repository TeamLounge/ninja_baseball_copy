#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "progressBar.h"
#include "playerUI.h"
#include "timerUI.h"
#include <queue>

struct tagShutter
{
	//����
	RECT rc; //Ÿ�� ���� rc
	bool isCrush;
	vector<string> sutterParticle;
};

class stageScene1 : public gameNode
{


private:
	player* _player;

	int _playerSelect; //���� ���õ� �÷��̾� ����
	vector<string> vText; //�ؽ�Ʈ�κ��� �޾ƿ� ������ ���� �� �ؽ�Ʈ�� �������� �ϴ� ���� 

	enemyManager* _em;
	objectManager* _obj;

	playerUI* _playerUI;
	
	timerUI* _timerUI;

	tagShutter _shutter;

	bool _isAllDead;

	queue<float> _cameraStopX;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���� �ȼ��浹
	void shutterCollison();

	void setImage();

	void setShutter();
	void updateShutter();
};

