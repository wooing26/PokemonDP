#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void	BeginPlay();
	virtual void	Tick();
	virtual void	Render(HDC hdc);

	void			SetFlipbook(Flipbook* flipbook);
	void			Reset();

private:
	Flipbook*	_flipbook = nullptr;
	float		_sumTime = 0.f;
	int32		_idx = 0;
};

