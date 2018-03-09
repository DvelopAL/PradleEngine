#include "Input.h"

namespace PradleEngine
{
	HANDLE Input::_inputHandle;
	INPUT_RECORD  Input::_inputRecord;
	DWORD Input::_mouseStates[3];
	COORD Input::_mouseCoordinate;
	BYTE Input::_keyValue[256];
	BYTE Input::_keyUpValue[256];

	Input::Input()
	{
	}

	bool Input::IsKey(KEY key)
	{
		return _keyValue[static_cast<int>(key)] == 1 ? true : false;
	}

	bool Input::IsMouseDown(MOUSE key)
	{
		return _mouseStates[static_cast<int>(key)] == 1 ? true : false;
	}

	bool Input::IsKeyUp(KEY key)
	{
		if (_keyValue[static_cast<int>(key)] == 0 && _keyValue[static_cast<int>(key)] == 0)
		{
			_keyValue[static_cast<int>(key)] = 1;
			return true;
		}

		return false;
	}

	bool Input::Init()
	{
		ZeroMemory(_keyValue, sizeof(_keyValue));
		memset(_keyUpValue, 1, sizeof(_keyUpValue));
		ZeroMemory(_mouseStates, sizeof(_mouseStates));
		_mouseCoordinate.X = 0;
		_mouseCoordinate.Y = 0;

		_inputHandle = GetStdHandle(STD_INPUT_HANDLE);
		if (_inputHandle == INVALID_HANDLE_VALUE)
			return false;

		DWORD modeOld, modeNew;
		GetConsoleMode(_inputHandle, &modeOld);
		modeNew = modeOld;
		modeNew |= ENABLE_MOUSE_INPUT;
		modeNew &= ~ENABLE_QUICK_EDIT_MODE;

		if (SetConsoleMode(_inputHandle, modeNew) != TRUE)
			return false;

		return true;
	}

	void Input::Update()
	{
		DWORD unread = 0, read = 0;
		GetNumberOfConsoleInputEvents(_inputHandle, &unread);

		if (unread == 0)
			return;

		ZeroMemory(&_inputRecord, sizeof(INPUT_RECORD));

		for (DWORD i = 0; i < unread; ++i)
		{
			ReadConsoleInput(_inputHandle, &_inputRecord, 1, &unread);

			switch (_inputRecord.EventType)
			{
			case KEY_EVENT:
			{
				WORD keycode = _inputRecord.Event.KeyEvent.wVirtualKeyCode;
				BOOL bkeydown = _inputRecord.Event.KeyEvent.bKeyDown;

				_keyValue[keycode] = bkeydown;

				if (bkeydown == 1)
					_keyUpValue[keycode] = 0;
			}
			break;

			case MOUSE_EVENT:
				ZeroMemory(_mouseStates, sizeof(_mouseStates));

				switch (_inputRecord.Event.MouseEvent.dwButtonState)
				{
				case FROM_LEFT_1ST_BUTTON_PRESSED: _mouseStates[static_cast<int>(MOUSE::LEFT)] = 1;
					break;
				case RIGHTMOST_BUTTON_PRESSED: _mouseStates[static_cast<int>(MOUSE::RIGHT)] = 1;
					break;
				case FROM_LEFT_2ND_BUTTON_PRESSED: _mouseStates[static_cast<int>(MOUSE::WHEEL)] = 1;
					break;
				}

				SetMouseCoordinate();
				break;
			}
		}

		for (int i = 0xa0; i < 0xa6; i++)
		{
			_keyValue[i] = GetAsyncKeyState(i) ? TRUE : FALSE;

			if (_keyValue[i] == TRUE)
				_keyValue[i] = FALSE;
		}

		FlushConsoleInputBuffer(_inputHandle);
	}

	void Input::DisbleQuickEditMode()
	{
		DWORD modeOld, modeNew;

		GetConsoleMode(_inputHandle, &modeOld);

		modeNew = modeOld;
		modeNew &= ~ENABLE_QUICK_EDIT_MODE;

		SetConsoleMode(_inputHandle, modeNew);
	}

	void Input::SetMouseCoordinate()
	{
		_mouseCoordinate.X = _inputRecord.Event.MouseEvent.dwMousePosition.X;
		_mouseCoordinate.Y = _inputRecord.Event.MouseEvent.dwMousePosition.Y;
	}
}