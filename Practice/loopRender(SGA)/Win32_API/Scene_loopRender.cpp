#include "setDefine.h"
#include "Scene_loopRender.h"

HRESULT Scene_loopRender::init()
{
	IMAGEMANAGER->addImage("���", "Images/���.bmp", 200, 250, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ö��", "Images/ö��.bmp", 200, 200, true, RGB(0, 0, 0));

	_offsetX1 = _offsetX2 = _offsetY1 = _offsetY2 = _offsetX3 = _offsetY3 = 0;

	return S_OK;
}

void Scene_loopRender::release()
{
}

void Scene_loopRender::update()
{
	_offsetX1 += 3;	//Ư�� ��ǥ �̵�
	_offsetX2 += 6;	//Ư�� ��ǥ �̵�
	_offsetX3 -= 4;	//Ư�� ��ǥ �̵�
}

void Scene_loopRender::render()
{
	//��������
	//loopRender(Ű��, DC, ȭ�鿡 �׸��� ũ��(Rect), ���� ����, ���� ����)
	IMAGEMANAGER->loopRender("���", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _offsetX1, _offsetY1);

	IMAGEMANAGER->loopRender("���", getMemDC(),
		&RectMake(0, 400,WINSIZE_X, 250), _offsetX2, _offsetY2);

	IMAGEMANAGER->loopRender("ö��", getMemDC(),
		&RectMake(0, 200, WINSIZE_X, 200), _offsetX3, _offsetY3);

}
