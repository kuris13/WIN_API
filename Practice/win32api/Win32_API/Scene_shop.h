#pragma once
#include "gameNode.h"
#include "item.h"

#include <array>

class Scene_shop : public gameNode
{
private:

	RECT _inventory;
	RECT _shopList;
	RECT _item[10];
	RECT _myItem[48];

	image* _inven;
	image* _itemList;
	image* _t[10];
	item* tem[10];

	array<item*,10> _invenArr;
	vector<item*> _shopVec;
	vector<item*> _invenVec;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void getItem(item* tem);



	Scene_shop();
	~Scene_shop();
};

