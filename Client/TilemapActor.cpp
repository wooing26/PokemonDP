#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"


TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{
	
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
	
	std::wstring texture[TileMap_LAYER::MAXCOUNT] = { L"PLAT_Buildings", L"PLAT_Mount", L"PLAT_Nature", L"PLAT_Props" };
	
	for (int32 i = 0; i < TileMap_LAYER::MAXCOUNT; i++)
	{
		_sprites[i] = GET_SINGLE(ResourceManager)->GetSprite(texture[i]);
	}
}

void TilemapActor::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Up))
	{
		_pos.y += _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Down))
	{
		_pos.y -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Left))
	{
		_pos.x -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Right))
	{
		_pos.x += _speed * deltaTime;
	}
}

void TilemapActor::Render(HDC hdc)
{	
	Super::Render(hdc);

	if (_tilemap == nullptr)
		return;

	if (_showDebug == false)
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	int32 left = max(GWinSizeX / 2, _pos.x) - _pos.x;
	int32 top = max(0, _pos.y) - _pos.y;
	int32 right = min(GWinSizeX, _pos.x + mapSize.x * TILE_SIZEX) - _pos.x;
	int32 bottom = min(GWinSizeY, _pos.y + mapSize.y * TILE_SIZEY) - _pos.y;

	int32 startX = left / TILE_SIZEX;
	int32 startY = top / TILE_SIZEY;
	int32 endX = right / TILE_SIZEX;
	int32 endY = bottom / TILE_SIZEY;

	for (int32 y = startY; y < endY; y++)
	{
		for (int32 x = startX; x < endX; x++)
		{
			::TransparentBlt(hdc,
				_pos.x + x * TILE_SIZEX,
				_pos.y + y * TILE_SIZEY,
				TILE_SIZEX,
				TILE_SIZEY,
				_sprites[tiles[y][x].layer]->GetDC(),
				tiles[y][x].x * TILE_SIZEX,
				tiles[y][x].y * TILE_SIZEY,
				TILE_SIZEX,
				TILE_SIZEY,
				_sprites[tiles[y][x].layer]->GetTransparent());
		}
	}
}

void TilemapActor::SetTileAt(Tile tile)
{
	
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x - _pos.x;
		int32 posY = mousePos.y - _pos.y;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;
		
		_tilemap->SetTileAt(tile, { x, y });
	}

}
