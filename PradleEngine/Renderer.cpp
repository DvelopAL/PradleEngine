#include "Core.h"

namespace PradleEngine
{
	ConsoleBuffer* Renderer::_backBuffer;
	std::vector<ConsoleBuffer*>  Renderer::_buffers;
	HANDLE Renderer::_outputHandle;
	CONSOLE_SCREEN_BUFFER_INFO Renderer::_consoleBufferInfo;

	bool Renderer::Init()
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

		_backBuffer = _buffers[1];

		return true;
	}

	void Renderer::DrawChar(int x, int y, char character, WORD wordColor, WORD bgColor)
	{
		if (!IsInConsole(x, y))
			return;

		int index = _backBuffer->GetBufferSize().X * y + x;
		_backBuffer->GetBufferArray()[index].Char.AsciiChar = character;
		_backBuffer->GetBufferArray()[index].Attributes = RGB(wordColor, bgColor);
	}

	void Renderer::DrawChar(COORD coord, char character, WORD wordColor, WORD bgColor)
	{
		if (!IsInConsole(coord))
			return;

		int index = _backBuffer->GetBufferSize().X * coord.Y + coord.X;
		_backBuffer->GetBufferArray()[index].Char.AsciiChar = character;
		_backBuffer->GetBufferArray()[index].Attributes = RGB(wordColor, bgColor);
	}

	void Renderer::SwapBuffer()
	{
		ConsoleBuffer* temp = _buffers[0];
		_buffers[0] = _buffers[1];
		_buffers[1] = temp;

		Render();
	}

	void Renderer::Clear(WORD bgColor)
	{
		CHAR_INFO temp;
		temp.Char.AsciiChar = ' ';
		temp.Attributes = RGB(BLACK, bgColor);

		int size = CONSOLE_WIDHT * CONSOLE_HEIGHT;
		for (int i = 0; i<size; i++)
			_buffers[1]->GetBufferArray()[i] = temp;

		_backBuffer = _buffers[1];
	}

	bool Renderer::Render()
	{
		COORD coordinate = { 0, 0 };
		SMALL_RECT rect = { 0, 0, CONSOLE_WIDHT - 1, CONSOLE_HEIGHT - 1 };
		return WriteConsoleOutput(_outputHandle, _buffers[0]->GetBufferArray(), _buffers[0]->GetBufferSize(), coordinate, &rect);
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
