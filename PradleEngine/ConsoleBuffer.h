#pragma once

#include <Windows.h>
#include "Defines.h"

namespace PradleEngine
{
	class ConsoleBuffer
	{
	public:
		ConsoleBuffer();
		virtual ~ConsoleBuffer();

		COORD GetBufferSize() { return _bufferSize; }
		CHAR_INFO* GetBufferArray() { return _bufferArray; }

	private:
		COORD _bufferSize;
		CHAR_INFO* _bufferArray;
	};
}