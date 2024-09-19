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
	Vec2Int size = GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1On")->GetSize();
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_1On"), BS_Clicked);
		ui->SetSize(size);
		ui->SetPos({ _pos.x + size.x  / 2, _pos.y + size.y / 2});

		ui->AddOnClickDelegate(this, &LayerPanel::OnClickLayerButton0);
		AddChild(ui);
	}
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_2Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_2On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_2On"), BS_Clicked);
		ui->SetSize(size);
		ui->SetPos({ _pos.x + size.x * 3/ 2, _pos.y + size.y / 2 });

		ui->AddOnClickDelegate(this, &LayerPanel::OnClickLayerButton1);
		AddChild(ui);
	}
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_3Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_3On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_3On"), BS_Clicked);
		ui->SetSize(size);
		ui->SetPos({ _pos.x + size.x * 5 / 2, _pos.y + size.y / 2 });

		ui->AddOnClickDelegate(this, &LayerPanel::OnClickLayerButton2);
		AddChild(ui);
	}
	{
		std::shared_ptr<Button> ui = std::make_shared<Button>();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_4Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_4On"), BS_Pressed);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Layer_4On"), BS_Clicked);
		ui->SetSize(size);
		ui->SetPos({ _pos.x + size.x * 7 / 2, _pos.y + size.y / 2 });

		ui->AddOnClickDelegate(this, &LayerPanel::OnClickLayerButton3);
		AddChild(ui);
	}

	Super::BeginPlay();

	// Layer1 클릭 이미지로 변환
	std::shared_ptr<UI> ui = GetChild(_selectedLayer);

	std::shared_ptr<Button> button = std::static_pointer_cast<Button>(ui);
	button->SetButtonState(BS_Clicked);

	_rect =
	{
		(int32)_pos.x,
		(int32)_pos.y,
		(int32)_pos.x + size.x * 4,
		(int32)_pos.y + size.y
	};
}

void LayerPanel::Tick()
{
	Super::Tick();
}

void LayerPanel::Render(HDC hdc)
{
	Super::Render(hdc);
}

void LayerPanel::OnClickLayerButton0()
{
	if (_selectedLayer == 0)
		return;

	std::shared_ptr<UI> ui = GetChild(_selectedLayer);
	
	std::shared_ptr<Button> button = std::static_pointer_cast<Button>(ui);
	button->SetButtonState(BS_Default);

	_selectedLayer = 0;
}

void LayerPanel::OnClickLayerButton1()
{
	if (_selectedLayer == 1)
		return;
	
	std::shared_ptr<UI> ui = GetChild(_selectedLayer);

	std::shared_ptr<Button> button = std::static_pointer_cast<Button>(ui);
	button->SetButtonState(BS_Default);

	_selectedLayer = 1;
}

void LayerPanel::OnClickLayerButton2()
{
	if (_selectedLayer == 2)
		return;
	
	std::shared_ptr<UI> ui = GetChild(_selectedLayer);

	std::shared_ptr<Button> button = std::static_pointer_cast<Button>(ui);
	button->SetButtonState(BS_Default);

	_selectedLayer = 2;
}

void LayerPanel::OnClickLayerButton3()
{
	if (_selectedLayer == 3)
		return;

	std::shared_ptr<UI> ui = GetChild(_selectedLayer);

	std::shared_ptr<Button> button = std::static_pointer_cast<Button>(ui);
	button->SetButtonState(BS_Default);

	_selectedLayer = 3;
}


