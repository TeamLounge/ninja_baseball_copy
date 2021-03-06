#pragma once
#include "gameNode.h"
#include "timerUI.h"
struct tagCharacterSelect
{
	RECT rc;
	string imageName;
};
class playerSelectScene : public gameNode
{
private:
	RECT _cursor[4]; //커서 이미지 이동할 렉트
	int _currentSelect; //현재 선택한 캐릭터

	float _elapsedSec;

	float _characterFrameSec;
	
	bool _isSelect; //선택했는지 확인

	tagCharacterSelect _character[4]; //캐릭터 이미지 렉트

	timerUI* _timerUI;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

