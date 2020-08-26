#include "setDefine.h"
#include "Scene_animation.h"



HRESULT Scene_animation::init()
{
	//��������Ʈ ��Ʈ �̹��� �߰�
	//450 , 256 -> bmp���� ũ��
	//9 ,4 ���� � ���� ����� 
	IMAGEMANAGER->addFrameImage("ĳ����", "Images/woman.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 450, 256, 9, 4, true, RGB(0, 0, 0));

	//�̹����� ��ü�� �Ҵ�
	player = IMAGEMANAGER->findImage("ĳ����");

	//�̹����� �� ���� RECT �ʱ�ȭ
	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 50, 64);

	//ī���� ���� �ʱ�ȭ
	_count = _index = 0;

	//ĳ���� �������� �Ǵ��ϴ� bool ����
	_isStop = false;

	return S_OK;
}

void Scene_animation::release()
{
}

void Scene_animation::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 5;
		rc.right -= 5;
		_isStop = false;

		player->setFrameY(1);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += 5;
		rc.right += 5;
		_isStop = false;

		player->setFrameY(2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 5;
		rc.bottom -= 5;
		_isStop = false;

		player->setFrameY(3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 5;
		rc.bottom += 5;
		_isStop = false;

		player->setFrameY(0);
	}

	//�ִϸ��̼� ���
	{
		_count++;

		if (_count % 5 == 0)
		{
			//ĳ���Ͱ� ������ ��� ���� ó���� ��ġ�� ��������Ʈ�� ��� (���� ���)
			if (_isStop)
			{
				player->setFrameX(0);
				return;
			}

			//�׷��� ���� ��� �ִϸ��̼� ���
			if (_index > 9) _index = 0;

			//setFrame�� ���� _index���� �޾ƿ´�.
			player->setFrameX(_index);
			_index++;
		}
	}

	//����Ű �Է��� �� ���� ���� �������� ������ ���ߵ���
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_isStop = true;
		player->setFrameX(0);
	}
}

void Scene_animation::render()
{
	//���
	IMAGEMANAGER->frameRender("ĳ����", getMemDC(), rc.left, rc.top);

	//����׿� �ڽ� ON/OFF
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), rc);
	}
}

Scene_animation::Scene_animation()
{
}


Scene_animation::~Scene_animation()
{
}
