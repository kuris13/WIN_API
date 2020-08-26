#include "setDefine.h"
#include "sceneManager.h"
#include "gameNode.h"



HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	mSceneList_iter iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);


		}
		else
		{
			++iter;
		}
	}
}

void sceneManager::update()
{
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void sceneManager::render()
{
	if (_currentScene)
	{
		_currentScene->render();
	}
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mSceneList_iter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return E_FAIL;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}
}




sceneManager::~sceneManager()
{
}
