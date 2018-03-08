#pragma once

#include <Windows.h>
#include <vector>
#include "Defines.h"

namespace PradleEngine
{
	class ConsoleBuffer;
	class Scene;
	class Engine
	{
	public:
		static Engine* Create();
		static Engine* Create(int syncFrame);
		static Engine* Create(CODE_PAGE codePage);
		static Engine* Create(CODE_PAGE codePage, int syncFrame);

		void SetCodePage(CODE_PAGE codePage);
		void SetSync(int syncFrame);
		void Excute(Scene* startScene);

	protected:
		Engine();
		Engine(CODE_PAGE codePage, int syncFrame);
		~Engine();

	private:
		//bool InitConsole();
		//void SwapChain();
		BOOL RenderBuffer();
		void ClearBackBuffer(WORD bgColor);
		void WaitForSync();

	private:
		//int _syncFrame;
		//std::vector<ConsoleBuffer*> _buffers;
		HANDLE _outputHandle;
		//CONSOLE_SCREEN_BUFFER_INFO _consoleBufferInfo;
	};
}