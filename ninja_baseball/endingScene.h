#pragma once
#include "gameNode.h"

class endingScene : public gameNode
{
private:
	RECT _textRC; //�ؽ�Ʈ ����ϴ� ���� rc

	int _sceneHeight; //ĳ���Ϳ� ��� fadein ȿ�� ���ؼ�

	float _elapsedTime;

	int _dialogTextNum[3]; //����� ����
	int _dialogNow;
	vector<string> _dialog;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

