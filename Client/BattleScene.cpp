#include "pch.h"
#include "BattleScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "Pokemon.h"
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
	GET_SINGLE(ResourceManager)->LoadTexture(L"Pokemon_2nd", L"Sprite\\Pokemon\\Pokemon_Gen2.bmp");

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

}

void BattleScene::LoadPokemon()
{
	{
		Pokemon* pokemon = new Pokemon(1);

		pokemon->SetPos({_myPos.x, _myPos.y - 80 * 3 / 2});
		_myPokemon = pokemon;
		
		AddActor(pokemon);
	}
	{
		Pokemon* pokemon = new Pokemon(6);

		pokemon->SetIsMine(false);
		pokemon->SetPos({ _enemyPos.x, _enemyPos.y - 80 * 3 / 2 });

		_enemyPokemon = pokemon;
		
		AddActor(pokemon);
	}
}

void BattleScene::LoadUI()
{
	{
		std::shared_ptr<BattlePanel> ui = std::make_shared<BattlePanel>();
		
		ui->SetMyPokemon(_myPokemon);
		ui->SetEnemyPokemon(_enemyPokemon);

		AddUI(ui);
	}
}
