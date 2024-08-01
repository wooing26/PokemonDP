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

	GET_SINGLE(ResourceManager)->CreateSprite(L"Battle_DryWater", GET_SINGLE(ResourceManager)->GetTexture(L"BattleBG"), 17, 17, 256, 144);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_DiamondOpening", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 46, 16, 256, 192);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TS_Battle", GET_SINGLE(ResourceManager)->GetTexture(L"TouchScreen"), 307, 410, 256, 192);
	

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
