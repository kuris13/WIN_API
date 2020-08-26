#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	//map으로 만든 이e미지 목록
	typedef map<string, image*> mapImageList;
	//map으로 만든 이미지 목록의 반복자
	typedef map<string, image*>::iterator mapImageIter;


private:
	mapImageList _mImageList;


public:
	//이미지 매니저 초기화
	HRESULT init(void);
	//이미지 매니저 해제
	void release();

	//빈 비트맵으로 초기화
	image* addImage(string strKey, int width, int height);


	//이미지 파일로 초기화
	image* addImage(string strKey, const char* fileName,
		int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	image* addImage(string strKey, const char* fileName,
	float x, float y, int width, int height,
	BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//애니메이션(스프라이트 시트) 초기화
	image * addFrameImage(string strKey, const char* fileName,
		int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	image * addFrameImage(string strKey, const char* fileName,
		float x, float y, int width, int height, int maxFrameX,
		int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));


	//이미지를 키값으로 찾기
	image* findImage(string strKey);
	//이미지를 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll();

	//render
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY,
		int sourceX, int sourceY, int sourceWidth, int sourceHeight);

	//alpha Render
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	//loop Render
	void loopRender(string strKey, HDC hdc,
		const LPRECT drawArea, int offsetX, int offsetY);


	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY);



	imageManager() {}
	~imageManager() {}
};

