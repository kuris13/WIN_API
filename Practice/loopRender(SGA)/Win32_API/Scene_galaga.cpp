#include "setDefine.h"
#include "Scene_galaga.h"

HRESULT Scene_galaga::init()
{
	//�� ����
	for (int i = 0; i < _ENEMY; i++)
	{
		enemy[i].img = new image;
		enemy[i].img->init("Images/galaga.bmp", 50, 50, RGB(255, 0, 255));
		enemy[i].rc = RectMakeCenter(
			(i % 10) * 50 + 50, (i / 10) * 70 + 50, 50, 50);
		enemy[i]._isDead = true;
	}

	//źȯ
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].img = new image;
		bullet[i].img->init("Images/galaga.bmp", 24, 24, RGB(255, 0, 255));
		bullet[i]._isFire = false;
	}

	//�÷��̾�
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

	//���͸� �¿�� �����̰� �Ѵ� (�浹����)
	for (int i = 0; i < _ENEMY; i++)
	{
		//������ ȭ�� ���� ����� �ʵ���
		if (enemy[i].rc.right > WINSIZE_X)
		{
			_isOver = false;
		}

		if (enemy[i].rc.left < 0)
		{
			_isOver = true;
		}
	}

	//���͸� �¿�� �����̰� �Ѵ� (��ǥ�̵�)
	for (int i = 0; i < _ENEMY; i++)
	{
		//���� ���� �ʾ�����?
		if (!enemy[i]._isDead) continue;

		//���� �����ϸ� ���ѹݺ�
		_isOver == true ? enemy[i].rc.left += 3 : enemy[i].rc.left -= 3;
		_isOver == true ? enemy[i].rc.right += 3 : enemy[i].rc.right -= 3;
	}

	//�̵��� ���õ� �Լ� ���ȣ��
	Movement();
}

void Scene_galaga::render()
{
	//���� render
	for (int i = 0; i < _ENEMY; i++)
	{
		if (!enemy[i]._isDead) continue;
		
		enemy[i].img->render(getMemDC(), enemy[i].rc.left, enemy[i].rc.top);
	}

	//źȯ render
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
	//�����̽��� �Է¿� ���� ź �߻�
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
	//�浹 ����
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

	//ź �̵�
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullet[i]._isFire) continue;
		bullet[i].rc.top -= 10;
		bullet[i].rc.bottom -= 10;
	}
}
