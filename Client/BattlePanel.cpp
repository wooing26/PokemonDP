#include "pch.h"
#include "BattlePanel.h"
#include "TextBox.h"
#include "HpBar.h"
#include "Pokemon.h"

BattlePanel::BattlePanel()
{
}

BattlePanel::~BattlePanel()
{
}

void BattlePanel::BeginPlay()
{
	if (_myPokemon == nullptr || _enemyPokemon == nullptr)
		return;

	{
		std::shared_ptr<TextBox> ui = std::make_shared<TextBox>();

		ui->SetTextStyle(TextStyle::BattleText);
		std::wstring pokemonName = _myPokemon->GetName();
		ui->SetTextZip({
			std::format(L"우왓! 야생의 {}이 나왔다!", _enemyPokemon->GetName()),
			std::format(L"가랏! {0}!", pokemonName),
			std::format(L"{0}은 무엇을 할까?", pokemonName)
			});
		AddChild(ui);
	}

	{
		std::shared_ptr<HpBar> ui = std::make_shared<HpBar>();
		ui->SetPokemon(_myPokemon);

		AddChild(ui);
	}

	{
		std::shared_ptr<HpBar> ui = std::make_shared<HpBar>();
		
		ui->SetIsMine(false);
		ui->SetPokemon(_enemyPokemon);

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

void BattlePanel::SetMyPokemon(Pokemon* pokemon)
{
	if (pokemon == nullptr)
		return;

	_myPokemon = pokemon;
}

void BattlePanel::SetEnemyPokemon(Pokemon* pokemon)
{
	if (pokemon == nullptr)
		return;

	_enemyPokemon = pokemon;
}
