#pragma once
#include "gameNode.h"
#include "progressBar.h"


typedef enum
{
	LOAD_IMAGE_0,			//�� ��Ʈ�� �̹���
	LOAD_IMAGE_1,			//�Ϲ� �̹���
	LOAD_IMAGE_2,			//�Ϲ� �̹��� (��ġ ��ǥ ����)
	LOAD_FRAMEIMAGE_0,		//������ �̹���
	LOAD_FRAMEIMAGE_1,		//������ �̹��� (��ġ ��ǥ ����)
	LOAD_SOUND,				//����
	LOAD_END				//��
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
	//�Ϲ� �̹��� �ʱ�ȭ
	HRESULT init(string keyName, int width, int height);
	HRESULT init(string keyName, const char* fileName, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));
	HRESULT init(string keyName, const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));

	//������ �̹��� �ʱ�ȭ
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

