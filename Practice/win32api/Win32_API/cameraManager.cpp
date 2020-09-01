#include "setDefine.h"
#include "cameraManager.h"



void cameraManager::setCamera(RECT &rc)
{
	p.x = rc.left;
	p.y = rc.top;
}

POINT cameraManager::CameraPoint()
{

	return { p.x,p.y };
}

cameraManager::cameraManager()
{
}


cameraManager::~cameraManager()
{
}
