#include "pch.h"
#include "BattleScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "BattlePanel.h"
#include "TextBox.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	// Battle Resource
	GET_SINGLE(ResourceManager)->LoadTexture(L"BattleBG", L"Sprite\\Background\\Battlegrounds.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"TouchScreen", L"Sprite\\Background\\Touch Screen Backgrounds.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Text_Boxes", L"Sprite\\UI\\Text Boxes.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"HP_Bars", L"Sprite\\UI\\HP.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Pokemon_1st", L"Sprite\\Pokemon\\Pokemon_Gen1.bmp");
	
	
	// Player Overworld
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasUp", L"Sprite\\Player\\LucasUp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasDown", L"Sprite\\Player\\LucasDown.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasLeft", L"Sprite\\Player\\LucasLeft.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasRight", L"Sprite\\Player\\LucasRight.bmp");

	// Battle Screen
	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_DryWater", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 0, 0, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_Land", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 800, 0, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_DiamondOpening", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 46, 16, 256, 192);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_Battle", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 307, 410, 256, 192);

	// UI
	GET_SINGLE(ResourceManager)->CreateSprite(L"TextBox", GET_SINGLE(ResourceManager)->GetTexture(L"Text_Boxes"), 0, 0, 250, 44);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"Enemy_HP_Male", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 0, 0, 120, 30);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Enemy_HP_Female", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 120, 0, 120, 30);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Enemy_HP_Genderless", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 240, 0, 120, 30);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"My_HP_Male", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 0, 30, 120, 41);
	GET_SINGLE(ResourceManager)->CreateSprite(L"My_HP_Female", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 120, 30, 120, 41);
	GET_SINGLE(ResourceManager)->CreateSprite(L"My_HP_Genderless", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 240, 30, 120, 41);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"LowHPBar", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 0, 71, 12, 7);
	GET_SINGLE(ResourceManager)->CreateSprite(L"MiddleHPBar", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 0, 78, 24, 7);
	GET_SINGLE(ResourceManager)->CreateSprite(L"HighHPBar", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 0, 85, 48, 7);
	GET_SINGLE(ResourceManager)->CreateSprite(L"EXPBar", GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 0, 92, 90, 3);

	// Number
	for (int32 i = 0; i < 10; i++)
	{
		GET_SINGLE(ResourceManager)->CreateSprite(std::to_wstring(i), GET_SINGLE(ResourceManager)->GetTexture(L"HP_Bars"), 100 + 8 * i, 100, 8, 7);
	}
	
	LoadMap();
	LoadTouchScreen();
	LoadPlayer();
	LoadPokemon();
	LoadUI();


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
		background->SetSize(size);
		AddActor(background);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"Battle_Land");
		Vec2Int size = GetMainScreenSize();
		fb->SetInfo({ texture, L"Battle_Land", { 256, 144 }, 3, 3, 0, 0.5f, false});

		FlipbookActor* background = new FlipbookActor();
		background->SetFlipbook(fb);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });
		background->SetSize(size);
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
		background->SetSize(size);
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
		Vec2Int size = { 80, 80 };
		int32 index = 10;
		fb->SetInfo({ texture, L"001_Bulbasaur", size, (index - 1) * 3 + 2, (index - 1) * 3 + 2, 0, 0.f, false });

		size *= 3;
		FlipbookActor* pokemon = new FlipbookActor();
		pokemon->SetFlipbook(fb);
		pokemon->SetLayer(LAYER_OBJECT);
		pokemon->SetPos({_myPos.x + size.x / 2, _myPos.y - size.y / 2});
		pokemon->SetSize(size);
		AddActor(pokemon);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Pokemon_1st");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"006_Charizard");
		Vec2Int size = { 80, 80 };
		int32 index = 7;
		fb->SetInfo({ texture, L"006_Charizard", size, (index - 1) * 3, (index - 1) * 3, 0, 0.f, false });

		size *= 3;
		FlipbookActor* pokemon = new FlipbookActor();
		pokemon->SetFlipbook(fb);
		pokemon->SetLayer(LAYER_OBJECT);
		pokemon->SetPos({ _enemyPos.x, _enemyPos.y - size.y / 4 });
		pokemon->SetSize(size);
		AddActor(pokemon);
	}
}

void BattleScene::LoadUI()
{
	{
		std::shared_ptr<BattlePanel> ui = std::make_shared<BattlePanel>();

		AddUI(ui);
	}
}
