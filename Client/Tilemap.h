#pragma once
#include "ResourceBase.h"

struct Tile
{
	// TODO
	int32 value = 0;
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

	virtual void					LoadFile(const std::wstring& path) override;
	virtual void					SaveFile(const std::wstring& path) override;

	Vec2Int							GetMapSize() { return _mapSize; }
	int32							GetTileSize() { return _tileSize; }
	Tile*							GetTileAt(Vec2Int pos);
	std::vector<std::vector<Tile>>&	GetTiles() { return _tiles; };
	
	void							SetMapSize(Vec2Int size);
	void							SetTileSize(int32 size);

private:
	Vec2Int							_mapSize = {};
	int32							_tileSize = {};
	std::vector<std::vector<Tile>>	_tiles;
};
