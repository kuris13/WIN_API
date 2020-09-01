#pragma once
#include "gameNode.h"
class popolScene : public gameNode
{
private:
	image* player;
	RECT rc;

	int state = 0;
	int idleState = 0;
public:

	HRESULT init();
	void release();
	void update();
	void render();


};

