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

	void			SetSprite(Sprite* sprite) { _sprite = sprite; }

	void			SetRenderSize(Vec2Int renderSize) { _renderSize = renderSize; }
	const Vec2Int&	GetRenderSize() { return _renderSize; }

private:
	Sprite*			_sprite = nullptr;
	Vec2Int			_renderSize = {};
};

