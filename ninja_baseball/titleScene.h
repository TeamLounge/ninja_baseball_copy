#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private :
	RECT _silhouette; //�Ƿ翧 �̹��� ������ ��
	float _elapsedSec;

	bool _isTitleStart; //Ÿ��Ʋ ������ �׼� ����
	bool _isTitleStoped; //�����̴� ����� ������

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

