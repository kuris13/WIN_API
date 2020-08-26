#include "setDefine.h"
#include "p_Scene.h"



HRESULT p_Scene::init()
{
	//이미지 추가
	 _ball = IMAGEMANAGER->addImage("공", "Images/bigball.bmp", 60, 60, true, RGB(255, 0, 255));
	 _mountain = IMAGEMANAGER->addImage("산", "Images/mountain.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	_probeY = _y + _ball->getHeight() / 2;



	return S_OK;
}

void p_Scene::release()
{
}

void p_Scene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	_probeY = _y + _ball->getHeight() / 2;

	//픽셀 충돌
	for (int i = _probeY - 300; i < _probeY + 300; i++)
	{
		//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
		auto color = GetPixel(_mountain->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//이미지 끼리 닿인 부분이 마젠타 색상이 아닐 경우
		if (!(r == 255 & g == 0 & b == 255))
		{
			//대상 이미지의 가장 겉의 라인을 따라가면서 움직일 수 있도록
			_y = i - _ball->getHeight() / 2;
			break;
		}



	}

}

void p_Scene::render()
{
	_mountain->render(getMemDC());
	_ball->render(getMemDC(), _rc.left, _rc.top);

}

p_Scene::p_Scene()
{
}


p_Scene::~p_Scene()
{
}
