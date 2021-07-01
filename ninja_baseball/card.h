#pragma once
#include "gameNode.h"
#include "cardState.h"
#include <vector>

/////////////////////////////
//     카드 구조체
////////////////////////////
struct CARD
{
	RECT rc;
	float x, y;
	image* img;
};

/////////////////////////
//    그림자 구조체
/////////////////////////
struct CARDSHADOW
{
	RECT rc;
	float x, y;
	image* img;
};


/////////////////////////
//    총알 구조체
/////////////////////////
struct tagPunchBullet
{
	RECT rc;
	float x, y;
	float fireX, fireY;
	image* img;
	bool isFire;
	float speed;
	float angle;
	float range;
	int count;
	int currentFrameX, currentFrameY;
};

class card : public gameNode
{
private:
	
public:
	vector<tagPunchBullet>				 _vPunchBullet;
	vector<tagPunchBullet>::iterator	 _viPunchBullet;
	cardState* _cardState;
	CARDSHADOW _cardShadow;
	CARD _card;

	void InputHandle();

	/////////////////////////////
	//    ## 피격용 렉트 ##     //
	////////////////////////////
	RECT _assultedRect;

	string _imageName;

	//중력
	float _gravity, _jumpPower;
	//무브 속도
	float _speed;
	//점프중인지, 공격받았는지, 공격중인지 등등 불값 적용들
	bool _isJump, _isLeft, _isDamaged, _isUpper, _isApex;
	//벽에 닿았는지 확인
	bool _isRightWall, _isLeftWall, _isTopWall, _isBottomWall;
	//Dash 어택인지 주먹발사 어택인지 확인용
	bool _isDash, _isPunchBullet;
	//플레이어의 센터 X와 센터Y를 받아오려고 만들었음.
	float _rpX, _rpY;
	//펀치 뷸렛 상태인지 프레임이 1에 왔는지 확인하고 총알을 발사하기 위한 방법
	bool _isFire;
	//공격용 렉트
	RECT _atkRc;
	//현재 프레임 번호 변수(스테이트)
	int _currentFrameX, _currentFrameY;
	//현재 프레임 번호 변수(총알)
	int _bulletFrameX, _bulletFrameY;
	//총알 몇번 쐈는지 카운트하는거
	int _bulletCount;
	int _bulletMax;
	float _range;
	//공격패턴을 넣기위한 작업
	int numPattern;
	bool _isCrash;
	//각종 상태 boo값 넣기
	bool _isCardSmallDamagedState, _isCardSmallDamaged;
	bool _isCardHeavyDamagedState, _isCardHeavyDamaged;
	bool _isCardDeathState, _isCardDeath;



	bool isattack;              //에너미가 공격했어??
	bool isdamage;				//에너미가 데미지 받았어??							
	bool iscatch;				//에저미가 잡혔어??

	card();
	~card();

	virtual HRESULT init();	
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();	

	void setImage();
	void setCard();
	void setCardShadow();
	void getGravity();

	////////////////////////////
	//   총알 발사 함수
	///////////////////////////
	void setBullet(int bulletMax, float range);
	void updateBullet();
	void renderBullet();
	void fireBullet(float x, float y, float angle);
	void moveBullet();

	//세터 함수
	void setIsUpper(bool isUpper) { _isUpper = isUpper; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsDash(bool isDash) { _isDash = isDash; }
	void setIsBullet(bool isPunchBullet) { _isPunchBullet = isPunchBullet; }
	void setIsDamaged(bool isDamaged) { _isDamaged = isDamaged; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	void setIsFire(bool isFire) { _isFire = isFire; }

	//게터 설정
	RECT getCardRc() { return _card.rc; }
	RECT getAtkCardRc() { return _atkRc; }
	float getCenterX() { return (_card.rc.left + _card.rc.right) / 2; }
	float getCenterY() { return (_card.rc.top + _card.rc.bottom) / 2; }
	bool getIsUpper() { return _isUpper; }
	bool getIsLeft() { return _isLeft; }
	bool getIsDash() { return _isDash; }
	bool getIsBullet() { return _isPunchBullet; }
	bool getIsFire() { return _isFire; }
};