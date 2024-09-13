#include "pch.h"
#include "HpBar.h"
#include "ResourceManager.h"

HpBar::HpBar()
{
}

HpBar::~HpBar()
{
}

void HpBar::BeginPlay()
{
	Super::BeginPlay();
	if (_isMine)
	{
		_hpBar = GET_SINGLE(ResourceManager)->GetSprite(L"My_HP_Male");

	}
}

void HpBar::Tick()
{
	Super::Tick();
}

void HpBar::Render(HDC hdc)
{
	Super::Render(hdc);
}
