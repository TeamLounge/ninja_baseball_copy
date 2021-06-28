#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class renderManager : public singletonBase<imageManager>
{
private:
	typedef struct tagObj
	{
		string bodyImageName;
		string shadowImageName;
		RECT body; //��ü
		RECT shadow; //�׸���
		int currentFrameX, currentFrameY;
		float shadowX, shadowY;
		bool isHaveRect;
	}OBJ;

	typedef vector<OBJ>						arrObj;
	typedef vector<OBJ>::iterator			iterObj;
	typedef map<string, arrObj>				mapObjList;
	typedef map<string, arrObj>::iterator	mapObjIter;

private:
	mapObjList _mObjList; //�������� ��

	arrObj _arrObj; //������Ʈ ���Ŀ� ����
public :

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObj(string strKey, string bodyImageName, string shadowImageName);

	void addObj(string strKey, string bodyImageName, string shadowImageName, RECT& body, RECT& shadow, int& currentFrameX, int& currentFrameY);

	void deleteObj(string strKey, int i);

	void setObjArray();

	void quickSort(int left, int right);
};

