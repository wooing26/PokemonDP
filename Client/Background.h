#pragma once
#include "Actor.h"

class Sprite;

class Background : public Actor
{
	using Super = Actor;
public:
	Background();
	virtual ~Background() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			SetMapSprite(Sprite* map);

private:
	Sprite*		_map = nullptr;
	Vec2Int		_mapStartPosInWorld = { 0, 0 };
};

