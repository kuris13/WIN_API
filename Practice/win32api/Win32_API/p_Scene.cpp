#include "setDefine.h"
#include "p_Scene.h"



HRESULT p_Scene::init()
{
	//�̹��� �߰�
	 _ball = IMAGEMANAGER->addImage("��", "Images/bigball.bmp", 60, 60, true, RGB(255, 0, 255));
	 _mountain = IMAGEMANAGER->addImage("��", "Images/mountain.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

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

	//�ȼ� �浹
	for (int i = _probeY - 300; i < _probeY + 300; i++)
	{
		//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
		auto color = GetPixel(_mountain->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//�̹��� ���� ���� �κ��� ����Ÿ ������ �ƴ� ���
		if (!(r == 255 & g == 0 & b == 255))
		{
			//��� �̹����� ���� ���� ������ ���󰡸鼭 ������ �� �ֵ���
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
