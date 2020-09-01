#include "setDefine.h"
#include "progressBar.h"




HRESULT progressBar::init(char* frontImageKey, char* backImageKey, int x, int y, int width, int height)
{
	//�������� x, y��ǥ (������)
	_x = x;
	_y = y;

	//�������� ���μ��� ����
	_width = width;
	_height = height;

	//�� ���� �������� RECT ������ ����
	_rcProgress = RectMake(x, y, width, height);

	//=================================================

	//char �迭 
	char frontImage[128];
	char backImage[128];

	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));

	sprintf_s(frontImage, "%s.bmp", frontImageKey);
	sprintf_s(backImage, "%s.bmp", backImageKey);

	_progressBarFront =
		IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack =
		IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));



	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render()
{
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y);
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,0,0,_width,_progressBarFront->getHeight());


}

void progressBar::setGauge(float currentValue, float maxValue)
{
	if (currentValue > maxValue)
	{
		_width = _progressBarBack->getWidth();
	}
	else
	{
		_width = (currentValue / maxValue) * _progressBarBack->getWidth();
	}

}
