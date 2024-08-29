#pragma once

enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,

	Space = VK_SPACE,

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',
	KEY_5 = '5',
	KEY_6 = '6',
	KEY_7 = '7',
	KEY_8 = '8',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
};

enum class KeyState
{
	None,	// 아무것도 아닌 상태
	Press,	// 계속 누르고 있는 상태
	Down,	// 막 누른 상태
	Up,		// 눌렀다가 땠을 때 상태

	End
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};

class InputManager
{
	DECLARE_SINGLE(InputManager)

public:
	void		Init(HWND hwnd);
	void		Update();

	// 누르고 있을 때
	bool		GetButtonPress(KeyType key) { return GetState(key) == KeyState::Press; }
	
	// 맨 처음 눌렀을 때
	bool		GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }
	
	// 맨 처음 눌렀다가 땔 때
	bool		GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT		GetMousePos() { return _mousePos; }
	
private:
	KeyState	GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND					_hwnd = 0;
	std::vector<KeyState>	_states;
	POINT					_mousePos;
};

