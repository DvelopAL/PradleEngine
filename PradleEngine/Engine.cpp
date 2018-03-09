#include "Core.h"

namespace PradleEngine
{
	Engine::Engine()
	{
		SetCodePage(CODE_PAGE::ENGLISH);
		_syncFrame = 0;
	}

	bool Engine::Init()
	{
		bool result = false;
		result = Renderer::Init() && Input::Init();
		return result;
	}

	Engine * Engine::Create()
	{
		Engine* engine = new (std::nothrow) Engine();
		if (engine && engine->Init())
		{
			return engine;
		}
		return nullptr;
	}

	Engine * Engine::Create(int syncFrame)
	{
		Engine* engine = new (std::nothrow) Engine();
		engine->SetSync(syncFrame);
		if (engine && engine->Init())
		{
			return engine;
		}
		return nullptr;
	}

	Engine * Engine::Create(CODE_PAGE codePage)
	{
		Engine* engine = new (std::nothrow) Engine();
		engine->SetCodePage(codePage);
		if (engine && engine->Init())
		{
			return engine;
		}
		return nullptr;
	}

	Engine * Engine::Create(CODE_PAGE codePage, int syncFrame)
	{
		Engine* engine = new (std::nothrow) Engine();
		engine->SetCodePage(codePage);
		engine->SetSync(syncFrame);
		if (engine && engine->Init())
		{
			return engine;
		}
		return nullptr;
	}

	void Engine::SetCodePage(CODE_PAGE codePage)
	{
		if (codePage == CODE_PAGE::KOREAN) system("chcp 949");
		else if (codePage == CODE_PAGE::ENGLISH) system("chcp 437");
	}

	void Engine::SetSync(int syncFrame)
	{
		_syncFrame = syncFrame;
	}

	void Engine::Excute(Scene * startScene)
	{
		if (this == nullptr)
		{
			printf("Engine initalize is failure can't excute engine");
			return;
		}

		SceneManager::ReplaceScene(startScene);
		
		// Simple game loop
		while (!SceneManager::IsQuitGame())
		{
			SceneManager::Update();
			Input::Update();
			Renderer::Clear(SceneManager::GetCurrentScene()->GetBGColor());

			SceneManager::GetCurrentScene()->Update();
			Renderer::SwapBuffer();
			WaitForSync();
		}
		SceneManager::GetCurrentScene()->ReleaseScene();
		delete this;
	}

	void Engine::WaitForSync()
	{
		static int oldtime = 0;
		while (GetTickCount() - oldtime < 1000 / _syncFrame);
		oldtime = GetTickCount();
	}
}
