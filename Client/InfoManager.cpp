#include "pch.h"
#include "InfoManager.h"
#include "Pokemon.h"

#include <iostream>
#include <sstream>
#include <fstream>

InfoManager::~InfoManager()
{
	Clear();
}

void InfoManager::Init()
{
	LoadPokemonInfo(L"..\\Resources\\Info\\PokemonInfo.csv");
}

void InfoManager::Clear()
{
	for (int32 i = 1; i < PokemonMaxCount; i++)
	{
		delete _infos[i];
		_infos[i] = nullptr;
		delete _stats[i];
		_stats[i] = nullptr;
	}

	_infos.clear();
	_stats.clear();
}

void InfoManager::LoadPokemonInfo(const std::wstring& path)
{
	_infos.resize(PokemonMaxCount);
	_stats.resize(PokemonMaxCount);
	// C++ ½ºÅ¸ÀÏ
	{
		std::wifstream ifs;

		ifs.open(path);

		std::wstring info;
		ifs >> info;

		for (int32 no = 1; no <= PokemonMaxCount; no++)
		{
			std::wstring line;
			ifs >> line;
			int32 start = 4;
			int32 end = line.find(L',', start);

			_infos[no] = new PokemonInfo();
			_stats[no] = new PokemonStat();
			
			_infos[no]->No = std::stoi(line.substr(0, 2));
			_infos[no]->name = line.substr(start, end - start);
			
			end = start;
			_infos[no]->generation = line[end] - L'0';
			_infos[no]->line = line[end + 2] - L'0';
			_infos[no]->start = line[end + 4] - L'0';
			_infos[no]->separateGender = line[end + 6] - L'0';
			//_infos[no].type1 = std::stoi(line.substr(start, end - start));
			//_infos[no].type2 = std::stoi(line.substr(start, end - start));


		}
		ifs.close();
	}
}

//for (int32 y = 0; y < _mapSize.y; y++)
//{
//	std::wstring line;
//	ifs >> line;
//
//	for (int32 x = 0; x < _mapSize.x; x++)
//	{
//		std::wstring data = line.substr(x * 6, 6);
//
//		_tiles[y][x].type = static_cast<Tilemap_TYPE>(std::stoi(data.substr(0, 2)));
//		_tiles[y][x].y = std::stoi(data.substr(2, 2));
//		_tiles[y][x].x = std::stoi(data.substr(4, 2));
//	}
//}