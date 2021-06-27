#include "stdafx.h"
#include "renderManager.h"

HRESULT renderManager::init()
{
	return S_OK;
}

void renderManager::release()
{
}

void renderManager::update()
{
	setObjArray();
	quickSort(0, _arrObj.size() - 1);
}

void renderManager::render(HDC hdc)
{
	for (int i = 0; i < _arrObj.size(); i++)
	{
		IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->frameRender(hdc, _arrObj[i].body.left, _arrObj[i].body.top, _arrObj[i].currentFrameX, _arrObj[i].currentFrameY);
		IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->render(hdc, _arrObj[i].shadow.left, _arrObj[i].shadow.top);
	}
}

void renderManager::addObj(string strKey, string bodyImageName, string shadowImageName, RECT& body, RECT& shadow, int& currentFrameX, int& currentFrameY)
{
	OBJ object;
	object.bodyImageName = bodyImageName;
	object.shadowImageName = shadowImageName;
	object.body = body;
	object.shadow = shadow;
	object.shadowX = (object.shadow.right + object.shadow.left) / 2;
	object.shadowY = (object.shadow.bottom + object.shadow.top) / 2;
	object.currentFrameX = currentFrameX;
	object.currentFrameY = currentFrameY;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));

}

void renderManager::deleteObj(string strKey, int i)
{
	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.erase(iter->second.begin()+i);
			return;
		}
	}
}

void renderManager::setObjArray()
{
	for (mapObjIter mIter = _mObjList.begin(); mIter != _mObjList.end(); mIter++)
	{
		for (iterObj vIter = mIter->second.begin(); vIter != mIter->second.end(); vIter++)
		{
			_arrObj.push_back(*vIter);
		}
	}
}

void renderManager::quickSort(int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int pivot = left;
	int i = left + 1;
	int j = right;
	OBJ temp;

	while (i <= j)
	{
		while (i <= right && _arrObj[i].shadowY <= _arrObj[pivot].shadowY) i++;
		while (j > left && _arrObj[j].shadowY >= _arrObj[pivot].shadowY) j--;

		if (i > j)
		{
			temp = _arrObj[pivot];
			_arrObj[pivot] = _arrObj[j];
			_arrObj[j] = temp;
		}
		else
		{
			temp = _arrObj[j];
			_arrObj[j] = _arrObj[i];
			_arrObj[i] = temp;
			break;
		}
	}
	quickSort(left, j - 1);
	quickSort(j + 1, right);
}


