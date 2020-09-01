#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;				//게이지용 RECT
	int _x, _y;						//좌표
	float  _width, _height;			//가로세로 크기

	image* _progressBarFront;		//앞에 위치할 이미지
	image* _progressBarBack;		//뒤에 위치할 이미지


public:
	HRESULT init(char* frontImageKey, char* backImageKey, int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentValue, float maxValue);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rcProgress; }
};

