#include "pch.h"
#include "Pokemon.h"
#include "InfoManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "Skill.h"

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
	_maxExp = _level * _level;
	_destExp = _maxExp;
}

void Pokemon::Tick()
{
	Super::Tick();

	if (_hp > _destHp)
		_hp--;
	else if (_hp < _destHp)
		_hp++;

	if (_exp > _destExp)
		_exp--;
	else if (_exp < _destExp)
	{
		_exp += 10;
		if (_exp > _destExp)
			_exp = _destExp;
		else if (_exp > _maxExp)
			_exp = _maxExp;
	}

	if (_exp >= _maxExp)
		int32 a = 3;
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
	// 상대방이 없으면 취소
	if (_target == nullptr)
		return;

	// 스킬 최대 보유 수보다 많으면 취소
	if (skillIndex >= 4)
		return;

	_target->OnDamaged(this, _skills[skillIndex]);
}

void Pokemon::OnDamaged(Pokemon* attacker, Skill* skill)
{
	const SkillInfo* info = skill->GetSkillInfo();

	// 명중률 계산
	int32 accuracy = std::rand() % 100 + 1;
	if (accuracy > info->accuracy)
		return;
	
	//(데미지 = (위력 × 공격 ×(레벨 × 2 ÷ 5 + 2) ÷ 방어 ÷ 50 × [[급소]] + 2)
	// × [[자속 보정]] × 타입상성1 × 타입상성2 × 랜덤수 / 255)

	// 급소 계산
	int32 criticalRate = std::rand() % 100 + 1;
	if (criticalRate <= 12)
		criticalRate = 2;
	else
		criticalRate = 1;

	// 공격력 및 방어력 계산
	PokemonStat attackerStat = attacker->GetStat();
	int32 attack, defense;
	switch (info->category)
	{
	case SkillCategory::Physical:
		attack = attackerStat.attack;
		defense = _stat.defense;
		break;
	case SkillCategory::Special:
		attack = attackerStat.specialAttack;
		defense = _stat.specialDefense;
		break;
	case SkillCategory::Status:
		break;
	}

	int32 damage = info->power * attack * (attacker->GetLevel() * 2 / 5 + 2) / defense / 50;
	damage = damage * criticalRate + 2;

}

void Pokemon::AddHp(int32 hp)
{
	_destHp += hp;
	if (_destHp < 0)
		_destHp = 0;
	else if (_destHp > _stat.hp)
		_destHp = _stat.hp;
}

void Pokemon::AddExp(int32 exp)
{
	_destExp += exp;
	if (_destExp < 0)
		_destExp = 0;
	
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

void Pokemon::AddSkill(Skill* skill)
{
	// 비어있는 스킬 인덱스 찾기
	int32 skillIndex = 0;
	while (_skills[skillIndex] != nullptr)
		skillIndex++;

	// 최대 스킬 보유 수보다 작으면 해당 인덱스에 스킬 할당
	if (skillIndex < 4)
		_skills[skillIndex] = skill;
}

void Pokemon::RemoveSkill(int32 skillIndex)
{
	if (skillIndex >= 4)
		return;

	if (_skills[skillIndex] == nullptr)
		return;

	SAFE_DELETE(_skills[skillIndex]);
}
