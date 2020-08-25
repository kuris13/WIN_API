#include "setDefine.h"
#include "Scene_alphaRender.h"

HRESULT Scene_alphaRender::init()
{
	//배경 이미지
	IMAGEMANAGER->addImage("배경", "Images/배경.bmp", 1280, 820);

	//알파블렌드 이미지
	IMAGEMANAGER->addImage("캐릭", "Images/발키리.bmp", 553, 390, true, RGB(255, 255, 255));

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
	//render(addImage할 때 지정한 key, 출력할 DC(화면))
	//render(addImage할 때 지정한 key, 출력할 DC(화면),\
					이미지의 출력 시작 X좌표, 이미지의 출력 시작 Y좌표)
	IMAGEMANAGER->render("배경", getMemDC());

	//alpha render
	//alphaRender(key값, 출력할 DC,	이미지의 출력 시작 X좌표, 이미지의 출력 시작 Y좌표, 투명도)
	IMAGEMANAGER->alphaRender("캐릭", getMemDC(), 320, 240, _alpha);
}
