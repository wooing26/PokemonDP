#include "pch.h"
#include "BattleScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	Super::Init();
	GET_SINGLE(ResourceManager)->LoadTexture(L"BattleBG", L"Sprite\\Background\\Battle Backgrounds.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"TouchScreen", L"Sprite\\Background\\Touch Screen Backgrounds.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Pokemon_1st", L"Sprite\\Pokemon\\Pokemon 1st Generation.bmp", RGB(147, 187, 236));

	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_DryWater", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 17, 17, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_DiamondOpening", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 46, 16, 256, 192);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_Battle", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 307, 410, 256, 192);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"001_Bulbasaur", GET_SINGLE(ResourceManager)->GetTexture(L"Pokemon_1st"), 1 * 3 + 80 * 2, 33 + 1, 80, 80);

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Battle_DryWater");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ GWinSizeX / 4, GWinSizeY / 2 });
		AddActor(background);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"TS_Battle");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ GWinSizeX * 3 / 4, GWinSizeY / 2 });
		AddActor(background);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"001_Bulbasaur");
		Vec2Int size = sprite->GetSize();

		SpriteActor* pokemon = new SpriteActor();
		pokemon->SetSprite(sprite);
		pokemon->SetLayer(LAYER_OBJECT);
		pokemon->SetPos(Vec2{ 500, GWinSizeY / 2 });
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
