#include "setDefine.h"
#include "Scene_shop.h"



HRESULT Scene_shop::init()
{
	//RECT 초기화 : 상점 & 인벤토리용 아마자를 씌울 RECT
	_inventory = RectMake(500, 100, 300, 400);
	_shopList = RectMake(100, 100, 300, 400);

	//RECT 초기화 : 상점 판매 리스트에 사용할 이미지를 씌우 RECT들
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


	//RECT 초기화 : 아이템 이미지를 담아둘 인벤토리의 RECT들
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


	//상점과 인벤토리에 사용할 이미지
	_inven = IMAGEMANAGER->addImage("인벤", "Images/인벤.bmp", 300, 400, true, RGB(0, 0, 0));
	_itemList = IMAGEMANAGER->addImage("상점", "Images/인벤.bmp", 300, 400, true, RGB(0, 0, 0));

	for (int i = 0; i < 10; i++)
	{
		_t[i] = new image;
	}

	//아이템 이미지 초기화
	_t[0] = IMAGEMANAGER->addImage("이미지1", "Images/t1.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[1] = IMAGEMANAGER->addImage("이미지2", "Images/t2.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[2] = IMAGEMANAGER->addImage("이미지3", "Images/t3.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[3] = IMAGEMANAGER->addImage("이미지4", "Images/t4.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[4] = IMAGEMANAGER->addImage("이미지5", "Images/t5.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[5] = IMAGEMANAGER->addImage("이미지6", "Images/t6.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[6] = IMAGEMANAGER->addImage("이미지7", "Images/t7.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[7] = IMAGEMANAGER->addImage("이미지8", "Images/t8.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[8] = IMAGEMANAGER->addImage("이미지9", "Images/t9.bmp", 32, 30, true, RGB(255, 255, 255));
	_t[9] = IMAGEMANAGER->addImage("이미지10", "Images/t10.bmp", 32, 30, true, RGB(255, 255, 255));


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
		//상점
		for (int i = 0; i < 10; i++)
		{
			//상점 아이템과 마우스 포인터의 충돌 검사
			if (PtInRect(&_item[i], _ptMouse))
			{
				//아이템 획득
				getItem(tem[i]);
				
				//확인용 메시지
				cout << "물건을 구매하였습니다." << endl;
				cout << "현재 아이템 보유 수량 :" <<_invenVec.size() << endl;
			}
		}

		//인벤토리
		for (int i = 0; i < 48; i++)
		{
			//내 인벤토리 아이템과 마우스 포인터의 충돌 검사
			if (PtInRect(&_myItem[i], _ptMouse))
			{
				//예외처리
				if (_invenVec.size() < 1) return;
				if (i >= _invenVec.size()) return;

				_invenVec.erase(_invenVec.begin() + i);

				//확인용 메시지 
				cout << "물건을 판매하였습니다." << endl;
				cout << "현재 아이템 보유 수량 :" << _invenVec.size() << endl;
			}
		}



	}
}

void Scene_shop::render()
{
	IMAGEMANAGER->render("인벤", getMemDC(), _inventory.left, _inventory.top);
	IMAGEMANAGER->render("상점", getMemDC(), _shopList.left, _shopList.top);

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
