#include "pch.h"
#include "TileMapScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "FlipbookActor.h"

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::Init()
{
	Super::Init();
	
	//GET_SINGLE(ResourceManager)->LoadTexture();
}

void TileMapScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if(GET_SINGLE(InputManager)->GetButtonPress(KeyType::W))
	{
		_pos.y -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::S))
	{
		_pos.y += _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		_pos.x -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		_pos.x += _speed * deltaTime;
	}
}

void TileMapScene::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2Int from = Vec2Int{ (int)_pos.x - _tileSize, (int)_pos.y };
	Vec2Int to = Vec2Int{ (int)_pos.x - _tileSize, (int)_pos.y };
	to.y += _tileSize * 40;

	for (int i = 0; i <= 40; i++)
	{
		from.x += _tileSize;
		to.x += _tileSize;

		Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
	}
	from = Vec2Int{ (int)_pos.x, (int)_pos.y - _tileSize };
	to = Vec2Int{ (int)_pos.x, (int)_pos.y - _tileSize };
	to.x += _tileSize * 40;
	for (int i = 0; i <= 40; i++)
	{
		from.y += _tileSize;
		to.y += _tileSize;

		Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
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
