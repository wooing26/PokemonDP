#include "pch.h"
#include "HpBar.h"
#include "ResourceManager.h"
#include "Sprite.h"

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
		_size = _hpBar->GetSize() * 4;
		_pos = Vec2(MainSizeX - _size.x, MainSizeY * 2 / 3);
	}
	else
	{
		_hpBar = GET_SINGLE(ResourceManager)->GetSprite(L"Other_HP_Male");
		_size = _hpBar->GetSize() * 4;
		_pos = Vec2(0, MainSizeY * 1 / 5);
	}
}

void HpBar::Tick()
{
	Super::Tick();
}

void HpBar::Render(HDC hdc)
{
	Super::Render(hdc);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;	// 0(투명) ~ 255(불투명)
	bf.AlphaFormat = AC_SRC_ALPHA;

	::AlphaBlend(hdc,
		_pos.x,
		_pos.y,
		_size.x,
		_size.y,
		_hpBar->GetDC(),
		_hpBar->GetPos().x,
		_hpBar->GetPos().y,
		_hpBar->GetSize().x,
		_hpBar->GetSize().y,
		bf);
}
