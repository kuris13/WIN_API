#include "setDefine.h"
#include "Scene_loopRender.h"

HRESULT Scene_loopRender::init()
{
	IMAGEMANAGER->addImage("노움", "Images/노움.bmp", 200, 250, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("철충", "Images/철충.bmp", 200, 200, true, RGB(0, 0, 0));

	_offsetX1 = _offsetX2 = _offsetY1 = _offsetY2 = _offsetX3 = _offsetY3 = 0;

	return S_OK;
}

void Scene_loopRender::release()
{
}

void Scene_loopRender::update()
{
	_offsetX1 += 3;	//특정 좌표 이동
	_offsetX2 += 6;	//특정 좌표 이동
	_offsetX3 -= 4;	//특정 좌표 이동
}


void Scene_loopRender::render()
{
	//루프렌더
	//loopRender(키값, DC, 화면에 그리는 크기(Rect), 가로 루프, 세로 루프)
	IMAGEMANAGER->loopRender("배경", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _offsetX1, _offsetY1);

	IMAGEMANAGER->loopRender("노움", getMemDC(),
		&RectMake(0, 400,WINSIZE_X, 250), _offsetX2, _offsetY2);

	IMAGEMANAGER->loopRender("철충", getMemDC(),
		&RectMake(0, 200, WINSIZE_X, 200), _offsetX3, _offsetY3);

}
