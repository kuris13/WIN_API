/*
	<< GetAsyncKeyState(int key) >>
	- 현재 키 상태를 받아오는 함수
	- 호출되기 전에 키를 누른 상태였는지,
	   함수가 호출된 시점인 현재에도 누르고 있는 상태인지 받아온다.

	 <현재 상태가 어떤 지를 알려주는 리턴 비트>
	 0x0000 : 이전에 누른 적이 없고, 호출 시점에 안 눌린 상태
	 0x8000 : 이전에 누른 적이 없고, 호출 시점에 눌린 상태
	 0x8001 : 이전에 누른 적이 있고, 호출 시점에 눌린 상태
	 0x0001 : 이전에 누른 적이 있고, 호출 시점에 안 눌린 상태

	 ※ 이전 시점 : 이전 GetAsyncKeyState를 호출한 후 ~
						   지금 GetAsyncKeyState를 호출하기 직전
*/




#include "setDefine.h"
#include "keyManager.h"

//초기화
HRESULT keyManager::init()
{
	//키가 입력되지 않은 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	return S_OK;
}

bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}
	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
