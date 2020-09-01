#pragma once
#include "gameNode.h"
#include "progressBar.h"


typedef enum
{
	LOAD_IMAGE_0,			//빈 비트맵 이미지
	LOAD_IMAGE_1,			//일반 이미지
	LOAD_IMAGE_2,			//일반 이미지 (위치 좌표 포함)
	LOAD_FRAMEIMAGE_0,		//프레임 이미지
	LOAD_FRAMEIMAGE_1,		//프레임 이미지 (위치 좌표 포함)
	LOAD_SOUND,				//사운드
	LOAD_END				//끝
}LOAD_ITEM;

typedef struct
{
	string keyName;
	const char* fileName;
	int x, y, width, height, frameX, frameY;
	bool trans;
	COLORREF transColor;
}tagImageResource;




class loadItem
{
private:
	LOAD_ITEM _itemCategory;
	tagImageResource _imageResource;
public :
	//일반 이미지 초기화
	HRESULT init(string keyName, int width, int height);
	HRESULT init(string keyName, const char* fileName, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));
	HRESULT init(string keyName, const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));

	//프레임 이미지 초기화
	HRESULT init();

	

};



class loding : public gameNode
{

public:


	HRESULT init();
	void release();
	void update();
	void render();


	loding();
	~loding();
};

