#include "setDefine.h"
#include "Scene_shop.h"



HRESULT Scene_shop::init()
{
	//RECT �ʱ�ȭ : ���� & �κ��丮�� �Ƹ��ڸ� ���� RECT
	_inventory = RectMake(500, 100, 300, 400);
	_shopList = RectMake(100, 100, 300, 400);

	//RECT �ʱ�ȭ : ���� �Ǹ� ����Ʈ�� ����� �̹����� ���� RECT��
	_item[0] = RectMake(138, 168, 32, 30);
	_item[1] = RectMake(177, 168, 32, 30);
	_item[2] = RectMake(215, 168, 32, 30);
	_item[3] = RectMake(254, 168, 32, 30);
	_item[4] = RectMake(294, 168, 32, 30);
	_item[5] = RectMake(332, 168, 32, 30);
	_item[6] = RectMake(138, 200, 32, 30);
	_item[7] = RectMake(177, 200, 32, 30);
	_item[8] = RectMake(215, 200, 32, 30);
	_item[9] = RectMake(1254, 200, 32, 30);


	//RECT �ʱ�ȭ : ������ �̹����� ��Ƶ� �κ��丮�� RECT��
	int width = 0, height = 0;
	for (int i = 0; i < 48; i++)
	{
		_myItem[i] = RectMake(538 + (width * 39), 168 + height, 32, 30);

		++width;

		if (width == 6)
		{
			width = 0;
			height += 32;

		}
	}


	//������ �κ��丮�� ����� �̹���
	_inven = IMAGEMANAGER->addImage("�κ�", "Images/�κ�.bmp", 300, 400, true, RGB(0, 0, 0));
	_itemList = IMAGEMANAGER->addImage("����", "Images/�κ�.bmp", 300, 400, true, RGB(0, 0, 0));

	for (int i = 0; i < 10; i++)
	{
		_t[i] = new image;
	}

	//������ �̹��� �ʱ�ȭ
	_t[0] = IMAGEMANAGER->addImage("�̹���1", "Images/t1.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[1] = IMAGEMANAGER->addImage("�̹���2", "Images/t2.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[2] = IMAGEMANAGER->addImage("�̹���3", "Images/t3.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[3] = IMAGEMANAGER->addImage("�̹���4", "Images/t4.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[4] = IMAGEMANAGER->addImage("�̹���5", "Images/t5.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[5] = IMAGEMANAGER->addImage("�̹���6", "Images/t6.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[6] = IMAGEMANAGER->addImage("�̹���7", "Images/t7.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[7] = IMAGEMANAGER->addImage("�̹���8", "Images/t8.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[8] = IMAGEMANAGER->addImage("�̹���9", "Images/t9.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[9] = IMAGEMANAGER->addImage("�̹���10", "Images/t10.bmp", 32, 30, true, RGB(255, 255, 255));


	for (int i = 0; i < 10; i++)
	{
		tem[i] = new item;
		tem[i]->setImage(_t[i]);
		_shopVec.push_back(tem[i]);
	}


	return S_OK;
}

void Scene_shop::release()
{

}

void Scene_shop::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����
		for (int i = 0; i < 10; i++)
		{
			//���� �����۰� ���콺 �������� �浹 �˻�
			if (PtInRect(&_item[i], _ptMouse))
			{
				//������ ȹ��
				getItem(tem[i]);
				
				//Ȯ�ο� �޽���
				cout << "������ �����Ͽ����ϴ�." << endl;
				cout << "���� ������ ���� ���� :" <<_invenVec.size() << endl;
			}
		}

		//�κ��丮
		for (int i = 0; i < 48; i++)
		{
			//�� �κ��丮 �����۰� ���콺 �������� �浹 �˻�
			if (PtInRect(&_myItem[i], _ptMouse))
			{
				//����ó��
				if (_invenVec.size() < 1) return;
				if (i >= _invenVec.size()) return;

				_invenVec.erase(_invenVec.begin() + i);

				//Ȯ�ο� �޽��� 
				cout << "������ �Ǹ��Ͽ����ϴ�." << endl;
				cout << "���� ������ ���� ���� :" << _invenVec.size() << endl;
			}
		}



	}
}

void Scene_shop::render()
{
	IMAGEMANAGER->render("�κ�", getMemDC(), _inventory.left, _inventory.top);
	IMAGEMANAGER->render("����", getMemDC(), _shopList.left, _shopList.top);

	for (int i = 0; i < 10; i++)
	{
		_t[i]->render(getMemDC(), _item[i].left, _item[i].top);

	}

	for (int i = 0; i < _invenVec.size(); i++)
	{
		_invenVec[i]->getImage()->render(getMemDC(), _myItem[i].left, _myItem[i].top);
	}

}

void Scene_shop::getItem(item * tem)
{
	_invenVec.push_back(tem);
}

Scene_shop::Scene_shop()
{
}


Scene_shop::~Scene_shop()
{
}
