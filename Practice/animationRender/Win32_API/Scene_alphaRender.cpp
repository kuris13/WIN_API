#include "setDefine.h"
#include "Scene_alphaRender.h"

HRESULT Scene_alphaRender::init()
{
	//��� �̹���
	IMAGEMANAGER->addImage("���", "Images/���.bmp", 1280, 820);

	//���ĺ��� �̹���
	IMAGEMANAGER->addImage("ĳ��", "Images/��Ű��.bmp", 553, 390, true, RGB(255, 255, 255));

	_alpha = 255;

	return S_OK;
}

void Scene_alphaRender::release()
{
}

void Scene_alphaRender::update()
{
	_alpha -= 3.0f;

	if (_alpha <= 0)
	{
		_alpha = 255;
	}
}

void Scene_alphaRender::render()
{
	//normal render
	//render(addImage�� �� ������ key, ����� DC(ȭ��))
	//render(addImage�� �� ������ key, ����� DC(ȭ��),\
					�̹����� ��� ���� X��ǥ, �̹����� ��� ���� Y��ǥ)
	IMAGEMANAGER->render("���", getMemDC());

	//alpha render
	//alphaRender(key��, ����� DC,	�̹����� ��� ���� X��ǥ, �̹����� ��� ���� Y��ǥ, ����)
	IMAGEMANAGER->alphaRender("ĳ��", getMemDC(), 320, 240, _alpha);
}
