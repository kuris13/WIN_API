#include "setDefine.h"
#include "Scene_galaga.h"

HRESULT Scene_galaga::init()
{
	//적 정보
	for (int i = 0; i < _ENEMY; i++)
	{
		enemy[i].img = new image;
		enemy[i].img->init("Images/galaga.bmp", 50, 50, RGB(255, 0, 255));
		enemy[i].rc = RectMakeCenter(
			(i % 10) * 50 + 50, (i / 10) * 70 + 50, 50, 50);
		enemy[i]._isDead = true;
	}

	//탄환
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].img = new image;
		bullet[i].img->init("Images/galaga.bmp", 24, 24, RGB(255, 0, 255));
		bullet[i]._isFire = false;
	}

	//플레이어
	playerImage = new image;
	playerImage->init("Images/galaga.bmp", 48, 48, RGB(255, 0, 255));
	player = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 256, 48, 48);

	return S_OK;
}

void Scene_galaga::release()
{
}

void Scene_galaga::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player.left -= 5;
		player.right -= 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player.left += 5;
		player.right += 5;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		this->isFired();
	}

	//==================================================

	//몬스터를 좌우로 움직이게 한다 (충돌판정)
	for (int i = 0; i < _ENEMY; i++)
	{
		//적들이 화면 밖을 벗어나지 않도록
		if (enemy[i].rc.right > WINSIZE_X)
		{
			_isOver = false;
		}

		if (enemy[i].rc.left < 0)
		{
			_isOver = true;
		}
	}

	//몬스터를 좌우로 움직이게 한다 (좌표이동)
	for (int i = 0; i < _ENEMY; i++)
	{
		//적이 죽지 않았으면?
		if (!enemy[i]._isDead) continue;

		//적이 무사하면 무한반복
		_isOver == true ? enemy[i].rc.left += 3 : enemy[i].rc.left -= 3;
		_isOver == true ? enemy[i].rc.right += 3 : enemy[i].rc.right -= 3;
	}

	//이동에 관련된 함수 상시호출
	Movement();
}

void Scene_galaga::render()
{
	//몬스터 render
	for (int i = 0; i < _ENEMY; i++)
	{
		if (!enemy[i]._isDead) continue;
		
		enemy[i].img->render(getMemDC(), enemy[i].rc.left, enemy[i].rc.top);
	}

	//탄환 render
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullet[i]._isFire) continue;

		RectangleMake(getMemDC(), bullet[i].rc);
		bullet[i].img->render(getMemDC(), bullet[i].rc.left, bullet[i].rc.top);
	}

	//player
	playerImage->render(getMemDC(), player.left, player.top);
}

void Scene_galaga::isFired()
{
	//스페이스바 입력에 따라 탄 발사
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i]._isFire) continue;

		bullet[i].rc = RectMakeCenter(player.left + 20, player.top - 5, 10, 10);
		bullet[i]._isFire = true;

		break;
	}
}

void Scene_galaga::Movement()
{
	//충돌 판정
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullet[i]._isFire) continue;

		for (int j = 0; j < _ENEMY; j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &bullet[i].rc, &enemy[j].rc))
			{
				enemy[j]._isDead = false;
				enemy[j].rc.top -= 9999;
				enemy[j].rc.bottom -= 9999;
				bullet[i]._isFire = false;
			}
		}
	}

	//탄 이동
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullet[i]._isFire) continue;
		bullet[i].rc.top -= 10;
		bullet[i].rc.bottom -= 10;
	}
}
