#pragma once

enum
{
	PokemonMaxCount = 251
};

struct PokemonInfo;

struct PokemonStat;

class InfoManager
{
	DECLARE_SINGLE(InfoManager);

	~InfoManager();
public:
	void				Init();
	void				Clear();

	void				LoadPokemonInfo(const std::wstring& path);

	PokemonInfo*		GetPokemonInfo(int32 pokeNum);
	PokemonStat*		GetPokemonStat(int32 pokeNum);

private:
	std::vector<PokemonInfo*>			_infos = {};
	std::vector<PokemonStat*>			_stats = {};

	std::map<std::wstring, PokeType>	_types;
};

