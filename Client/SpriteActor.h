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

	void			SetRenderRatio(float renderRatio) { _renderRatio = renderRatio; }
	const float&	GetRenderRatio() { return _renderRatio; }

private:
	Sprite*			_sprite = nullptr;
	float			_renderRatio = 1.f;
};

