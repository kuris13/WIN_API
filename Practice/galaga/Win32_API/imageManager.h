#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	//map���� ���� ��e���� ���
	typedef map<string, image*> mapImageList;
	//map���� ���� �̹��� ����� �ݺ���
	typedef map<string, image*>::iterator mapImageIter;


private:
	mapImageList _mImageList;


public:
	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	//�̹��� �Ŵ��� ����
	void release();

	//�� ��Ʈ������ �ʱ�ȭ
	image* addImage(string strKey, int width, int height);


	//�̹��� ���Ϸ� �ʱ�ȭ
	image* addImage(string strKey, const char* fileName,
		int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	image* addImage(string strKey, const char* fileName,
	float x, float y, int width, int height,
	BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//�ִϸ��̼�(��������Ʈ ��Ʈ) �ʱ�ȭ
	image * addFrameImage(string strKey, const char* fileName,
		int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	image * addFrameImage(string strKey, const char* fileName,
		float x, float y, int width, int height, int maxFrameX,
		int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));


	//�̹����� Ű������ ã��
	image* findImage(string strKey);
	//�̹����� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll();

	//render
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY,
		int sourceX, int sourceY, int sourceWidth, int sourceHeight);

	//alpha Render
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	imageManager() {}
	~imageManager() {}
};

