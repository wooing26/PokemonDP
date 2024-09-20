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
	
	std::wstring texture[Tilemap_TYPE::MAXCOUNT] = { L"PLAT_Buildings", L"PLAT_Mount", L"PLAT_Nature", L"PLAT_Props",
		L"Buildings", L"Caves", L"Mounts", L"Nature", L"Props"};

	for (int32 i = 0; i < Tilemap_TYPE::MAXCOUNT; i++)
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

	int32 startX = 0;
	int32 startY = 0;
	int32 endX = mapSize.x;
	int32 endY = mapSize.y;

	if (_showAll == false)
	{
		startX = left / TILE_SIZEX;
		startY = top / TILE_SIZEY ;
		endX = right / TILE_SIZEX;
		endY = bottom / TILE_SIZEY;
	}

	for (int32 y = startY; y < endY; y++)
	{
		for (int32 x = startX; x < endX; x++)
		{
			if (x >= 0 && y >= 0)
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX,
					_pos.y + y * TILE_SIZEY,
					TILE_SIZEX,
					TILE_SIZEY,
					_sprites[tiles[y][x].type]->GetDC(),
					tiles[y][x].x * TILE_SIZEX,
					tiles[y][x].y * TILE_SIZEY,
					TILE_SIZEX,
					TILE_SIZEY,
					_sprites[tiles[y][x].type]->GetTransparent());
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
