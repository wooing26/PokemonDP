#include "pch.h"
#include "BattlePanel.h"
#include "TextBox.h"
#include "HpBar.h"

BattlePanel::BattlePanel()
{
}

BattlePanel::~BattlePanel()
{
}

void BattlePanel::BeginPlay()
{
	{
		std::shared_ptr<TextBox> ui = std::make_shared<TextBox>();

		ui->SetTextStyle(TextStyle::BattleText);
		std::wstring pokemonName = L"�̻��ؾ�";
		ui->SetTextZip({
			L"���! �߻��� ���ڸ��� ���Դ�!",
			std::format(L"����! {0}!", pokemonName),
			std::format(L"{0}�� ������ �ұ�?", pokemonName)
			});
		AddChild(ui);
	}

	{
		std::shared_ptr<HpBar> ui = std::make_shared<HpBar>();

		AddChild(ui);
	}

	{
		std::shared_ptr<HpBar> ui = std::make_shared<HpBar>();
		
		ui->SetIsMine(false);
		AddChild(ui);
	}

	Super::BeginPlay();
}

void BattlePanel::Tick()
{
	Super::Tick();
}

void BattlePanel::Render(HDC hdc)
{
	Super::Render(hdc);
}
