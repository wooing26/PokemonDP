#pragma once
#include "FlipbookActor.h"

class GameObject : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	GameObject();
	virtual ~GameObject();

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	virtual void	TickIdle() {}
	virtual void	TickMove() {}
	virtual void	TickSkill() {}

	virtual void	UpdateAnimation() {}

	void			SetState(ObjectState state);
	ObjectState		GetState() { return _state; }
	void			SetDir(Dir dir);

	void			SetCellPos(Vec2Int cellPos, bool teleport = false);
	Vec2Int			GetCellPos() { return _cellPos; }


private:
	Vec2Int			_cellPos = {};
	Vec2			_speed = {};
	Dir				_dir = DIR_Down;
	ObjectState		_state = ObjectState::Idle;
	

};

