#pragma once

#include "ConsoleBuffer.h"

namespace PradleEngine
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		static void DrawChar(int x, int y, char character, WORD wordColor, WORD bgColor);
		static void DrawChar(COORD coord, char character, WORD wordColor, WORD bgColor);
		static void SwapBuffer();
		static void Clear(WORD bgColor);
		static void SetBackBuffer(ConsoleBuffer* backBuffer) { _backBuffer = backBuffer; }

		static bool Init();
		static bool Render();

		static bool IsInConsole(int x, int y);
		static bool IsInConsole(COORD coordinate);
		
	private:
		static HANDLE _outputHandle;
		static ConsoleBuffer* _backBuffer;
		static std::vector<ConsoleBuffer*> _buffers;
		static CONSOLE_SCREEN_BUFFER_INFO _consoleBufferInfo;
	};
}