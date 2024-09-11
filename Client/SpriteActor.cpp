#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "InputManager.h"
#include "SceneManager.h"

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

	if (_sprite == nullptr)
		return;
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr)
		return;

	Vec2Int size = _sprite->GetSize();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	::TransparentBlt(
		hdc,
		(int32)_pos.x - _size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - _size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		_size.x,
		_size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		size.x,
		size.y,
		_sprite->GetTransparent());
}

void SpriteActor::SetSprite(Sprite* sprite)
{
	if (sprite == nullptr)
		return;

	_sprite = sprite;
	SetSize(sprite->GetSize());
}
