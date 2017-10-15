#include "Core.h"

namespace PradleEngine
{
	Scene* SceneManager::_currentScene = nullptr;
	Scene* SceneManager::_nextScene = nullptr;
	bool SceneManager::_isQuit = false;

	void SceneManager::ReplaceScene(Scene * scene)
	{
		if (_nextScene == scene)
			return;

		if (_nextScene)
		{
			_nextScene->ReleaseScene();
			_nextScene = nullptr;
		}
		_nextScene = scene;
	}

	void SceneManager::Update()
	{
		if (_nextScene == nullptr)
			return;

		if (_currentScene)
		{
			_currentScene->ReleaseScene();
			_currentScene = nullptr;
		}
		_currentScene = _nextScene;
		_currentScene->OnEnter();
		_nextScene = nullptr;
	}
}