#pragma once
#include "gameNode.h"
struct tagCharaterSelect
{
	RECT rc;
	string imageName;
};
class playerSelectScene : public gameNode
{
private:
	RECT _cursor[4]; //커서 이미지 이동할 렉트
	int _currentSelect; //현재 선택한 캐릭터

	tagCharaterSelect _character[4]; //캐릭터 이미지 렉트
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

