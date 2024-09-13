#include "pch.h"
#include "BattlePanel.h"
#include "TextBox.h"

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
		std::wstring pokemonName = L"거북왕";
		ui->SetTextZip({
			L"우왓! 야생의 리자몽이 나왔다!",
			std::format(L"가랏! {0}!", pokemonName),
			std::format(L"{0}은 무엇을 할까?", pokemonName)
			});
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
