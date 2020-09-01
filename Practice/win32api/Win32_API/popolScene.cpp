#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	IMAGEMANAGER->addImage("���2", "Images/back.bmp", WINSIZE_X * 3, WINSIZE_Y);

	IMAGEMANAGER->addFrameImage("���", "Images/idle.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 360, 80, 4, 1, true, RGB(255, 0, 254));


	player = IMAGEMANAGER->findImage("���");

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 90, 80);

	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += 5;
		rc.right += 5;

		state = 1;

		player->setFrameX(0);
	}

	//��� ���¶��
	if (state == 0)
	{
		player->setFrameX(idleState++ / 20);
	}

	if (idleState > 80)
	{
		idleState = 0;
	}


	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		state = 0;
		
	}

}

void popolScene::render()
{
	IMAGEMANAGER->render("���2", getMemDC());

	IMAGEMANAGER->frameRender("���", getMemDC(), rc.left, rc.top);
}
