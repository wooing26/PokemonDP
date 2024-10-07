#include "pch.h"
#include "InfoManager.h"
#include "Pokemon.h"
#include "Skill.h"

#include <iostream>
#include <fstream>

InfoManager::~InfoManager()
{
	Clear();
}

void InfoManager::Init()
{
	// 한글 이름으로 포켓몬 타입 변환
	const int32 size = static_cast<int32>(PokeType::End);
	std::wstring typeName[size] =
	{
		L"",
		L"노말",
		L"불꽃",
		L"물",
		L"풀",
		L"전기",
		L"얼음",
		L"격투",
		L"독",
		L"땅",
		L"비행",
		L"에스퍼",
		L"벌레",
		L"바위",
		L"고스트",
		L"드래곤",
		L"악",
		L"강철",
		L"페어리",
	};

	// 한글 이름으로 기술 카테고리 변환
	const int32 size2 = static_cast<int32>(SkillCategory::End);
	std::wstring categoryName[size2] =
	{
		L"물리",
		L"특수",
		L"변화"
	};

	// map으로 포켓몬 타입을 변환하기 위한 세팅
	for (int32 i = 0; i < size; i++)
	{
		_types[typeName[i]] = static_cast<PokeType>(i);
	}

	// map으로 기술 카테고리를 변환하기 위한 세팅
	for (int32 i = 0; i < size2; i++)
	{
		_categories[categoryName[i]] = static_cast<SkillCategory>(i);
	}

	LoadPokemonInfo(L"..\\Resources\\Info\\PokemonInfo.csv");
	LoadPokemonSkill(L"..\\Resources\\Info\\PokemonSkill.csv");

	SetTypeChart();
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
	// C++ 스타일
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
			
			// 도감 번호, 한글 이름
			_infos[no]->No = std::stoi(line.substr(0, 3));
			_infos[no]->name = line.substr(start, end - start);
			
			// 리소스 위치
			start = end + 1;
			_infos[no]->generation = line[start] - L'0';
			_infos[no]->line = std::stoi(line.substr(start + 2, 2));
			_infos[no]->start = line[start + 5] - L'0';
			_infos[no]->separateGender = line[start + 7] - L'0';

			// 타입 1
			start = start + 9;
			end = line.find(L',', start);
			_infos[no]->type1 = _types[line.substr(start, end - start)];

			// 타입 2
			start = end + 1;
			end = line.find(L',', start);
			_infos[no]->type2 = _types[line.substr(start, end - start)];

			// 스탯
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

void InfoManager::LoadPokemonSkill(const std::wstring& path)
{
	_skills.resize(SkillMaxCount + 1);
	// C++ 스타일
	{
		std::locale::global(std::locale("korean"));

		std::wifstream ifs;

		ifs.open(path);

		for (int32 no = 1; no <= SkillMaxCount; no++)
		{
			std::wstring line;
			ifs >> line;
			int32 start = 4;
			int32 end = line.find(L',', start);

			_skills[no] = new SkillInfo();

			// 기술 번호, 한글 이름
			_skills[no]->No = std::stoi(line.substr(0, 3));
			_skills[no]->name = line.substr(start, end - start);

			// 타입
			start = end + 1;
			end = line.find(L',', start);
			_skills[no]->type = _types[line.substr(start, end - start)];

			// 분류
			start = end + 1;
			end = line.find(L',', start);
			_skills[no]->category = _categories[line.substr(start, end - start)];

			// 위력
			start = end + 1;
			end = line.find(L',', start);
			_skills[no]->power = std::stoi(line.substr(start, end - start));

			// 명중률
			start = end + 1;
			end = line.find(L',', start);
			_skills[no]->accuracy = std::stoi(line.substr(start, end - start));

			// pp
			start = end + 1;
			end = line.find(L',', start);
			_skills[no]->maxPp = std::stoi(line.substr(start, end - start));

			// 세대
			start = end + 1;
			_skills[no]->generation = line[start] - L'0';

			// 컨디션 (포켓몬 콘테스트)
			_skills[no]->condition = line.substr(start + 2);

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

SkillInfo* InfoManager::GetPokemonSkill(int32 skillNum)
{
	return nullptr;
}

void InfoManager::SetTypeChart()
{
	_typeChart =
	{
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f},
		{1.0f, 1.0f, 0.5f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f},
		{1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f},
		{1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.5f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f},
		{1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 2.0f, 2.0f, 0.5f},
		{1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 2.0f},
		{1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f},
		{1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 0.5f, 0.5f},
		{1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f},
		{1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f},
		{1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f},
		{1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 0.5f, 1.0f},
	};
}

float InfoManager::GetTypeEffectiveness(PokeType attackType, PokeType defenseType)
{
	if (attackType == PokeType::End || defenseType == PokeType::End)
		return 0.0f;

	return _typeChart[static_cast<int32>(attackType)][static_cast<int32>(defenseType)];
}
