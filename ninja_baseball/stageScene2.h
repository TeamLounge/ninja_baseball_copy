#pragma once
#include "gameNode.h"
#include "player.h"
class stageScene2 : public gameNode
{
private:
	vector<string> vText; //�ؽ�Ʈ ���� �� �ҷ������ ����

	string _imageName;
	float _x, _y; //�̹��� ���� x, y��ǥ

	float _distance; //_y�� ȭ�� �߽� ������ �Ÿ�

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

