#pragma once

#include <Windows.h>
#include "Defines.h"
#include "Engine.h"

namespace PradleEngine
{
	enum class MOUSE
	{
		RIGHT,
		LEFT,
		WHEEL,
	};

	enum class KEY {
		NUMBER_0 = 0x30, NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L,
		M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		RETURN = 0x0D, ESCAPE = 0x1B, /*DELETE = 0x2E,*/ SPACE = 0x20,
		LSHIFT = 0xA0, RSHIFT, LCONTROL, RCONTROL, LEMNU, RMENU,
		LEFT = 0x25, UP, RIGHT, DOWN
	};

	class Input
	{
	public:
		Input();

		static COORD GetMouseCoordinate() { return _mouseCoordinate; }
		static bool IsKey(KEY key);
		static bool IsMouseDown(MOUSE key);
		static bool IsKeyUp(KEY key);

	private:
		friend Engine;

		static bool InitInput();
		static void Update();
		static void SetMouseCoordinate();

	private:
		static HANDLE _inputHandle;
		static INPUT_RECORD _inputRecord;
		static DWORD _mouseStates[3];
		static COORD _mouseCoordinate;
		static BYTE _keyValue[256];	
		static BYTE _keyUpValue[256];
	};
}