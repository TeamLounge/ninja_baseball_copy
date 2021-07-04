#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class renderManager : public singletonBase<renderManager>
{
private:
	typedef struct tagObj
	{
		const char* bodyImageName;
		const char* shadowImageName;
		int *currentFrameX;
		int *currentFrameY;
		float* shadowX;
		float* shadowY;
		float* bodyX;
		float *bodyY;
		bool isNotHaveCurrentFrame;
		bool isFrameImage;
		bool isAlphaBlend;
		int* alpha;
	}OBJ; //렌더할 객체 정보

	typedef vector<OBJ>						arrObj;
	typedef vector<OBJ>::iterator			iterObj;
	typedef map<string, arrObj>				mapObjList;
	typedef map<string, arrObj>::iterator	mapObjIter;

private:
	mapObjList _mObjList; //오브젝터 맵

	arrObj _arrObj; //오브젝트 정렬용 벡터
public :

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//====================오브젝트 추가==============================

	//============currentFrameX, currentFrameY가 없는 경우===========
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, bool isFrameImage);
	//투명값 있는 경우
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, bool isFrameImage, int* alphaBlend);
	//==============================================================

	//============currentFrameX, currentFrameY가 있는 경우===========
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, int* currentFrameX, int* currentFrameY);
	//투명값 있는 경우
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, int* currentFrameX, int* currentFrameY, int* alphaBlend);
	//==============================================================
	//==============================================================

	//특정 오브젝트 삭제
	bool deleteObj(string strKey, int i);

	//맵의 오브젝트들 정렬하기 위해 한 벡터에 담음
	void setObjArray();

	//오브젝트 정렬
	void quickSort(int left, int right);

	//모든 오브젝트 삭제
	bool deleteAll();
};

