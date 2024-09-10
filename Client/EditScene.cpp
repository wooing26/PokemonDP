#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
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
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"BattleButton_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"BattleButton_On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"BattleButton_Off"), BS_Clicked);
		ui->SetPos({ 500, 1000 });

		ui->AddOnClickDelegate(this, &EditScene::ChangeBattle);

		AddUI(ui);
	}
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();

		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"TilemapEditorButton_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"TilemapEditorButton_On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"TilemapEditorButton_Off"), BS_Clicked);
		ui->SetPos({ 1000, 1000 });

		ui->AddOnClickDelegate(this, &EditScene::ChangeTilemap);

		AddUI(ui);
	}
	Super::Init();
}

void EditScene::Update()
{
	Super::Update();

	if (_sceneType != SceneType::EditScene)
	{
		GET_SINGLE(SceneManager)->ChangeScene(_sceneType);
	}
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

void EditScene::ChangeBattle()
{
	_sceneType = SceneType::BattleScene;
}

void EditScene::ChangeTilemap()
{
	_sceneType = SceneType::TileMapScene;
}
