#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Flipbook.h"

Player::Player()
{
	//Idle
	_flipbookIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Idle");
	_flipbookIdle[DIR_Down] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Idle");
	_flipbookIdle[DIR_Left] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Idle");
	_flipbookIdle[DIR_Right] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Idle");

	// Move
	_flipbookMove[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Move");
	_flipbookMove[DIR_Down] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Move");
	_flipbookMove[DIR_Left] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Move");
	_flipbookMove[DIR_Right] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Move");

	// Run
	_flipbookRun[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Run");
	_flipbookRun[DIR_Down] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Run");
	_flipbookRun[DIR_Left] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Run");
	_flipbookRun[DIR_Right] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Run");
	
	// Bicycle Idle
	_flipbookBicycleIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_BicycleIdle");
	_flipbookBicycleIdle[DIR_Down] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_BicycleIdle");
	_flipbookBicycleIdle[DIR_Left] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_BicycleIdle");
	_flipbookBicycleIdle[DIR_Right] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_BicycleIdle");

	// Bicycle
	_flipbookBicycle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Bicycle");
	_flipbookBicycle[DIR_Down] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Bicycle");
	_flipbookBicycle[DIR_Left] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Bicycle");
	_flipbookBicycle[DIR_Right] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Bicycle");
}
	

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);

	SetCellPos({ 5, 5 }, true);
	SetSizeRatio(2);
}

void Player::Tick()
{
	Super::Tick();

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
	_keyPressed = true;
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	// 자전거 모드 변경
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::B))
	{
		_onBicycle = !(_onBicycle);
		_speed = 400 - _speed;
	}

	// 이동
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::W))
	{
		SetDir(DIR_Up);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LShift))
		{
			// 달리기
			SetCellPos(nextPos);
			SetState(ObjectState::Run);
		}
		else
		{
			// 걷기
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::S))
	{
		SetDir(DIR_Down);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LShift))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Run);
		}
		else
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		SetDir(DIR_Left);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LShift))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Run);
		}
		else
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		SetDir(DIR_Right);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LShift))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Run);
		}
		else
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else
	{
		_keyPressed = false;
		if (_state == ObjectState::Idle)
			UpdateAnimation();
	}

}

void Player::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = _destPos - _pos;
	if (dir.Length() < 1.f)
	{
		SetState(ObjectState::Idle);
		_pos = _destPos;
	}
	else
	{
		switch (_dir)
		{
		case DIR_Up:
			_pos.y -= _speed * deltaTime;
			break;
		case DIR_Down:
			_pos.y += _speed * deltaTime;
			break;
		case DIR_Left:
			_pos.x -= _speed * deltaTime;
			break;
		case DIR_Right:
			_pos.x += _speed * deltaTime;
			break;
		}
	}
}

void Player::TickRun()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = _destPos - _pos;
	if (dir.Length() < 0.5f)
	{
		SetState(ObjectState::Idle);
		_pos = _destPos;
	}
	else
	{
		switch (_dir)
		{
		case DIR_Up:
			_pos.y -= _speed * 2 * deltaTime;
			break;
		case DIR_Down:
			_pos.y += _speed * 2 * deltaTime;
			break;
		case DIR_Left:
			_pos.x -= _speed * 2 * deltaTime;
			break;
		case DIR_Right:
			_pos.x += _speed * 2 * deltaTime;
			break;
		}
	}
}

void Player::TickBattle()
{
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookMove[_dir]);
		else
		{
			if (_onBicycle)
				SetFlipbook(_flipbookBicycleIdle[_dir]);
			else
				SetFlipbook(_flipbookIdle[_dir]);
		}
		break;
	case ObjectState::Move:
		if (_onBicycle)
			SetFlipbook(_flipbookBicycle[_dir]);
		else
			SetFlipbook(_flipbookMove[_dir]);
		break;
	case ObjectState::Run:
		if (_onBicycle)
			SetFlipbook(_flipbookBicycle[_dir]);
		else
			SetFlipbook(_flipbookRun[_dir]);
		break;
	}
}
