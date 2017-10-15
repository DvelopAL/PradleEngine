#include "ConsoleBuffer.h"

namespace PradleEngine
{
	ConsoleBuffer::ConsoleBuffer()
	{
		_bufferSize = { CONSOLE_WIDHT, CONSOLE_HEIGHT };
		_bufferArray = new CHAR_INFO[CONSOLE_WIDHT * CONSOLE_HEIGHT];
		ZeroMemory(_bufferArray, CONSOLE_WIDHT * CONSOLE_HEIGHT * sizeof(CHAR_INFO));
	}

	ConsoleBuffer::~ConsoleBuffer()
	{
		delete[] _bufferArray;
	}
}
