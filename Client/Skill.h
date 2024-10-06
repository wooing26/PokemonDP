#pragma once
#include "GameObject.h"

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

class Skill : public GameObject
{
	using Super = GameObject;
public:
	Skill();
	virtual ~Skill() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	virtual void	TickBattle() override;

	virtual void	UpdateAnimation() override;

private:
	SkillInfo*			_info = nullptr;
	int32				_pp = 0;
};

