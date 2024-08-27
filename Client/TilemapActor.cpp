#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "InputManager.h"


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

	//TickPicking();
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

}

void TilemapActor::TickPicking()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({x, y});
		
	}

}
