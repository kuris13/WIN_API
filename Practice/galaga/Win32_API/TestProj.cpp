#include "setDefine.h"
#include "TestProj.h"



HRESULT TestProj::init()
{
	//==============================================================================
	IMAGEMANAGER->addImage("노움", "Images/노움.bmp", 50, 65, true, RGB(0, 0, 0));

	for (int i = 0; i < 7; i++)
	{
		enemy[i].isCreated = true;
		enemy[i].rc = RectMake(1000, 10 + i * 100, 50, 65);
	}
	//==============================================================================
	

	//==============================================================================
	IMAGEMANAGER->addImage("철충", "Images/철충.bmp", 100, 100, true,RGB(0,0,0));
	player = RectMake(100, 400, 100, 100);
	//==============================================================================

	
	//==============================================================================
	IMAGEMANAGER->addImage("총알", "Images/bullet.bmp", 70, 70, true, RGB(0, 0, 0));
	
	//==============================================================================





	//==============================================================================
	IMAGEMANAGER->addImage("라오진배경", "Images/라오진배경.bmp", 1280, 720);
	background = RectMake(0, 0, 1280, 720);
	//==============================================================================

	return S_OK;
}

void TestProj::release()
{
}

void TestProj::update()
{





	for (int i = 0; i < bulletLength; i++)
	{
		if (bullet[i].isCreated)
		{
			bullet[i].rc.left += 10;
			bullet[i].rc.right += 10;

			if (bullet[i].rc.left >= WINSIZE_X)
			{
				bullet[i].isCreated = false;
			}

			RECT rcTemp;
			for (int j = 0; j <enemyLenght; j++)
			{
				if (IntersectRect(&rcTemp, &bullet[i].rc, &enemy[j].rc))
				{
					enemy[j].isCreated = false;
				}
			}
		}

	}




	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (bullet[bC].isCreated == false)
		{
			bullet[bC].isCreated = true;
			bullet[bC].rc = RectMake(player.right+20,(player.bottom + player.top)/2-40,70,70);
			bC++;

			if (bC == bulletLength) bC = 0;
					
		}
		
	}






	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player.top -= 10;
		player.bottom -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player.top += 10;
		player.bottom += 10;
	}

}

void TestProj::render()
{
	//==============================================================================
	IMAGEMANAGER->render("라오진배경", getMemDC(), background.left, background.top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), background);
	}
	//==============================================================================


	//==============================================================================
	IMAGEMANAGER->render("철충", getMemDC(), player.left, player.top);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), player);
	}
	//==============================================================================


	//==============================================================================
	for (int i = 0; i < 7; i++)
	{
		if (enemy[i].isCreated)
		{
			IMAGEMANAGER->render("노움", getMemDC(), enemy[i].rc.left, enemy[i].rc.top);
		}
	}
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < 7; i++)
		{
			RectangleMake(getMemDC(), enemy[i].rc);
		}
	}
	//==============================================================================


	//==============================================================================
	for (int i = 0; i < bulletLength; i++)
	{
		if(bullet[i].isCreated == true)
		{
			IMAGEMANAGER->render("총알", getMemDC(), bullet[i].rc.left, bullet[i].rc.top);
		}
	}

	//==============================================================================


}

TestProj::TestProj()
{
}


TestProj::~TestProj()
{
}
