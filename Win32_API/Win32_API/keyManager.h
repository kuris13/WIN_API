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
	POINT ptMouse = { 0,0 };
	POINT edge[4] = { 0 };
	HRESULT init();
	bool inTheMouse(RECT rc);
	void makeEdge(RECT edge);
	bool inTheRect(RECT rc, RECT rc2);
	bool isOnceKeyDown(int key);		//Ű�� �Էµ���
	bool isOnceKeyUp(int key);			//Ű �Է� ����
	bool isStayKeyDown(int key);		//��� ���� ����
	bool isToggleKey(int key);				//���Ű

	keyManager() {}
	~keyManager() {}
};