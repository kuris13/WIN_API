#include "setDefine.h"
#include "birdScene.h"

HRESULT birdScene::init()
{
	gameStop = true;
	IMAGEMANAGER->addImage("배경2", "Images/back.bmp",WINSIZE_X*3,WINSIZE_Y);
	IMAGEMANAGER->addImage("ufo", "Images/ufo.bmp", 58, 40, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("적", "Images/enemy.bmp", 100, 100, true, RGB(255, 0, 255));

	enemy[0] = RectMakeCenter(WINSIZE_X - 150, 50, 100, 100);
	enemy[1] = RectMakeCenter(WINSIZE_X - 150, 150, 100, 100);
	enemy[2] = RectMakeCenter(WINSIZE_X - 150, WINSIZE_Y - 200, 100, 100);
	enemy[3] = RectMakeCenter(WINSIZE_X - 150, WINSIZE_Y-100, 100, 100);

	player = RectMakeCenter(200, WINSIZE_Y / 2, 58, 40);


	return S_OK;
}

void birdScene::release()
{
}

void birdScene::update()
{
	if (gameStop)
	{
		

		_offsetX1 += 3;


		RECT temp;
		for (int i = 0; i < 4; i++)
		{
			if (IntersectRect(&temp, &player, &enemy[i]))
			{
				//게임 오버 
				gameStop = false;
			}
		}
		


		//기본적으로 밑으로 떨어짐
		player.top += 2;
		player.bottom += 2;


		if (isJump)
		{
			player.top -= 5;
			player.bottom -= 5;

			if (jC == 30)
			{
				isJump = false;
				jC = 0;
			}
			++jC;
		}

		for (int i = 0; i < 4; i++)
		{
			enemy[i].left -= 6;
			enemy[i].right -= 6;

		}

		if (enemy[0].right < 0)
		{
			for (int i = 0; i < 4; i++)
			{
				enemy[i].left = WINSIZE_X;
				enemy[i].right = WINSIZE_X + 100;

			}

		}


		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			isJump = true;
			jC = 0;
		}
		

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		gameStop = true;

		player = RectMakeCenter(200, WINSIZE_Y / 2, 58, 40);
	}
}

void birdScene::render()
{
	IMAGEMANAGER->loopRender("배경2", getMemDC(),&RectMake(0,0,WINSIZE_X,WINSIZE_Y) ,_offsetX1,_offsetY1);

	IMAGEMANAGER->render("ufo", getMemDC(),player.left,player.top);

	IMAGEMANAGER->render("적", getMemDC(), enemy[0].left, enemy[0].top);
	IMAGEMANAGER->render("적", getMemDC(), enemy[1].left, enemy[1].top);
	IMAGEMANAGER->render("적", getMemDC(), enemy[2].left, enemy[2].top);
	IMAGEMANAGER->render("적", getMemDC(), enemy[3].left, enemy[3].top);

}
