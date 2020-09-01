#pragma once
#include "singletonBase.h"
class cameraManager :public singletonBase<cameraManager>
{
private:
	POINT p = { 0,0 };
	

public:
	void setCamera(RECT &rc);
	POINT CameraPoint();

	cameraManager();
	~cameraManager();
};

