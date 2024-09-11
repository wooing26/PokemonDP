#pragma once
#include "Actor.h"

class Sprite;

class SpriteActor : public Actor
{
	using Super = Actor;
public:
	SpriteActor();
	virtual ~SpriteActor();

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			SetSprite(Sprite* sprite);

	void			SetRenderRatio(float renderRatio) { _size = _size * renderRatio; }

private:
	Sprite*			_sprite = nullptr;

};

