#include "pch.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();
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
}

void Player::TickMove()
{
}

void Player::TickBattle()
{
}

void Player::UpdateAnimation()
{
}
