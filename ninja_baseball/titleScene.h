#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private :
	RECT _silhouette; //실루엣 이미지 움직일 용
	float _elapsedSec; //타이틀 프레임 렌더용 elapsedtime 저장

	float _textElapsedSec; //버튼 문구 깜박임 용
	int _textBlend; //버튼 깜박임 위해 투명도 설정

	bool _isTitleStart; //타이틀 들어오는 액션 시작
	bool _isTitleStoped; //움직이는 모션이 끝나면

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

