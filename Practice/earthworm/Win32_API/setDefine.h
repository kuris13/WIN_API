#pragma once

//������ ��� ����
#include <Windows.h>

//C��� ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/* ===================================
���� ���� ��� ���ϵ�
=================================== */
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "box.h"
#include "worm.h"
/* ===================================
�̱���
=================================== */
#define KEYMANAGER keyManager::getSingleton()
//#define MOUSEMANAGER mouseManager::getSingleton()
#define RND randomFunction::getSingleton()


/* ===================================
		������ define ����
=================================== */
#define WIN_NAME (LPTSTR)(TEXT("Window API"))
#define WINSTART_X 400
#define WINSTART_Y 100
#define WINSIZE_X 800
#define WINSIZE_Y 800
#define WIN_STYLE CS_HREDRAW | CS_VREDRAW

#define FOCUSBOX 5
/* ===================================
		Extern
=================================== */
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;