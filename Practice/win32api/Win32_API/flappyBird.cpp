#include "setDefine.h"
#include "flappyBird.h"



HRESULT flappyBird::init()
{
	_rcBackground = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 400, 800);

	_rcGround = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 300,400, 200);


	_bird.x = WINSIZE_X / 2 - 100;
	_bird.y = WINSIZE_Y / 2 - 80;
	_bird.speed = 4.0f;
	_bird.gravity = 0.0f;
	_bird.rc = RectMakeCenter(_bird.x, _bird.y, 50, 50);

	for (int i = 0; i < 2; i++)
	{
		_pipe[i].speed = 5.0f;

	}

	_pipe[0].rc = RectMake(WINSIZE_X - 200, -300, 100, 400);
	_pipe[1].rc = RectMake(WINSIZE_X - 200, _pipe[0].rc.bottom + 150, 100, 400);

	_score = 0;
	_isStart = false;
	_isGameover = false;


	return S_OK;
}

void flappyBird::release()
{
}

void flappyBird::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isStart = true;
		_bird.gravity = 0.0f;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _isGameover)
	{
		this->init();
	}

	_bird.rc = RectMakeCenter(_bird.x, _bird.y, 50, 50);

	this->BirdJump();
	this->collision();
	this->collision();

}

void flappyBird::render()
{
	//배경화면
	RectangleMake(getMemDC(), _rcBackground);

	for (int i = 0; i < 2; i++)
	{
		RectangleMake(getMemDC(), _pipe[i].rc);

		auto brush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(getMemDC(), &_pipe[i].rc, brush);
		DeleteObject(brush);
	}

	//바닥
	{
		RectangleMake(getMemDC(), _rcGround);
		auto brush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(getMemDC(), &_rcGround, brush);
		DeleteObject(brush);
	} 

	//새
	{
		RectangleMake(getMemDC(), _bird.rc);
		auto brush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(getMemDC(), &_bird.rc, brush);
		DeleteObject(brush);
	}

}


void flappyBird::BirdJump()
{

}

void flappyBird::collision()
{

}

void flappyBird::makePipe()
{

}
