#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;				//�������� RECT
	int _x, _y;						//��ǥ
	float  _width, _height;			//���μ��� ũ��

	image* _progressBarFront;		//�տ� ��ġ�� �̹���
	image* _progressBarBack;		//�ڿ� ��ġ�� �̹���


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

