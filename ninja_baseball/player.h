#pragma once
#include "gameNode.h"
#include "playerstate.h"

#include "enemyManager.h"
class playerstate; //이것이 문제였네..

//class enemyManager; //enemy들과 충돌 위한 전방선언(상호참조용)

class player : public gameNode
{
private:
	//기본적인 요소 다른게 필요하다면 추가해주셔도됩니다
	//===================================
	image* _playerimg; //이미지
	string _playerImgName;

	RECT _playerrc; // 렉트
	float _x, _y; // 좌표
	float _shadowX, _shadowY;
	playerstate* _state; // 상태패턴 변수

	//==================================
	//추가항목들은 밑에 추가해주세용 주석도 달아주시는거 잊지 말아주세요
	int _character; // 캐릭터 구분변수 1이면 captin 2 Ryno
	int _life , _hp;  // 목숨과 hp

	//enemyManager* _em; //애너미정보가져오기
public:
	//public변수는 다른 클래스쪽에서 막 참조해도 되는걸로 해주세용 get,set쓰기 귀찮으니까 ㅜ
	//이 렉트는 player가 공격중이다 하면 상태클래스내에서 꺼낼 렉트를 미리 생성해두는겁니다.
	RECT _attack_rc;
	RECT _grip_rc;
	//이건 플레이어의 좌,우 구분할 때 쓰는 bool변수 , 공격을했는지 안했는지 판단하기위해서 쓰는 bool변수 , 맞았는지 안맞았는지 판단하는 bool 변수
	//기어다니는지 아닌지 판단하는 bool변수 , 잡앗는지 안 잡았는지 확인하는 bool 변수, 날때 전기쏘기 bool변수
	bool isRight, isattack, isdamage;
	bool iscrawl , iscatch ,isfly, isEnd;
	image* _shadow; // 그림자이미지
	bool _isrun ,_run;
	float _runtime;
	//플레이어 스테이트 상태 확인
	bool _isGreenAttackState, _isGreenAttack1, _isGreenAttack2, _isGreenAttack3;
	bool _isGreenAttackFrontCombo1, _isGreenAttackFrontCombo2;
	bool _isGreenDashAlt, _isGreenDashAttack;
	bool _isGreenJumpAttack, _isGreenJumpPowerAttack;
	bool _isGreenCatchFrontCombo, _isGreenCatchAttack, _isGreenCatchBackAttack;

	bool _isRedAttackState, _isRedAttack1, _isRedAttack2, _isRedAttack3;
	bool _isRedDownAttack, _isRedDynamiteDance, _isRedCatchAttack, _isCatchAttackSwitch, _isRedHomeRunAttack;
	bool _isRedJumpAttack, _isRedCatch, _isRedGrip, _isRedLegKickAttack, _isRedSliding;
	bool _isRedDashAttack, _isRedCatchAttackOn, _isRedThrow;
	int _catchAttackCnt;


	image* _effect; // 번개이미지1
	image* _effect1; // 번개이미지2
	image* _effect2; // 번개이미지3
	image* _effect3; // 번개이미지4

	enemyManager* _em; //애너미정보가져오기

	//함수를 선언하려면 여기에다
	//겟터와 셋터는 따로따로 밑에 다 선언 해주세요
	virtual HRESULT init(int character, bool isStart);
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void handleInput(); // 상태변환받는함수

	virtual void addImage();
	virtual void collision();
	void isStateSet();   //스테이트상태 확인 불값 -> 데미지 확인위해 by 김광수

	//수만은 겟터
	virtual image* getImage() { return _playerimg; }
	virtual RECT getRect() { return _playerrc; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual int gethp() { return _hp; }
	virtual int getlife() { return _life; }
	virtual RECT getAtkRect() { return _attack_rc; }
	virtual RECT getGripRect() { return _grip_rc; }

	//수만은 셋터
	virtual void setImage(image* img) { _playerimg = img; }

	virtual void setRect(RECT rc) { _playerrc = rc; }
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }

	virtual void setImageName(string s) { _playerImgName = s; }

	virtual void sethp(int hp) { _hp = hp; }
	virtual void setlife(int life) { _life  = life; }

	//에너미매니저와 링크
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	//그림자 중점좌표 setter, getter
	void setShadowX(float shadowX) { _shadowX = shadowX; }
	void setShadowY(float shadowY) { _shadowY = shadowY; }
	
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
};

