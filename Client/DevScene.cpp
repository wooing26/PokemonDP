#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Player.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	// Player Overworld
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasUp", L"Sprite\\Player\\LucasUp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasDown", L"Sprite\\Player\\LucasDown.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasLeft", L"Sprite\\Player\\LucasLeft.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasRight", L"Sprite\\Player\\LucasRight.bmp");

	LoadMap();
	LoadPlayer(); 
	LoadPokemon();
	LoadUI();

	{
		Player* player = new Player();
		AddActor(player);
	}
	

	Super::Init();
}
void DevScene::Update()
{
	Super::Update();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void DevScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);
}

void DevScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);
}

void DevScene::LoadMap()
{
}

void DevScene::LoadPlayer()
{
	// Idle
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasUp_Idle");
		fb->SetInfo({ texture, L"FB_LucasUp_Idle", {32, 32}, 0, 0, 0, 0.5f, false});
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasDown_Idle");
		fb->SetInfo({ texture, L"FB_LucasDown_Idle", {32, 32}, 0, 0, 0, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasLeft_Idle");
		fb->SetInfo({ texture, L"FB_LucasLeft_Idle", {32, 32}, 0, 0, 0, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasRight_Idle");
		fb->SetInfo({ texture, L"FB_LucasRight_Idle", {32, 32}, 0, 0, 0, 0.5f, false });
	}

	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasUp_Move");
		fb->SetInfo({ texture, L"FB_LucasUp_Move", {32, 32}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasDown_Move");
		fb->SetInfo({ texture, L"FB_LucasDown_Move", {32, 32}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasLeft_Move");
		fb->SetInfo({ texture, L"FB_LucasLeft_Move", {32, 32}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasRight_Move");
		fb->SetInfo({ texture, L"FB_LucasRight_Move", {32, 32}, 0, 3, 0, 0.5f });
	}

	// Run
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasUp_Run");
		fb->SetInfo({ texture, L"FB_LucasUp_Run", {32, 32}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasDown_Run");
		fb->SetInfo({ texture, L"FB_LucasDown_Run", {32, 32}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasLeft_Run");
		fb->SetInfo({ texture, L"FB_LucasLeft_Run", {32, 32}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasRight_Run");
		fb->SetInfo({ texture, L"FB_LucasRight_Run", {32, 32}, 0, 3, 1, 0.5f });
	}

	// Bicycle
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasUp_Bicycle");
		fb->SetInfo({ texture, L"FB_LucasUp_Bicycle", {32, 32}, 0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasDown_Bicycle");
		fb->SetInfo({ texture, L"FB_LucasDown_Bicycle", {32, 32}, 0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasLeft_Bicycle");
		fb->SetInfo({ texture, L"FB_LucasLeft_Bicycle", {32, 32}, 0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasRight_Bicycle");
		fb->SetInfo({ texture, L"FB_LucasRight_Bicycle", {32, 32}, 0, 3, 2, 0.5f });
	}

	// Bicycle Idle
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasUp_BicycleIdle");
		fb->SetInfo({ texture, L"FB_LucasUp_BicycleIdle", {32, 32}, 0, 0, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasDown_BicycleIdle");
		fb->SetInfo({ texture, L"FB_LucasDown_BicycleIdle", {32, 32}, 0, 0, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasLeft_BicycleIdle");
		fb->SetInfo({ texture, L"FB_LucasLeft_BicycleIdle", {32, 32}, 0, 0, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LucasRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LucasRight_BicycleIdle");
		fb->SetInfo({ texture, L"FB_LucasRight_BicycleIdle", {32, 32}, 0, 0, 3, 0.5f, false });
	}
}

void DevScene::LoadPokemon()
{
}

void DevScene::LoadUI()
{
}
