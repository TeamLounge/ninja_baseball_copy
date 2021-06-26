#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private :
	RECT _silhouette; //실루엣 이미지 움직일 용
	float _elapsedSec;

	bool _isTitleStart; //타이틀 들어오는 액션 시작
	bool _isTitleStoped; //움직이는 모션이 끝나면

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

