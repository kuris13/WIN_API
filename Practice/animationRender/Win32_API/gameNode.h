#pragma once
#include "image.h"

static image* _backBuffer
= IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);

	virtual void release();
	virtual void update();
	virtual void render();

	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	gameNode() {}
	~gameNode() {}
};

