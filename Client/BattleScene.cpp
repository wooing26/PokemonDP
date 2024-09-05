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
	GET_SINGLE(ResourceManager)->LoadTexture(L"BattleBG", L"Sprite\\Background\\Battle Backgrounds.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"TouchScreen", L"Sprite\\Background\\Touch Screen Backgrounds.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Celadon_City", L"Sprite\\Background\\Celadon City.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Pokemon_1st", L"Sprite\\Pokemon\\Pokemon_Gen1.bmp");
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasUp", L"Sprite\\Player\\LucasUp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasDown", L"Sprite\\Player\\LucasDown.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasLeft", L"Sprite\\Player\\LucasLeft.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasRight", L"Sprite\\Player\\LucasRight.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_DryWater", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 0, 0, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_Land", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 800, 0, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_DiamondOpening", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 46, 16, 256, 192);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_Battle", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 307, 410, 256, 192);

	
	LoadMap();
	LoadTouchScreen();
	LoadPlayer();
	LoadPokemon();

	Super::Init();
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

void BattleScene::LoadMap()
{
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Battle_DryWater");
		Vec2Int size = GetMainScreenSize();

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });
		background->SetRenderRatio(1.f);
		AddActor(background);
	}
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Battle_Land");
		Vec2Int size = GetMainScreenSize();

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });
		background->SetRenderRatio(1.f);
		AddActor(background);
	}
}

void BattleScene::LoadTouchScreen()
{
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"TS_Battle");
		Vec2Int size = GetTouchScreenSize();
		Vec2Int pos = GetMainScreenSize();

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)pos.x + size.x / 2, (float)size.y / 2 });
		background->SetRenderRatio(1.f);
		AddActor(background);
	}
}

void BattleScene::LoadPlayer()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LIdleDown");
		fb->SetInfo({ texture, L"FB_LIdleDown", {32, 32}, 0, 3, 0, 0.5f });

		FlipbookActor* player = new FlipbookActor();
		player->SetFlipbook(fb);
		player->SetLayer(LAYER_OBJECT);
		player->SetPos(Vec2{ 1025, 150 });
		AddActor(player);
	}
	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasMoveUp");
		fb->SetInfo({ texture, L"FB_LucasMoveUp", {32, 32}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasMoveDown");
		fb->SetInfo({ texture, L"FB_LucasMoveDown", {32, 32}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasMoveLeft");
		fb->SetInfo({ texture, L"FB_LucasMoveLeft", {32, 32}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasMoveRight");
		fb->SetInfo({ texture, L"FB_LucasMoveRight", {32, 32}, 0, 3, 0, 0.5f });
	}
}

void BattleScene::LoadPokemon()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Pokemon_1st");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"001_Bulbasaur");
		fb->SetInfo({ texture, L"001_Bulbasaur", {80, 80}, 2, 2, 0, 0.f, false });

		FlipbookActor* pokemon = new FlipbookActor();
		pokemon->SetFlipbook(fb);
		pokemon->SetLayer(LAYER_OBJECT);
		pokemon->SetPos(_myPos + Vec2{ 40, -40 } *3);
		AddActor(pokemon);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Pokemon_1st");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"006_Charizard");
		fb->SetInfo({ texture, L"006_Charizard", {80, 80}, (7 - 1) * 3, (7 - 1) * 3, 0, 0.f, false });

		FlipbookActor* pokemon = new FlipbookActor();
		pokemon->SetFlipbook(fb);
		pokemon->SetLayer(LAYER_OBJECT);
		pokemon->SetPos(_enemyPos + Vec2{ -40, 40 } *3);
		AddActor(pokemon);
	}
}
