#pragma once
#include "gameNode.h"

class TestProj : public gameNode
{
private:
	RECT rc;

public:

	HRESULT init();
	void release();
	void update();
	void render();


	TestProj() {}
	~TestProj() {}
};

