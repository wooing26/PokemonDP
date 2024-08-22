#include "pch.h"
#include "TilemapActor.h"
#include "SceneManager.h"
#include "Scene.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	
	int32 MaxX = min(_mapSize.x - (cameraPos.x - GWinSizeX / 2), GWinSizeX);
	int32 MaxY = min(_mapSize.y - (cameraPos.y - GWinSizeY / 2), GWinSizeY);

	Vec2Int from = Vec2Int{ (int32) _pos.x - ((int32)cameraPos.x - GWinSizeX / 2), (int32)_pos.y - ((int32)cameraPos.y - GWinSizeY / 2) };
	Vec2Int to = from;
	to.y += _mapSize.y;

	while(from.x <= MaxX)
	{
		from.x += _tileSize;
		to.x += _tileSize;
		
		if (from.x >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
	}

	from = Vec2Int{ (int32)_pos.x - ((int32)cameraPos.x - GWinSizeX / 2), (int32)_pos.y - ((int32)cameraPos.y - GWinSizeY / 2) };
	to = from;
	to.x += _mapSize.x;
	while (from.y <= MaxY)
	{
		from.y += _tileSize;
		to.y += _tileSize;

		if (from.y >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
	}
}
