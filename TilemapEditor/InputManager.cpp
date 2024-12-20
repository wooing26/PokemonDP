#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd, HWND paletteHwnd)
{
	_mainHwnd = hwnd;
	_paletteHwnd = paletteHwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	HWND activeHwnd = ::GetForegroundWindow();
	if (activeHwnd != _mainHwnd && activeHwnd != _paletteHwnd)
		return;

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		KeyState& state = _states[key];

		// Ű�� ���� ������ true
		if (asciiKeys[key] & 0x80)
		{
			// ���� �����ӿ� ������ �־����� Press
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			// ���� �����ӿ� ������ �־����� Up
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos);				// ���콺 Ŀ�� ��ġ
	::ScreenToClient(activeHwnd, &_mousePos);	// ������(���α׷� â) ���� ���콺 ��ǥ�� ����
}