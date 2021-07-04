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

	playerUI* _playerUI; //�÷��̾� ����â
	
	timerUI* _timerUI; //Ÿ�̸�

	tagShutter _shutter; //����

	float  _down, _gravity;

	queue<float> _setEnemy;

	queue<float> _cameraStopX;

	gameOverUI* _gameoverUI;
	
	bool _setBaseBallandGlove;
	bool _isAllEnemySet;
	bool _isWhiteBaseBallSet;

	int _count;

	bool _isGameOverSound;
	bool _isContinueSound;
	int _soundCount;
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

