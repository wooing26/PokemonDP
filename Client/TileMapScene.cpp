#include "pch.h"
#include "TileMapScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Sprite.h"
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
	Super::Init();
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"buildings", L"Sprite\\Tile\\TileSet\\buildings (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"caves", L"Sprite\\Tile\\TileSet\\caves (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"mounts", L"Sprite\\Tile\\TileSet\\mounts (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"nature", L"Sprite\\Tile\\TileSet\\nature (HGSS).png");

	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT Buildings", L"Sprite\\Tile\\TileSet\\PLAT Buildings.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT Nature", L"Sprite\\Tile\\TileSet\\PLAT Mount.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT Nature", L"Sprite\\Tile\\TileSet\\PLAT Nature.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT Nature", L"Sprite\\Tile\\TileSet\\PLAT Props.png");
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"borders", L"Sprite\\Tile\\TileSet\\borders.png");

	GET_SINGLE(ResourceManager)->CreateSprite(L"borders", GET_SINGLE(ResourceManager)->GetTexture(L"borders"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT Nature", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT Nature"), 0, 0);


	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"borders");
		Vec2Int size = sprite->GetSize();

		SetMapSize(Vec2(size.x, size.y));
		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });
		AddActor(background);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"PLAT Nature");
		Vec2Int size = sprite->GetSize();

		SetMapSize(Vec2(size.x, size.y));
		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_OBJECT);
		background->SetPos(Vec2{ (float)size.x / 2 + GWinSizeX / 2, (float)size.y / 2});
		AddActor(background);
	}
}

void TileMapScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

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

	GET_SINGLE(SceneManager)->SetCameraPos(_cameraPos);

	
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		_cellPos.x = (mousePos.x - (_cameraPos.x - GWinSizeX / 2))/ _tileSize;
		_cellPos.y = (mousePos.y - (_cameraPos.y - GWinSizeY / 2))/ _tileSize;
		_startCellPos.push_back(_cellPos);
	}
	else if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::LeftMouse))
	{
		_cellPos.x = (mousePos.x - (_cameraPos.x - GWinSizeX / 2)) / _tileSize;
		_cellPos.y = (mousePos.y - (_cameraPos.y - GWinSizeY / 2)) / _tileSize;
		_endCellPos.push_back(_cellPos);
	}
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
