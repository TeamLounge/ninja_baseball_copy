#pragma once
#include "gameNode.h"
#include "player.h"
class stageScene3 : public gameNode
{
private:
	player* _player;

	vector<string> vText; //�ؽ�Ʈ ���� �� �ҷ������ ����

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

