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
		static void SwapBuffer();
		static void ClearBuffer(WORD bgColor);
		static void WaitForSync();

		static bool Init();
		static bool Render();

		static bool IsInConsole(int x, int y);
		static bool IsInConsole(COORD coordinate);

	private:
		static void SetBackBuffer(ConsoleBuffer* backBuffer) { _backBuffer = backBuffer; }

	private:
		static ConsoleBuffer* _backBuffer;
	};
}