#include "pch.h"
#include "TileMapScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "FlipbookActor.h"
#include "SpriteActor.h"
#include "TilemapActor.h"

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"buildings", L"Sprite\\Tile\\TileSet\\buildings (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"caves", L"Sprite\\Tile\\TileSet\\caves (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"mounts", L"Sprite\\Tile\\TileSet\\mounts (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"nature", L"Sprite\\Tile\\TileSet\\nature (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"props", L"Sprite\\Tile\\TileSet\\props (HGSS).png");

	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Buildings", L"Sprite\\Tile\\TileSet\\PLAT Buildings.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Mount", L"Sprite\\Tile\\TileSet\\PLAT Mount.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Nature", L"Sprite\\Tile\\TileSet\\PLAT Nature.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Props", L"Sprite\\Tile\\TileSet\\PLAT Props.png");
	

	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasDown", L"Sprite\\Player\\LucasDown.bmp");

	GET_SINGLE(ResourceManager)->LoadTexture(L"borders", L"Sprite\\Tile\\TileSet\\borders.png");

	GET_SINGLE(ResourceManager)->CreateSprite(L"borders", GET_SINGLE(ResourceManager)->GetTexture(L"borders"), 0, 0);

	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Buildings", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Buildings"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Mount", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Mount"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Nature", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Nature"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Props", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Props"), 0, 0);


	{
		TilemapActor* actor = new TilemapActor();
		actor->SetPos({ GWinSizeX / 2, 0 });
		_tilemapActor = actor;
		AddActor(actor);

		Tilemap* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
		tm->SetMapSize({ 40, 40 });
		tm->SetTileSize(32);

		actor->SetTilemap(tm);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Nature");
		Vec2Int size = sprite->GetSize();

		SetMapSize(Vec2(size.x, size.y));
		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2});
		AddActor(background);
		_spriteActor = background;
	}

	Super::Init();
}

void TileMapScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Move Camera Pos
	if(GET_SINGLE(InputManager)->GetButtonPress(KeyType::W))
	{
		_cameraPos.y -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::S))
	{
		_cameraPos.y += _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		_cameraPos.x -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		_cameraPos.x += _speed * deltaTime;
	}

	// Edit Tilemap
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	if (IsMouseInSelect(mousePos))
	{
		if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::LeftMouse))
		{
			Vec2 selectedPos = { (mousePos.x + (_cameraPos.x - GWinSizeX / 2)), (mousePos.y + (_cameraPos.y - GWinSizeY / 2)) };
			
			if (0 <= selectedPos.x && selectedPos.x <= _mapSize.x
				&& 0 <= selectedPos.y && selectedPos.y <= _mapSize.y)
			{
				_selectedTilePos.x = selectedPos.x / _tileSize;
				_selectedTilePos.y = selectedPos.y / _tileSize;
			}
		}
	}
	else if (IsMouseInEdit(mousePos))
	{
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LeftMouse))
		{
			_tilemapActor->SetTileAt({ _tilemapLayer,_selectedTilePos.x, _selectedTilePos.y });
		}
	}
	
	// Save or Load Tilemap
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Sprite\\Tile\\Tilemap01.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Sprite\\Tile\\Tilemap01.txt");
	}

	// Change Sprite
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_1))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Buildings"));
		_tilemapLayer = TileMap_LAYER::PLAT_Buildings;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_2))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Mount"));
		_tilemapLayer = TileMap_LAYER::PLAT_Mount;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_3))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Nature"));
		_tilemapLayer = TileMap_LAYER::PLAT_Nature;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_4))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Props"));
		_tilemapLayer = TileMap_LAYER::PLAT_Props;
	}

	GET_SINGLE(SceneManager)->SetCameraPos(_cameraPos);
}

void TileMapScene::Render(HDC hdc)
{
	Super::Render(hdc);

	int32 MaxX = min(_mapSize.x - (_cameraPos.x - GWinSizeX / 2) + 1, GWinSizeX);
	int32 MaxY = min(_mapSize.y - (_cameraPos.y - GWinSizeY / 2) + 1, GWinSizeY);

	Vec2Int from = Vec2Int{ - ((int32)_cameraPos.x - GWinSizeX / 2), - ((int32)_cameraPos.y - GWinSizeY / 2) };
	Vec2Int to = from;
	to.y += _mapSize.y;

	while (from.x <= MaxX)
	{	
		if (from.x >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
		
		from.x += _tileSize;
		to.x += _tileSize;
	}

	from = Vec2Int{ - ((int32)_cameraPos.x - GWinSizeX / 2), - ((int32)_cameraPos.y - GWinSizeY / 2) };
	to = from;
	to.x += _mapSize.x;
	while (from.y <= MaxY)
	{
		if (from.y >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
		
		from.y += _tileSize;
		to.y += _tileSize;
	}
}

void TileMapScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);
}

void TileMapScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);
}

bool TileMapScene::IsMouseInSelect(POINT mousePos)
{
	RECT rect =
	{
		0,
		0,
		GWinSizeX / 2,
		GWinSizeY 
	};

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}

bool TileMapScene::IsMouseInEdit(POINT mousePos)
{
	RECT rect =
	{ 
		GWinSizeX / 2,
		0,
		GWinSizeX,
		GWinSizeY 
	};

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}

void TileMapScene::ChangeSelectedSprite(Sprite* sprite)
{
	Vec2Int size = sprite->GetSize();

	SetMapSize(Vec2(size.x, size.y));
	_spriteActor->SetSprite(sprite);
	_spriteActor->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });

	_selectedTilePos = { 0, 0 };

	_cameraPos = { GWinSizeX / 2, GWinSizeY / 2 };
}
