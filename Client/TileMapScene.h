#pragma once
#include "Scene.h"

class TileMapScene : public Scene
{
	using Super = Scene;
public:
	TileMapScene();
	virtual ~TileMapScene();

	virtual void	Init() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	virtual void	AddActor(Actor* actor) override;
	virtual void	RemoveActor(Actor* actor) override;

private:
	Vec2		_pos = {0, 0};
	Vec2		_playerPos = {GWinSizeX / 2, GWinSizeY / 2};
	int32		_speed = 100;
	int32		_tileSize = 32;
};

