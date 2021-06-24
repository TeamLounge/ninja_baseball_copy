#pragma once
#include "gameNode.h"
#include "playerstate.h"

class player : public gameNode
{
private:
	//기본적인 요소 다른게 필요하다면 추가해주셔도됩니다
	//===================================
	image* _playerimg; //이미지
	RECT _playerrc; // 렉트
	float _x, _y; // 좌표
	playerstate* _state; // 상태패턴 변수
	//==================================
	//추가항목들은 밑에 추가해주세용 주석도 달아주시는거 잊지 말아주세요


public:
	//public변수는 다른 클래스쪽에서 막 참조해도 되는걸로 해주세용 get,set쓰기 귀찮으니까 ㅜ
	//이건 플레이어의 좌,우 구분할 때 쓰는 bool변수 
	bool isRight;

	//함수를 선언하려면 여기에다
	//겟터와 셋터는 따로따로 밑에 다 선언 해주세요
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void handleInput(); // 상태변환받는함수


	//수만은 겟터
	virtual image* getImage() { return _playerimg; }
	virtual RECT getRect() { return _playerrc; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }


	//수만은 셋터
	virtual void setImage(image* img) { _playerimg = img; }
	virtual void setRect(RECT rc) { _playerrc = rc; }
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }

};

