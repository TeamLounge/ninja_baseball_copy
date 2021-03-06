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

	//씬 두개 이상에서 쓰이는 이미지들 미리 등록
	IMAGEMANAGER->addImage("tile_background", "image/6_UI/tile_background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_green", "image/6_UI/inGame/green.bmp", 63, 72, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_red", "image/6_UI/inGame/red.bmp", 63, 72, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("yellow_0", "image/8_Dialog/yellowdialog/yellow_0.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_1", "image/8_Dialog/yellowdialog/yellow_1.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_2", "image/8_Dialog/yellowdialog/yellow_2.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_3", "image/8_Dialog/yellowdialog/yellow_3.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_4", "image/8_Dialog/yellowdialog/yellow_4.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_5", "image/8_Dialog/yellowdialog/yellow_5.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_6", "image/8_Dialog/yellowdialog/yellow_6.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_7", "image/8_Dialog/yellowdialog/yellow_7.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_8", "image/8_Dialog/yellowdialog/yellow_8.bmp", 24, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellow_9", "image/8_Dialog/yellowdialog/yellow_9.bmp", 24, 24, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->addImage("timer_0", "image/6_UI/inGame/time_0.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_1", "image/6_UI/inGame/time_1.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_2", "image/6_UI/inGame/time_2.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_3", "image/6_UI/inGame/time_3.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_4", "image/6_UI/inGame/time_4.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_5", "image/6_UI/inGame/time_5.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_6", "image/6_UI/inGame/time_6.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_7", "image/6_UI/inGame/time_7.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_8", "image/6_UI/inGame/time_8.bmp", 45, 45, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("timer_9", "image/6_UI/inGame/time_9.bmp", 45, 45, true, RGB(255, 0, 255), false);

	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("start", new startScene);
	SCENEMANAGER->addScene("playerSelect", new playerSelectScene);
	SCENEMANAGER->addScene("stage1", new stageScene1);
	SCENEMANAGER->addScene("stage2", new stageScene2);
	SCENEMANAGER->addScene("stage3", new stageScene3);
	SCENEMANAGER->addScene("ending", new endingScene);

	SCENEMANAGER->changeScene("title");

	setMusic();

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
	
	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	HPEN myPen = (HPEN)CreatePen(1, 2, RGB(255, 0, 0));
	SelectObject(getMemDC(), myPen);

	SCENEMANAGER->render();

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myPen);
	DeleteObject(myBrush);
	//==================================================
	//여기도 건들지마라
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
	//this->getBackBuffer()->render(getHDC(), 0, 0);
}

void playGround::setMusic()
{
	SOUNDMANAGER->addSound("캐릭터선택", "music/01_Player Select.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지1", "music/02_Stage 1 In Seattle.mp3", true, true);
	SOUNDMANAGER->addSound("보스씬", "music/03_Boss Theme.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지클리어", "music/04_Stage Clear!.mp3", true, false);
	SOUNDMANAGER->addSound("스토리씬", "music/05_Story Sequence.mp3", true, true);
	SOUNDMANAGER->addSound("continue", "music/19_Continue.mp3", true, true);
	SOUNDMANAGER->addSound("gameOver", "music/20_Game Over.mp3", true, false);
	SOUNDMANAGER->addSound("보스등장", "music/24_Boss Enter.mp3", true, false);

}
