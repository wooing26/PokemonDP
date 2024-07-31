#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		KeyState& state = _states[key];

		// 키가 눌려 있으면 true
		if (asciiKeys[key] & 0x80)
		{
			// 이전 프레임에 눌러져 있었으면 Press
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			// 이전 프레임에 눌러져 있었으면 Up
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos);				// 마우스 커서 위치
	::ScreenToClient(_hwnd, &_mousePos);	// 윈도우(프로그램 창) 기준 마우스 좌표로 변경
}
