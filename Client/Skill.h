#pragma once
#include "Component.h"

struct SkillInfo
{
	int32				No = 0;
	std::wstring		name = L"";
	PokeType			type = PokeType::None;
	SkillCategory		category = SkillCategory::Physical;
	int32				power = 0;
	int32				accuracy = 0;
	int32				maxPp = 0;
	int32				generation = 1;
	std::wstring		condition = L"";
};

class Skill : public Component
{
	using Super = Component;
public:
	Skill();
	Skill(int32 No);
	virtual ~Skill() override;

	virtual void		BeginPlay() override;
	virtual void		TickComponent() override;
	virtual void		Render(HDC hdc) override;

	const SkillInfo*	GetSkillInfo() { return _info; }
	PokeType			GetSkillType() { return _info->type; }
	SkillCategory		GetSkillCategory() { return _info->category; }

private:
	SkillInfo*			_info = nullptr;
	int32				_pp = 0;
};

