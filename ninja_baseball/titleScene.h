#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private :
	RECT _silhouette; //�Ƿ翧 �̹��� ������ ��
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

