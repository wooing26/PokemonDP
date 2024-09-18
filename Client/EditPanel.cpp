#include "pch.h"
#include "EditPanel.h"
#include "Button.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

EditPanel::EditPanel()
{
	
}

EditPanel::~EditPanel()
{

}

void EditPanel::BeginPlay()
{
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"BattleButton_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"BattleButton_On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"BattleButton_Off"), BS_Clicked);
		ui->SetPos({ _pos.x - 300, _pos.y });

		ui->AddOnClickDelegate(this, &EditPanel::OnClickBattleButton);
		AddChild(ui);
	}
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"TilemapEditorButton_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"TilemapEditorButton_On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"TilemapEditorButton_Off"), BS_Clicked);
		ui->SetPos({ _pos.x + 300, _pos.y });

		ui->AddOnClickDelegate(this, &EditPanel::OnClickTilemapButton);
		AddChild(ui);
	}

	Super::BeginPlay();
}

void EditPanel::Tick()
{
	Super::Tick();
}

void EditPanel::Render(HDC hdc)
{
	Super::Render(hdc);
}

void EditPanel::OnClickTilemapButton()
{
	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
	scene->SetSceneType(SceneType::TileMapScene);
}

void EditPanel::OnClickBattleButton()
{
	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
	scene->SetSceneType(SceneType::BattleScene);
}
