#include "Core.h"

namespace PradleEngine
{
	ConsoleBuffer* Renderer::_backBuffer;

	void Renderer::DrawChar(int x, int y, char character, WORD wordColor, WORD bgColor)
	{
		if (!IsInConsole(x, y))
			return;

		int index = _backBuffer->GetBufferSize().X * y + x;
		_backBuffer->GetBufferArray()[index].Char.AsciiChar = character;
		_backBuffer->GetBufferArray()[index].Attributes = RGB(wordColor, bgColor);
	}

	bool Renderer::IsInConsole(int x, int y)
	{
		if (x < 0 || y < 0 || x >= CONSOLE_WIDHT || y >= CONSOLE_HEIGHT)
			return false;
		return true;
	}

	bool Renderer::IsInConsole(COORD coordinate)
	{
		if (coordinate.X < 0 || coordinate.Y < 0 || coordinate.X >= CONSOLE_WIDHT || coordinate.Y >= CONSOLE_HEIGHT)
			return false;
		return true;
	}
}
