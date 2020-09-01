#include "setDefine.h"
#include "birdScene.h"



HRESULT birdScene::init()
{
	gameStop = true;
	IMAGEMANAGER->addImage("배경2", "Images/back.bmp",WINSIZE_X*3,WINSIZE_Y);
	IMAGEMANAGER->addImage("ufo", "Images/ufo.bmp", 58, 40, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("적", "Images/enemy.bmp", 100, 100, true, RGB(255, 0, 255));

	
	gameInit();

	return S_OK;
}

void birdScene::gameInit()
{

	score = 0;
	enemy[0] = RectMakeCenter(WINSIZE_X - 150, 50, 100, 100);
	enemy[1] = RectMakeCenter(WINSIZE_X - 150, 150, 100, 100);
	enemy[2] = RectMakeCenter(WINSIZE_X - 150, 250, 100, 100);

	enemy[3] = RectMakeCenter(WINSIZE_X - 150, 350, 100, 100);
	enemy[4] = RectMakeCenter(WINSIZE_X - 150, 450, 100, 100);
	enemy[5] = RectMakeCenter(WINSIZE_X - 150, 550, 100, 100);
	enemy[6] = RectMakeCenter(WINSIZE_X - 150, 650, 100, 100);

	player = RectMakeCenter(200, WINSIZE_Y / 2, 58, 40);

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
		for (int i = 0; i < 7; i++)
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


		for (int i = 0; i < 7; i++)
		{
			if (i == randEnemy || i == randEnemy + 1) continue;
			enemy[i].left -= 6;
			enemy[i].right -= 6;

		}

		if (enemy[0].right < 0)
		{
			for (int i = 0; i < 7; i++)
			{
				enemy[i].left = WINSIZE_X;
				enemy[i].right = WINSIZE_X + 100;

				
				randEnemy = RND->getFromIntTo(1, 5);
			}
			++score;
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
		gameInit();
	}
}

void birdScene::render()
{
	IMAGEMANAGER->loopRender("배경2", getMemDC(),&RectMake(0,0,WINSIZE_X,WINSIZE_Y) ,_offsetX1,_offsetY1);

	IMAGEMANAGER->render("ufo", getMemDC(),player.left,player.top);


	for (int i = 0; i < 7; i++)
	{

		if (i == randEnemy || i == randEnemy + 1) continue;
		IMAGEMANAGER->render("적", getMemDC(), enemy[i].left, enemy[i].top);
	}

	
	wsprintf(str,"scroe : %d",score);
	wsprintf(str2, "다시 하실려면 위쪽 화살표를 눌러주세요");


	TextOut(getMemDC(), WINSIZE_X - 200, 50, str, strlen(str));

	if (gameStop == false)
	{
		TextOut(getMemDC(), WINSIZE_X/2, WINSIZE_Y /2, str2, strlen(str2));
	}

}
