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
	void	Init();
	void	Clear();

	void	LoadPokemonInfo(const std::wstring& path);

private:
	std::vector<PokemonInfo*>	_infos = {};
	std::vector<PokemonStat*>	_stats = {};
};

