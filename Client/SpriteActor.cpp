#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();
}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2Int size = _sprite->GetSize();

	/*::BitBlt(hdc,
		50,
		50,
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		SRCCOPY);*/

	::StretchBlt(hdc,
		_pos.x - _renderSize.x / 2,
		_pos.y - _renderSize.y / 2,
		_renderSize.x,
		_renderSize.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		size.x,
		size.y,
		SRCCOPY);
}
