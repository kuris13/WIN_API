//Ű�Ŵ���(keyManager)
//�̱��� Ŭ������ ��ӹ޾� � Ŭ���������� Ű�Ŵ����� ������ �� �ֵ��� �����.

#pragma once
#include "singletonBase.h"

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];

public:
	HRESULT init();

	bool isOnceKeyDown(int key);		//Ű�� �Էµ���
	bool isOnceKeyUp(int key);			//Ű �Է� ����
	bool isStayKeyDown(int key);		//��� ���� ����
	bool isToggleKey(int key);				//���Ű

	keyManager() {}
	~keyManager() {}
};