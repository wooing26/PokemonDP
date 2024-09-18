#include "pch.h"
#include "LayerPanel.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Button.h"

LayerPanel::LayerPanel()
{
}

LayerPanel::~LayerPanel()
{
}

void LayerPanel::BeginPlay()
{
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1On"), BS_Clicked);
		ui->SetSize(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1On")->GetSize());
		ui->SetPos({ _pos.x - _size.x / 2, _pos.y - _size.y / 2});

		ui->AddOnClickDelegate(this, &LayerPanel::OnClickLayerButton);
		AddChild(ui);
	}

	Super::BeginPlay();
}

void LayerPanel::Tick()
{
	Super::Tick();
}

void LayerPanel::Render(HDC hdc)
{
	Super::Render(hdc);
}

void LayerPanel::OnClickLayerButton()
{
}
