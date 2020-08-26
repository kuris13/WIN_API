#pragma once
#include "gameNode.h"
class p_Scene : public gameNode
{
private:
	RECT _rc;
	RECT _rc1;

	image* _mountain;
	image* _ball;

	float _x, _y;
	int _probeY;



public:

	HRESULT init();
	void release();
	void update();
	void render();


	p_Scene();
	~p_Scene();
};

