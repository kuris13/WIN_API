//키매니저(keyManager)
//싱글톤 클래스를 상속받아 어떤 클래스에서도 키매니저에 접근할 수 있도록 만든다.

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
	bool isOnceKeyDown(int key);		//키가 입력됐음
	bool isOnceKeyUp(int key);			//키 입력 종료
	bool isStayKeyDown(int key);		//계속 눌린 상태
	bool isToggleKey(int key);				//토글키

	keyManager() {}
	~keyManager() {}
};