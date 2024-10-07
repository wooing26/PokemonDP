#include "pch.h"
#include "Skill.h"
#include "InfoManager.h"

Skill::Skill()
{
}

Skill::Skill(int32 No)
{
	_info = GET_SINGLE(InfoManager)->GetPokemonSkill(No);
	_pp = _info->maxPp;
}

Skill::~Skill()
{
}

void Skill::BeginPlay()
{
	Super::BeginPlay();
}

void Skill::TickComponent()
{
}

void Skill::Render(HDC hdc)
{
}


