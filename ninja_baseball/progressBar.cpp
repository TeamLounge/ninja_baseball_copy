#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y, const char* topImageAddress, const char* bottomImageAddress, int width, int height)
{
	_x = x;
	_y = y;
	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = new image;
	_progressBarBottom = new image;

	_progressBarTop->init(topImageAddress, width, height, true, RGB(255, 0, 255));
	_progressBarBottom->init(bottomImageAddress, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMake(_x, _y, _progressBarTop->getWidth(),
		_progressBarTop->getHeight());
}


void progressBar::render()
{
	_progressBarBottom->render(getMemDC(),
		_rcProgress.left,
		_y, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	//��� ������ ũ�Ⱑ �����Ǿ���ϱ⶧���� ����ũ��(sourWidth)�� _width ���� ����
	_progressBarTop->render(getMemDC(),
		_rcProgress.left,
		_y, 0, 0,
		_width, _progressBarBottom->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
