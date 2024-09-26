#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Flipbook.h"

Player::Player()
{
	//Idle
	_flipbookIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Idle");
	_flipbookIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Idle");
	_flipbookIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Idle");
	_flipbookIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Idle");

	// Move
	_flipbookMove[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Move");
	_flipbookMove[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Move");
	_flipbookMove[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Move");
	_flipbookMove[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Move");

	// Run
	_flipbookRun[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Run");
	_flipbookRun[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Run");
	_flipbookRun[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Run");
	_flipbookRun[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Run");
	
	// Bicycle Idle
	_flipbookBicycleIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_BicycleIdle");
	_flipbookBicycleIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_BicycleIdle");
	_flipbookBicycleIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_BicycleIdle");
	_flipbookBicycleIdle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_BicycleIdle");

	// Bicycle
	_flipbookBicycle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasUp_Bicycle");
	_flipbookBicycle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasDown_Bicycle");
	_flipbookBicycle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasLeft_Bicycle");
	_flipbookBicycle[DIR_Up] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LucasRight_Bicycle");
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
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


}

void Player::TickMove()
{
}

void Player::TickRun()
{
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
			SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::Move:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	case ObjectState::Run:
		SetFlipbook(_flipbookRun[_dir]);
		break;
	}
}
