#pragma once
#include "gameNode.h"
class startScene : public gameNode
{
private:
	float _elapsedSecForFrame; //프레임 렌더용 변수
	float _elapsedSecForText; //텍스트 출력용

	vector<string> _dialog; //다이얼로그 저장용 벡터
	int _dialogTextNum[7]; //다이얼로그 출력 얼마나 할지
	int _dialogNow; //현재 출력되고 있는 텍스트 줄

	string _faceImgName; // 얼굴 이미지 전환용
	string _dBackgroundName; //다이얼로그 뒷 배경 전환용

	int _backgroundHeight; //뒷 배경 fade in용

	bool _isFirstDialogEnd; //첫번째 다이얼로그가 끝났는지
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

