#pragma once

//������ ��� ����
#include <Windows.h>

//C��� ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//C++ ��Ÿ�� ��� ����
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

/* ===================================
���� ���� ��� ���ϵ�
=================================== */
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"

/* ===================================
�̱���
=================================== */
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()

/* ===================================
		������ define ����
=================================== */
#define WIN_NAME (LPTSTR)(TEXT("Window API"))
#define WINSTART_X 400
#define WINSTART_Y 100
#define WINSIZE_X 1280
#define WINSIZE_Y 720
#define WIN_STYLE CS_HREDRAW | CS_VREDRAW

/* ===================================
		Extern
=================================== */
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

/* ===================================
	�����Ҵ�� ��ü�� �����ϴ� ��ũ�� �Լ�
=================================== */
#define SAFE_DELETE(p) {if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL;}}