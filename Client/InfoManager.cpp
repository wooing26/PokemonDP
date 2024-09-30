#include "pch.h"
#include "InfoManager.h"
#include "Pokemon.h"

#include <iostream>
#include <fstream>

InfoManager::~InfoManager()
{
	Clear();
}

void InfoManager::Init()
{
	const int32 size = static_cast<int32>(PokeType::End);
	std::wstring typeName[size] =
	{
		L"",
		L"�븻",
		L"�Ҳ�",
		L"��",
		L"Ǯ",
		L"����",
		L"����",
		L"����",
		L"��",
		L"��",
		L"����",
		L"������",
		L"����",
		L"����",
		L"��Ʈ",
		L"�巡��",
		L"��",
		L"��ö",
		L"��",
	};

	for (int32 i = 0; i < size; i++)
	{
		_types[typeName[i]] = static_cast<PokeType>(i);
	}

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
	_infos.resize(PokemonMaxCount + 1);
	_stats.resize(PokemonMaxCount + 1);
	// C++ ��Ÿ��
	{
		std::locale::global(std::locale("korean"));
		
		std::wifstream ifs;

		ifs.open(path);

		std::wstring info;
		ifs >> info;
		ifs >> info;

		for (int32 no = 1; no <= PokemonMaxCount; no++)
		{
			std::wstring line;
			ifs >> line;
			int32 start = 4;
			int32 end = line.find(L',', start);

			_infos[no] = new PokemonInfo();
			_stats[no] = new PokemonStat();
			
			// ���� ��ȣ, �ѱ� �̸�
			_infos[no]->No = std::stoi(line.substr(0, 3));
			_infos[no]->name = line.substr(start, end - start);
			
			// ���ҽ� ��ġ
			start = end + 1;
			_infos[no]->generation = line[start] - L'0';
			_infos[no]->line = std::stoi(line.substr(start + 2, 2));
			_infos[no]->start = line[start + 5] - L'0';
			_infos[no]->separateGender = line[start + 7] - L'0';

			// Ÿ�� 1
			start = start + 9;
			end = line.find(L',', start);
			_infos[no]->type1 = _types[line.substr(start, end - start)];

			// Ÿ�� 2
			start = end + 1;
			end = line.find(L',', start);
			_infos[no]->type2 = _types[line.substr(start, end - start)];

			// ����
			start = end + 1;
			_stats[no]->hp = std::stoi(line.substr(start, 3));
			_stats[no]->attack = std::stoi(line.substr(start + 4, 3));
			_stats[no]->defense = std::stoi(line.substr(start + 8, 3));
			_stats[no]->specialAttack = std::stoi(line.substr(start + 12, 3));
			_stats[no]->specialDefense = std::stoi(line.substr(start + 16, 3));
			_stats[no]->speed = std::stoi(line.substr(start + 20, 3));
			_stats[no]->total = std::stoi(line.substr(start + 24, 3));
		}
		ifs.close();
	}
}

PokemonInfo* InfoManager::GetPokemonInfo(int32 pokeNum)
{
	if (pokeNum > PokemonMaxCount)
		return nullptr;

	return _infos[pokeNum];
}

PokemonStat* InfoManager::GetPokemonStat(int32 pokeNum)
{
	if (pokeNum > PokemonMaxCount)
		return nullptr;

	return _stats[pokeNum];
}
