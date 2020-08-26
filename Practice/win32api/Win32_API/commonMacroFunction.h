#pragma once
#include <Windows.h>

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2};
	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void LineMake(HDC hdc, POINT startPT, POINT endPT)
{
	MoveToEx(hdc, startPT.x, startPT.y, NULL);
	LineTo(hdc, endPT.x, endPT.y);
}

//인라인 함수 (inline function)
/*
	1. 개요
	 - 매크로(define)의 장점과 함수의 장점을 합친 함수
	 - 본질적으로 함수의 성질을 갖고 있기 때문에
	    매개변수에 자료형(타입)을 지정할 수 있어 매크로의 단점 보완.

	2. 사용방법
	inline [자료형] [함수명] (매개변수)
	{
		실행문
	}
	  - 함수 원형 앞에 inline 이라는 예약어만 입력하면 끝.

	3. 인라인 함수를 남용하지 않는 이유
	  - 반복적인 프로그래밍으로 인해 똑같은 코드가 반복될 수도 있고,
	     코드의 길이가 일정 수준 이상으로 길어진다면
		 인라인 함수의 사용 자체를 지양해야 한다.
	  - 안정적인 동작 환경을 보장하기 위해,
	     컴파일러가 자체적으로 코드의 길이를 제한하고 있다.
*/