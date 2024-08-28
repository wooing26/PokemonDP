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

	{
		std::wstring textureName = L"PLAT_Nature";
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(textureName);
		
		Vec2Int size = texture->GetSize();
		int32 tileCountX = size.x / TILE_SIZEX;
		int32 tileCountY = size.y / TILE_SIZEY;
		
		_sprites[TileMap_LAYER::PLAT_Nature].resize(tileCountY, std::vector<Sprite*>(tileCountX, nullptr));
		
		for (int32 y = 0; y < tileCountY; y++)
		{
			for (int32 x = 0; x < tileCountX; x++)
			{
				std::wstring key = std::format(L"{0}[{1}][{2}]", textureName, y, x);
				_sprites[TileMap_LAYER::PLAT_Nature][y][x] = GET_SINGLE(ResourceManager)->CreateSprite(key, texture, x * TILE_SIZEX, y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
			}
		}
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
	const int32 tileSize = _tilemap->GetTileSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	int32 left = max(GWinSizeX / 2, _pos.x);

	for (int32 y = 0; y < mapSize.y; y++)
	{
		for (int32 x = 0; x < mapSize.x; x++)
		{
			::TransparentBlt(hdc,
				_pos.x + x * TILE_SIZEX,
				_pos.y + y * TILE_SIZEY,
				TILE_SIZEX,
				TILE_SIZEY,
				_sprites[tiles[y][x].layer][tiles[y][x].y][tiles[y][x].x]->GetDC(),
				_sprites[tiles[y][x].layer][tiles[y][x].y][tiles[y][x].x]->GetPos().x,
				_sprites[tiles[y][x].layer][tiles[y][x].y][tiles[y][x].x]->GetPos().y,
				TILE_SIZEX,
				TILE_SIZEY,
				_sprites[tiles[y][x].layer][tiles[y][x].y][tiles[y][x].x]->GetTransparent());
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
