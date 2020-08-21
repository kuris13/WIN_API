/*
	<< GetAsyncKeyState(int key) >>
	- ���� Ű ���¸� �޾ƿ��� �Լ�
	- ȣ��Ǳ� ���� Ű�� ���� ���¿�����,
	   �Լ��� ȣ��� ������ ���翡�� ������ �ִ� �������� �޾ƿ´�.

	 <���� ���°� � ���� �˷��ִ� ���� ��Ʈ>
	 0x0000 : ������ ���� ���� ����, ȣ�� ������ �� ���� ����
	 0x8000 : ������ ���� ���� ����, ȣ�� ������ ���� ����
	 0x8001 : ������ ���� ���� �ְ�, ȣ�� ������ ���� ����
	 0x0001 : ������ ���� ���� �ְ�, ȣ�� ������ �� ���� ����

	 �� ���� ���� : ���� GetAsyncKeyState�� ȣ���� �� ~
						   ���� GetAsyncKeyState�� ȣ���ϱ� ����
*/




#include "setDefine.h"
#include "keyManager.h"

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
