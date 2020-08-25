#include "setDefine.h"
#include "TestProj.h"

HRESULT TestProj::init()
{
	IMAGEMANAGER->addImage("테스트", "Images/발키리.bmp", 553, 390);
	rc = RectMake(128, 128, 553, 390);

	return S_OK;
}

void TestProj::release()
{
}

void TestProj::update()
{
}

void TestProj::render()
{
	IMAGEMANAGER->render("테스트", getMemDC(), rc.left, rc.top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), rc);
	}
}
