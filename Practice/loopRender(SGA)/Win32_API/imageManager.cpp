#include "setDefine.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release()
{
	this->deleteAll();
}

//�� ��Ʈ������ �ʱ�ȭ �� �߰�
image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� �̹����� �̹� �����ϴ��� Ű������ �˻�
	image* img = findImage(strKey);
	
	//�߰��Ϸ��� �̹����� �̹� �����ϸ� ���� ������ �ʰ� �״�� ��ȯ
	if (img) return img;
	
	//������ ���� �����
	img = new image;
	
	//�ҷ����� ���߿� ���� �߸��ƴٸ� �ϴ� ������ ����
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//map ����Ʈ�� ���� (pair�� ������ �����͸�)
	_mImageList.insert(make_pair(strKey, img));
	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	image* img = findImage(strKey);
	if (img) return img;

	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	image* img = findImage(strKey);
	if (img) return img;

	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	return nullptr;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	return nullptr;
}

image * imageManager::findImage(string strKey)
{
	//Ư�� key�� map���� �˻� (�ݺ��� ���)
	mapImageIter key = _mImageList.find(strKey);

	//key�� �˻��Ͽ� �߰��� ���
	if (key != _mImageList.end())
	{
		//ã������ ���� ��� ��ȯ
		return key->second;
	}

	//�� ã���� NULL
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		//Ư�� �̹����� �޸𸮿��� ����, ���� ��� ����
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::deleteAll()
{
	//map�� 1ȸ ��ȸ
	mapImageIter iter = _mImageList.begin();

	//for (;�ݺ�����;) = while(true)
	for (; iter != _mImageList.end();)
	{
		//�̹����� ������?
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else  //�̹����� ������?
		{
			iter++;
		}
	}

	//map ��ü ����
	_mImageList.clear();

	return TRUE;
}

void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourceX, sourceY,
		sourceWidth, sourceHeight);

}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}
