#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private :
	RECT _silhouette; //실루엣 이미지 움직일 용
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

