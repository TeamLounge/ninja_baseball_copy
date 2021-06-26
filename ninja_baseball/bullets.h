#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//총알 이미지 
	RECT rc;				//총알 렉트
	float x, y;				//총알 좌표(실시간)
	float angle;			//총알 각도
	float radius;			//총알 반지름
	float speed;			//총알 스피드
	float fireX, fireY;		//총알 발사시 처음 좌표(발사된 좌표)
	bool isFire;			//발사됐누?
	int count;				//총알 프레임카운트용
};

//공용으로 너도 나도 쏠 총알
class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
public:
	bullet() {};
	~bullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	//총알을 지워달라고 소통하는 함수
	void removeBullet(int arrNum);

	
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};


//기존의 방식(미리 만들어두고 사용하는 미사일)
class missile : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	//사거리 용(?)

public:
	missile() {};
	~missile() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알 발사함수(생성될 좌표)
	void fire(float x, float y);
	//총알 움직여줍시다
	void move();
};

//발사할때 생성해서 쏠 미싸일
class hyunMoo : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	hyunMoo() {};
	~hyunMoo() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVHyunMoo()				{ return _vBullet; }
	vector<tagBullet>::iterator getVIHyunMoo()	{ return _viBullet; }
};