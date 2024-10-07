#pragma once

enum
{
	PokemonMaxCount = 251,
	SkillMaxCount = 251
};

struct PokemonInfo;
struct PokemonStat;

struct SkillInfo;

class InfoManager
{
	DECLARE_SINGLE(InfoManager);

	~InfoManager();
public:
	void				Init();
	void				Clear();

	void				LoadPokemonInfo(const std::wstring& path);
	void				LoadPokemonSkill(const std::wstring& path);

	PokemonInfo*		GetPokemonInfo(int32 pokeNum);
	PokemonStat*		GetPokemonStat(int32 pokeNum);
	SkillInfo*			GetPokemonSkill(int32 skillNum);

	void				SetTypeChart();
	float				GetTypeEffectiveness(PokeType attackType, PokeType defenseType);

private:
	std::vector<PokemonInfo*>				_infos = {};
	std::vector<PokemonStat*>				_stats = {};
	std::vector<SkillInfo*>					_skills = {};

	std::map<std::wstring, PokeType>		_types;
	std::map<std::wstring, SkillCategory>	_categories;

	std::vector<std::vector<float>>			_typeChart = {};
};

