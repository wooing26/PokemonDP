#pragma once
#include "Creature.h"

class Skill;

struct PokemonInfo
{
	int32			No = 0;
	std::wstring	name = L"MissingNo.";
	int32			generation = 1;
	int32			line = 0;
	int32			start = 0;
	bool			separateGender = false;
	PokeType		type1 = PokeType::None;
	PokeType		type2 = PokeType::None;
};

struct PokemonStat
{
	int32			hp = 0;
	int32			attack = 0;
	int32			defense = 0;
	int32			specialAttack = 0;
	int32			specialDefense = 0;
	int32			speed = 0;
	int32			total = 0;
};

class Pokemon : public Creature
{
	using Super = Creature;
public:
	Pokemon();
	Pokemon(int32 No);
	virtual ~Pokemon() override;

	virtual void		BeginPlay() override;
	virtual void		Tick() override;
	virtual void		Render(HDC hdc) override;

	virtual void		TickIdle() override;
	virtual void		TickMove() override;
	virtual void		TickBattle() override;

	virtual void		UpdateAnimation() override;

	void				SetIsMine(bool isMine) { _isMine = isMine; }

	const PokemonStat&	GetStat() { return _stat; }
	const std::wstring& GetName();
	int32				GetLevel() { return _level; }
	int32				GetHp() { return _hp; }
	int32				GetExp() { return _exp; }
	int32				GetMaxExp() { return _maxExp; }

	void				UseSkill(int32 skillIndex);
	void				OnDamaged(Pokemon* attacker, Skill* skill);

	void				AddHp(int32 hp);
	void				AddExp(int32 exp);
	void				LevelUp();

	void				AddSkill(Skill* skill);
	void				RemoveSkill(int32 skillIndex);

private:
	Flipbook*			_flipbookIdle[4] = {};
	Flipbook*			_flipbookMove[4] = {};
	Flipbook*			_flipbookBattle[2] = {};

	bool				_isMine = true;

private:
	PokemonStat			_stat = {};				// 실제 스탯
	int32				_level = 5;
	
	int32				_hp = 10;
	int32				_destHp = 10;

	int32				_exp = 0;
	int32				_destExp = 5000;
	int32				_maxExp = 1000;

	PokemonInfo*		_info = {};
	PokemonStat*		_baseStat = {};			// 종족치

	Pokemon*			_target = nullptr;
	Skill*				_skills[4] = {};
};

