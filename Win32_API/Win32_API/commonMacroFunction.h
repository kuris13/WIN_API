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

inline void EllipseMake(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//�ζ��� �Լ� (inline function)
/*
	1. ����
	 - ��ũ��(define)�� ������ �Լ��� ������ ��ģ �Լ�
	 - ���������� �Լ��� ������ ���� �ֱ� ������
	    �Ű������� �ڷ���(Ÿ��)�� ������ �� �־� ��ũ���� ���� ����.

	2. �����
	inline [�ڷ���] [�Լ���] (�Ű�����)
	{
		���๮
	}
	  - �Լ� ���� �տ� inline �̶�� ���� �Է��ϸ� ��.

	3. �ζ��� �Լ��� �������� �ʴ� ����
	  - �ݺ����� ���α׷������� ���� �Ȱ��� �ڵ尡 �ݺ��� ���� �ְ�,
	     �ڵ��� ���̰� ���� ���� �̻����� ������ٸ�
		 �ζ��� �Լ��� ��� ��ü�� �����ؾ� �Ѵ�.
	  - �������� ���� ȯ���� �����ϱ� ����,
	     �����Ϸ��� ��ü������ �ڵ��� ���̸� �����ϰ� �ִ�.
*/