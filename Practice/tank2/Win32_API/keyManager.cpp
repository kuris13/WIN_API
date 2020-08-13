#include "setDefine.h"
#include "keyManager.h"

/*
	GetAsyncKeyState(int key)
	- ���� Ű�� ���¸� �޾ƿ��� �Լ�
	- ȣ��Ǳ� ���� Ű�� ���� ���¿�����,
	 �Լ��� ȣ��� ������ ���翡�� ������ �ִ� �������� �޾ƿ´�.

	 <���� ���°� � ���� �˷��ִ� ���� ��Ʈ>
	 0x0000 : ������ ���� ���� ����, ȣ�� ������ �� ���� ����
	 0x8000 : ������ ���� ���� ����, ȣ�� ������ ���� ����
	 0x8001 : ������ ���� ���� �ְ�, ȣ�� ������ ���� ����
	 0x0001 : ������ ���� ���� �ְ�, ȣ�� ������ �� ���� ����
	
	���� ���α׷��ֿ����� ������ �Է��� �ʿ��ϱ� ������ ��Ʈ ���� �񱳸� �Ѵ�!
	( ���� ���� = ���� GetAsynckeyStateȣ���� �� ~ ���� GetAsyncKeyState�� ȣ���ϱ� ���� )




*/



//�ʱ�ȭ
HRESULT keyManager::init()
{
	//Ű�� �Էµ��� ���� ���·� �ʱ�ȭ
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	return S_OK;
}



void keyManager::makeEdge(RECT rc) {
	//���� ��
	edge[0] = { rc.left, rc.top };
	//������ ��
	edge[1] = { rc.right, rc.top };
	//���� �Ʒ�
	edge[2] = { rc.left, rc.bottom };
	//������ �Ʒ� 
	edge[3] = { rc.right, rc.bottom };
}

//�ڽ��� �÷����̿��� �浹 üũ
//���� ��ġ�� �κ��� ã��
//�𼭸� ��ǥ�� �̿��Ѵٸ�, �浹ü�� ũ�Ⱑ �ʹ� ���� �� �浹�� üũ�� �� ����
//�ϴ� �𼭸��� ������
//rc �浹ü  rc2 �÷��̾�
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
