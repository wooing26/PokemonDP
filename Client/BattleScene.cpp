#include "pch.h"
#include "BattleScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	Super::Init();
	GET_SINGLE(ResourceManager)->LoadTexture(L"BattleBG", L"Sprite\\Background\\Battle Backgrounds.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"TouchScreen", L"Sprite\\Background\\Touch Screen Backgrounds.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Pokemon_1st", L"Sprite\\Pokemon\\Pokemon 1st Generation.png", RGB(147, 187, 236));
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasDown", L"Sprite\\Player\\LucasDown.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_DryWater", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 0, 0, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_Land", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 800, 0, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_DiamondOpening", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 46, 16, 256, 192);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_Battle", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 307, 410, 256, 192);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"001_Bulbasaur", GET_SINGLE(ResourceManager)->GetTexture(L"Pokemon_1st"), 1 * 3 + 80 * 2, 33 + 1, 80, 80);
	

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Battle_DryWater");
		Vec2Int size = GetMainScreenSize();

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2});
		background->SetRenderSize(size);
		AddActor(background);
	}
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Battle_Land");
		Vec2Int size = GetMainScreenSize();

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });
		background->SetRenderSize(size);
		AddActor(background);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"TS_Battle");
		Vec2Int size = GetTouchScreenSize();
		Vec2Int pos = GetMainScreenSize();

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)pos.x + size.x / 2, (float)size.y / 2});
		background->SetRenderSize(size);
		AddActor(background);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LIdleDown");
		fb->SetInfo({ texture, L"FB_LIdleDown", {32, 32}, 0, 3, 0, 0.5f });

		FlipbookActor* player = new FlipbookActor();
		player->SetFlipbook(fb);
		player->SetLayer(LAYER_OBJECT);
		player->SetPos(Vec2{ 100, 100 });
		AddActor(player);
	}
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"001_Bulbasaur");
		Vec2Int size = sprite->GetSize();
		Vec2Int pos = GetMainScreenSize();

		size *= 3;
		SpriteActor* pokemon = new SpriteActor();
		pokemon->SetSprite(sprite);
		pokemon->SetLayer(LAYER_OBJECT);
		pokemon->SetPos(Vec2{ (float)size.x / 2, pos.y - (float)size.y / 2 });
		pokemon->SetRenderSize(size);
		AddActor(pokemon);
	}
	
}

void BattleScene::Update()
{
	Super::Update();
}

void BattleScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void BattleScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);
}

void BattleScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);
}
