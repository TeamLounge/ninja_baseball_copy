#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "progressBar.h"
#include "playerUI.h"
#include "timerUI.h"

struct tagXY
{
	float x, y;
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

	vector<tagXY> _guide;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���� �ȼ��浹
	void shutterCollison();
};

