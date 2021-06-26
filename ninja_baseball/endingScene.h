#pragma once
#include "gameNode.h"

class endingScene : public gameNode
{
private:
	RECT _textRC; //텍스트 출력하는 공간 rc

	int _sceneHeight; //캐릭터와 배경 fadein 효과 위해서

	float _elapsedTime;

	int _dialogTextNum; //출력할 개수

	char str[128];
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

