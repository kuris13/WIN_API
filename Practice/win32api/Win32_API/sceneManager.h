#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager :public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator mSceneList_iter;

	mSceneList _mSceneList;
	gameNode* _currentScene;


public:

	HRESULT init();
	void release();
	void update();
	void render();


	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);

	

	sceneManager() : _currentScene(NULL) {};
	~sceneManager();
};

