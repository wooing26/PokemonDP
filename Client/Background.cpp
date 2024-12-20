#include "pch.h"
#include "Background.h"
#include "Sprite.h"
#include "SceneManager.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::BeginPlay()
{
	Super::BeginPlay();
}

void Background::Tick()
{
	Super::Tick();
}

void Background::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_map == nullptr)
		return;

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	::TransparentBlt(
		hdc,
		0,
		0,
		_size.x,
		_size.y,
		_map->GetDC(),
		_map->GetPos().x,
		_map->GetPos().y,
		_size.x,
		_size.y,
		_map->GetTransparent());
}

void Background::SetMapSprite(Sprite* map)
{
	if (map == nullptr)
		return;

	_map = map;
	SetSize(map->GetSize());
}
