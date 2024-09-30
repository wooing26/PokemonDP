#pragma once
#include "Creature.h"

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

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	virtual void	TickIdle() override;
	virtual void	TickMove() override;
	virtual void	TickBattle() override;

	virtual void	UpdateAnimation() override;

	void			SetIsMine(bool isMine) { _isMine = isMine; }

private:
	Flipbook*			_flipbookIdle[4] = {};
	Flipbook*			_flipbookMove[4] = {};
	Flipbook*			_flipbookBattle[2] = {};

	bool				_isMine = true;

private:
	PokemonStat			_stat = {};
	int32				_level = 1;
	int32				_maxHp = 10;
	int32				_exp = 0;
	int32				_maxExp = 10;

	PokemonInfo*		_info = {};
	PokemonStat*		_baseStat = {};
};

