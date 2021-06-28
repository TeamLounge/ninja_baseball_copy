#pragma once
#include "gameNode.h"
class startScene : public gameNode
{
private:
	float _elapsedSecForFrame; //프레임 렌더용 변수
	float _elapsedSecForText; //텍스트 출력용

	vector<string> _dialog;
	int _dialogTextNum[7];
	int _dialogNow;

	string _faceImgName; // 얼굴 이미지 전환용
	string _dBackgroundName; //다이얼로그 뒷 배경 전환용

	int _backgroundHeight; //뒷 배경 fade in용

	bool _isFirstDialogEnd;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

