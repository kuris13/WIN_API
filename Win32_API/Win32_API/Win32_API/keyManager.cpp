#include "setDefine.h"
#include "keyManager.h"

/*
	GetAsyncKeyState(int key)
	- 현재 키의 상태를 받아오는 함수
	- 호출되기 전에 키를 누른 상태였는지,
	 함수가 호출된 시점인 현재에도 누르고 있는 상태인지 받아온다.

	 <현재 상태가 어떤 지를 알려주는 리턴 비트>
	 0x0000 : 이전에 누른 적이 없고, 호출 시점에 안 눌린 상태
	 0x8000 : 이전에 누른 적이 없고, 호출 시점에 눌린 상태
	 0x8001 : 이전에 누른 적이 있고, 호출 시점에 눌린 상태
	 0x0001 : 이전에 누른 적이 있고, 호출 시점에 안 눌린 상태
	
	게임 프로그래밍에서는 정교한 입력이 필요하기 때문에 비트 값과 비교를 한다!
	( 이전 시점 = 이전 GetAsynckeyState호출한 후 ~ 지금 GetAsyncKeyState를 호출하기 직전 )




*/



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



void keyManager::makeEdge(RECT rc) {
	//왼쪽 위
	edge[0] = { rc.left, rc.top };
	//오른쪽 위
	edge[1] = { rc.right, rc.top };
	//왼쪽 아래
	edge[2] = { rc.left, rc.bottom };
	//오른쪽 아래 
	edge[3] = { rc.right, rc.bottom };
}

//박스가 플레어이와의 충돌 체크
//서로 겹치는 부분을 찾기
//모서리 좌표를 이용한다면, 충돌체의 크기가 너무 작을 때 충돌을 체크할 수 없음
//일단 모서리로 만들어보자
//rc 충돌체  rc2 플레이어
bool keyManager::inTheRect(RECT rc , RECT player)
{

	makeEdge(rc);
	/*
	if (rc.left < rc2.left &&
		rc.right > rc2.left &&
		rc.top < rc2.top && 
		rc.bottom > rc2.top || rc.left < rc2.right &&
		rc.right > rc2.right &&
		rc.top < rc2.top &&
		rc.bottom > rc2.top ||
		rc.left > rc2.left &&
		rc.right < rc2.right &&
		rc.top > rc2.top &&
		rc.bottom < rc2.bottom
		)
	{

		return true;
	}
	*/
	if (player.left < edge[0].x && player.right > edge[0].x &&
		player.top < edge[0].y && player.bottom > edge[0].y )
	{
		return true;
	}
	else if (player.left < edge[1].x && player.right > edge[1].x &&
		player.top < edge[1].y && player.bottom > edge[1].y)
	{
		return true;
	}
	else if (player.left < edge[2].x && player.right > edge[2].x &&
		player.top < edge[2].y && player.bottom > edge[2].y)
	{
		return true;
	}
	else if (player.left < edge[3].x && player.right > edge[3].x &&
		player.top < edge[3].y && player.bottom > edge[3].y)
	{
		return true;
	}





	return false;
}
bool keyManager::inTheMouse(RECT rc)
{

	if (rc.left < ptMouse.x && rc.right > ptMouse.x &&
		rc.top < ptMouse.y && rc.bottom > ptMouse.y)
	{

		return true;
	}

	return false;
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
