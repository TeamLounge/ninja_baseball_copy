#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "progressBar.h"
#include "playerUI.h"
#include "timerUI.h"
#include "gameOverUI.h"
#include <queue>

class gameOverUI;

struct tagShutter
{
	//����
	float x, y; //left top ��ǥ
	RECT body; //��ü rc
	RECT rc; //Ÿ�� ���� rc
	bool isCrush;
	bool isClosed;
	int height; //������ ��� ���ؼ�
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

	float  _down, _gravity;

	queue<float> _cameraStopX;
	
	gameOverUI* _gameoverUI;

	bool _isSetCard;
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

