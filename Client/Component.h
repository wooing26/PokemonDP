#pragma once

class Actor;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void BeginPlay() {}
	virtual void TickComponent() {}
	virtual void Render(HDC hdc) { }

	void					SetOwner(std::shared_ptr<Actor> owner) { _owner = owner; }
	std::shared_ptr<Actor>	GetOwner() { return _owner; }

protected:
	std::shared_ptr<Actor>	_owner = nullptr;
};

