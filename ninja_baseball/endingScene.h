#pragma once
#include "gameNode.h"

class endingScene : public gameNode
{
private:
	RECT _textRC; //�ؽ�Ʈ ����ϴ� ���� rc

	int _sceneHeight; //ĳ���Ϳ� ��� fadein ȿ�� ���ؼ�

	float _elapsedTime;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

