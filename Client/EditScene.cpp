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
	SetSceneType(SceneType::EditScene);

	GET_SINGLE(ResourceManager)->LoadTexture(L"TilemapEditorButton", L"Sprite\\Miscellaneous\\TilemapEditorButton.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"BattleButton", L"Sprite\\Miscellaneous\\BattleButton.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"DevSceneButton", L"Sprite\\Miscellaneous\\DevSceneButton.bmp", RGB(128, 128, 128));

	GET_SINGLE(ResourceManager)->CreateSprite(L"TilemapEditorButton_Off", GET_SINGLE(ResourceManager)->GetTexture(L"TilemapEditorButton"), 0, 0, 300, 143);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TilemapEditorButton_On", GET_SINGLE(ResourceManager)->GetTexture(L"TilemapEditorButton"), 0, 143, 300, 143);

	GET_SINGLE(ResourceManager)->CreateSprite(L"BattleButton_Off", GET_SINGLE(ResourceManager)->GetTexture(L"BattleButton"), 0, 0, 300, 143);
	GET_SINGLE(ResourceManager)->CreateSprite(L"BattleButton_On", GET_SINGLE(ResourceManager)->GetTexture(L"BattleButton"), 0, 143, 300, 143);

	GET_SINGLE(ResourceManager)->CreateSprite(L"DevSceneButton_Off", GET_SINGLE(ResourceManager)->GetTexture(L"DevSceneButton"), 0, 0, 300, 143);
	GET_SINGLE(ResourceManager)->CreateSprite(L"DevSceneButton_On", GET_SINGLE(ResourceManager)->GetTexture(L"DevSceneButton"), 0, 143, 300, 143);

	{
		std::shared_ptr<EditPanel> ui = std::make_shared<EditPanel>();

		ui->SetPos({ GWinSizeX / 2, GWinSizeY * 2 / 3 });
		AddUI(ui);
	}
	Super::Init();
}

void EditScene::Update()
{
	Super::Update();

	SceneType sceneType = GetSceneType();

	if (sceneType != SceneType::EditScene)
	{
		GET_SINGLE(SceneManager)->ChangeScene(sceneType);
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
