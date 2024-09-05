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
		(int32)_pos.x - (size.x * _renderRatio) / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - (size.y * _renderRatio) / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x * _renderRatio,
		size.y * _renderRatio,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		size.x,
		size.y,
		_sprite->GetTransparent());
}
