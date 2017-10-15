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
		static bool IsInConsole(int x, int y);
		static bool IsInConsole(COORD coordinate);

	private:
		friend Engine;

		static void SetBackBuffer(ConsoleBuffer* backBuffer) { _backBuffer = backBuffer; }

	private:
		static ConsoleBuffer* _backBuffer;
	};
}