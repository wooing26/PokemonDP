#pragma once
#include "Actor.h"

class Tilemap;

enum TILE_SIZE
{
	TILE_SIZEX = 32,
	TILE_SIZEY = 32,
};

class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void	BeginPlay();
	virtual void	Tick();
	virtual void	Render(HDC hdc);

	void			SetTileAt(class Tile tile);

	void			SetTilemap(Tilemap* tilemap) { _tilemap = tilemap; }
	Tilemap*		GetTilemap() { return _tilemap; }

	void			SetShowDebug(bool showDebug) { _showDebug = showDebug; }

	void			SetShowAll(bool showAll) { _showAll = showAll; }

protected:
	Tilemap*									_tilemap = nullptr;
	bool										_showDebug = true;
	bool										_showAll = false;
	class Sprite*								_sprites[Tilemap_TYPE::MAXCOUNT] = {};

	float										_speed = 500;
};

