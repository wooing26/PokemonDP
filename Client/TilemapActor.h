#pragma once
#include "Actor.h"

class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void	BeginPlay();
	virtual void	Tick();
	virtual void	Render(HDC hdc);

	void			SetMapSize(Vec2 mapSize) { _mapSize = mapSize; }
	Vec2			GetMapSize() { return _mapSize; }

private:
	Vec2			_mapSize = {};
	int32			_tileSize = 32;
};

