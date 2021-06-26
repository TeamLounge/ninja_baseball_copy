#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* Bulletimg;	//총알 이미지
	RECT rc;			//총알 렉트
	float x, y;			//총알 좌표(실시간)
	float angle;		//총알 각도
	float speed;		//총알 스피드
	float fireX, fireY;	//총알 발사 좌표
	bool isFire;		//발사 여부
};

class punchBullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;		//이미지 불러올 이름
	float _range;				//사거리
	int _bulletMax;				//총알 최대갯수

public:
	punchBullet() {};
	~punchBullet() {};
	
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed);

	void move();
};

