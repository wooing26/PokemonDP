#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Button.h"
#include "EditPanel.h"

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"TilemapEditorButton", L"Sprite\\Miscellaneous\\TilemapEditorButton.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"BattleButton", L"Sprite\\Miscellaneous\\BattleButton.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"TilemapEditorButton_Off", GET_SINGLE(ResourceManager)->GetTexture(L"TilemapEditorButton"), 0, 0, 300, 143);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TilemapEditorButton_On", GET_SINGLE(ResourceManager)->GetTexture(L"TilemapEditorButton"), 0, 143, 300, 143);

	GET_SINGLE(ResourceManager)->CreateSprite(L"BattleButton_Off", GET_SINGLE(ResourceManager)->GetTexture(L"BattleButton"), 0, 0, 300, 143);
	GET_SINGLE(ResourceManager)->CreateSprite(L"BattleButton_On", GET_SINGLE(ResourceManager)->GetTexture(L"BattleButton"), 0, 143, 300, 143);

	{
		EditPanel* ui = new EditPanel();
		ui->SetPos({ 500, 1000 });

		AddUI(ui);
	}
	Super::Init();
}

void EditScene::Update()
{
	Super::Update();
}

void EditScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void EditScene::AddActor(Actor* actor)
{
}

void EditScene::RemoveActor(Actor* actor)
{
}
