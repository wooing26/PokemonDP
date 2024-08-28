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

	void			SetMapSize(Vec2 mapSize) { _mapSize = mapSize; }

	bool			IsMouseInSelect(POINT mousePos);
	bool			IsMouseInEdit(POINT mousePos);

private:
	Vec2					_pos = { 0, 0 };
	Vec2					_cameraPos = { GWinSizeX / 2, GWinSizeY / 2 };
	Vec2					_mapSize = { 320, 320 };
	int32					_speed = 500;
	int32					_tileSize = 32;

	class TilemapActor*		_tilemapActor = nullptr;
	Vec2Int					_selectedTilePos = {0, 0};
};

