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
	Enter = VK_RETURN,

	LShift = VK_LSHIFT,
	Wave = VK_OEM_3,

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',
	KEY_5 = '5',
	KEY_6 = '6',
	KEY_7 = '7',
	KEY_8 = '8',
	KEY_9 = '9',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
	I = 'I',
	T = 'T',
	B = 'B',
};

enum class KeyState
{
	None,	// �ƹ��͵� �ƴ� ����
	Press,	// ��� ������ �ִ� ����
	Down,	// �� ���� ����
	Up,		// �����ٰ� ���� �� ����

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
	void		Init(HWND mainHwnd, HWND paletteHwnd);
	void		Update();

	// ������ ���� ��
	bool		GetButtonPress(KeyType key) { return GetState(key) == KeyState::Press; }

	// �� ó�� ������ ��
	bool		GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// �� ó�� �����ٰ� �� ��
	bool		GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT		GetMousePos() { return _mousePos; }

private:
	KeyState	GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND					_mainHwnd = 0;
	HWND					_paletteHwnd = 0;
	std::vector<KeyState>	_states;
	POINT					_mousePos;
};
