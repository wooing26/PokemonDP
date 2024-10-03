#include "pch.h"
#include "Pokemon.h"
#include "InfoManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"

Pokemon::Pokemon()
{
}

Pokemon::Pokemon(int32 No)
{
	_info = GET_SINGLE(InfoManager)->GetPokemonInfo(No);
	_baseStat = GET_SINGLE(InfoManager)->GetPokemonStat(No);

	std::wstring textureName;

	// 세대별 texture 이름
	switch (_info->generation)
	{
	case 1:
		textureName = L"Pokemon_1st";
		break;
	case 2:
		textureName = L"Pokemon_2nd";
		break;
	}
	
	// 내 포켓몬 전투
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(textureName);
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(_info->name + L"Mine");
		fb->SetInfo({ texture, _info->name, { 80, 80 }, _info->start * 3 + 2, _info->start * 3 + 2, _info->line, 0.f, false });

		_flipbookBattle[0] = fb;
	}
	// 상대 포켓몬 전투
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(textureName);
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(_info->name + L"Enemy");
		fb->SetInfo({ texture, _info->name, { 80, 80 }, _info->start * 3, _info->start * 3, _info->line, 0.f, false });

		_flipbookBattle[1] = fb;
	}
}

Pokemon::~Pokemon()
{
}

void Pokemon::BeginPlay()
{
	Super::BeginPlay();

	SetLayer(LAYER_OBJECT);
	if (_isMine)
	{
		SetFlipbook(_flipbookBattle[0]);
	}
	else
	{
		SetFlipbook(_flipbookBattle[1]);
	}

	SetSize({ 80 * 3, 80 * 3 });

	// 레벨
	_level = 10;

	// 최대 체력
	_stat.hp = ((2 * _baseStat->hp + 100) * _level / 100) + 10;

	// 실제 스탯
	_stat.attack = ((2 * _baseStat->attack) * _level / 100 + 5);
	_stat.defense = ((2 * _baseStat->defense) * _level / 100 + 5);
	_stat.specialAttack = ((2 * _baseStat->specialAttack) * _level / 100 + 5);
	_stat.specialDefense = ((2 * _baseStat->specialDefense) * _level / 100 + 5);
	_stat.speed = ((2 * _baseStat->speed) * _level / 100 + 5);

	// 필요 경험치
	_maxExp = _level * _level * _level;
}

void Pokemon::Tick()
{
	Super::Tick();
}

void Pokemon::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Pokemon::TickIdle()
{
}

void Pokemon::TickMove()
{
}

void Pokemon::TickBattle()
{
}

void Pokemon::UpdateAnimation()
{
}

const std::wstring& Pokemon::GetName()
{
	return _info->name;
}

void Pokemon::UseSkill(int32 skillIndex)
{
}

void Pokemon::OnDamaged(Pokemon* attacker)
{
}

void Pokemon::AddHp(int32 hp)
{
	if (hp > _stat.hp - _hp)
		_hp = _stat.hp;
	else
		_hp += hp;
}

void Pokemon::AddExp(int32 exp)
{
	if (exp > _maxExp - _exp)
		_exp = _maxExp;
	else
		_exp += exp;
}

void Pokemon::LevelUp()
{
	// 레벨 업
	_level++;
	// 최대 체력
	_stat.hp = ((2 * _baseStat->hp + 100) * _level / 100) + 10;

	// 실제 스탯
	_stat.attack = ((2 * _baseStat->attack) * _level / 100 + 5);
	_stat.defense = ((2 * _baseStat->defense) * _level / 100 + 5);
	_stat.specialAttack = ((2 * _baseStat->specialAttack) * _level / 100 + 5);
	_stat.specialDefense = ((2 * _baseStat->specialDefense) * _level / 100 + 5);
	_stat.speed = ((2 * _baseStat->speed) * _level / 100 + 5);

	// 필요 경험치
	_maxExp = _level * _level * _level;
}
