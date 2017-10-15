#pragma once

#include "Scene.h"

namespace PradleEngine
{
	class SceneManager
	{
	public:
		SceneManager() = default;
		~SceneManager() = default;
		
		static void ReplaceScene(Scene* scene);

		static Scene* GetCurrentScene() { return _currentScene; }
		static Scene* GetNextScene() { return _nextScene; }

		static void QuitGame(bool isQuit) { _isQuit = isQuit; }
		static bool IsQuitGame() { return _isQuit; }

	private:
		friend Engine;

		static void Update();

	private:
		static Scene* _currentScene;
		static Scene* _nextScene;
		static bool _isQuit;
	};
}