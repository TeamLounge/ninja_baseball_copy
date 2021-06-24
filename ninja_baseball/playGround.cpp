#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	//상속해서 다르게 하실수 있으니까
	//만약 상속을하셨다면 다르게 new할당을 해주시면 됩니다.
	// player = new (상속한 클래스);




	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	
	


}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	TIMEMANAGER->render(getMemDC());

	
	//==================================================
	//여기도 건들지마라
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
