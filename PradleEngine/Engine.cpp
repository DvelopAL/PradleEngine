#include "Core.h"

namespace PradleEngine
{
	Engine::Engine()
	{
		SetCodePage(CODE_PAGE::ENGLISH);
		if (!InitConsole())
			return;
	}

	Engine::Engine(CODE_PAGE codePage, int syncFrame) :
		_syncFrame(syncFrame)
	{
		SetCodePage(codePage);
		if (!InitConsole())
			return;
	}

	Engine::~Engine()
	{
		for (int i = 0; i < 2; ++i)
		{
			delete _buffers[i];
			_buffers[i] = nullptr;
		}
	}

	Engine * Engine::Create()
	{
		Engine* engine = new (std::nothrow) Engine();
		if (engine)
		{
			return engine;
		}
		return nullptr;
	}

	Engine * Engine::Create(int syncFrame)
	{
		Engine* engine = new (std::nothrow) Engine();
		engine->SetSync(syncFrame);
		if (engine)
		{
			return engine;
		}
		return nullptr;
	}

	Engine * Engine::Create(CODE_PAGE codePage)
	{
		Engine* engine = new (std::nothrow) Engine();
		engine->SetCodePage(codePage);
		if (engine)
		{
			return engine;
		}
		return nullptr;
	}

	Engine * Engine::Create(CODE_PAGE codePage, int syncFrame)
	{
		Engine* engine = new (std::nothrow) Engine(codePage, syncFrame);
		if (engine)
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
		Renderer::SetBackBuffer(_buffers[1]);
		SceneManager::ReplaceScene(startScene);
		
		// Simple game loop
		while (!SceneManager::IsQuitGame())
		{
			SceneManager::Update();
			Input::Update();
			ClearBackBuffer(SceneManager::GetCurrentScene()->GetBGColor());
			Renderer::SetBackBuffer(_buffers[1]);

			SceneManager::GetCurrentScene()->Update();
			SwapChain();
			WaitForSync();
		}
		SceneManager::GetCurrentScene()->ReleaseScene();
		delete this;
	}

	bool Engine::InitConsole()
	{
		_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		// TODO
		// 여기서 예외 처리 조금만 더 (Loging, MngBox..)
		if (_outputHandle == INVALID_HANDLE_VALUE)
			return false;

		COORD screenSize = { CONSOLE_WIDHT, CONSOLE_HEIGHT };
		SetConsoleScreenBufferSize(_outputHandle, screenSize);
		GetConsoleScreenBufferInfo(_outputHandle, &_consoleBufferInfo);

		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(_outputHandle, &cursorInfo);

		for (int i = 0; i < 2; ++i)
		{
			ConsoleBuffer* temp = new ConsoleBuffer();
			_buffers.push_back(temp);
		}

		if (!Input::InitInput())
			return false;

		return true;
	}

	void Engine::SwapChain()
	{
		ConsoleBuffer* temp = _buffers[0];
		_buffers[0] = _buffers[1];
		_buffers[1] = temp;

		RenderBuffer();
	}

	BOOL Engine::RenderBuffer()
	{
		COORD coordinate = { 0, 0 };
		SMALL_RECT rect = { 0, 0, CONSOLE_WIDHT - 1, CONSOLE_HEIGHT - 1 };
		return WriteConsoleOutput(_outputHandle, _buffers[0]->GetBufferArray(), _buffers[0]->GetBufferSize(), coordinate, &rect);
	}

	void Engine::ClearBackBuffer(WORD bgColor)
	{
		CHAR_INFO temp;
		temp.Char.AsciiChar = ' ';
		temp.Attributes = RGB(BLACK, bgColor);

		int size = CONSOLE_WIDHT * CONSOLE_HEIGHT;
		for (int i = 0; i<size; i++)
			_buffers[1]->GetBufferArray()[i] = temp;
	}

	void Engine::WaitForSync()
	{
		static int oldtime = 0;
		while (GetTickCount() - oldtime < 1000 / _syncFrame);
		oldtime = GetTickCount();
	}
}
