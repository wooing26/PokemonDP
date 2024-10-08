#pragma once
#include "ResourceBase.h"

struct Tile
{
	// TODO
	Tilemap_TYPE	type = Tilemap_TYPE::PLAT_Nature;
	int32			x = 0;
	int32			y = 0;
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

	virtual void					LoadFile(const std::wstring& path) override;
	virtual void					SaveFile(const std::wstring& path) override;
	void							LoadFileOld(const std::wstring& path);
	void							SaveLayer(const std::wstring& path);

	void							SetTileAll(Tile tile);
	
	void							SetTileAt(Tile tile, Vec2Int pos);
	Tile*							GetTileAt(Vec2Int pos);

	std::vector<std::vector<Tile>>&	GetTiles() { return _tiles; };
	
	void							SetMapSize(Vec2Int size);
	Vec2Int							GetMapSize() { return _mapSize; }
	void							ResizeMap(Vec2Int size);

	void							SetTileSize(int32 size);
	int32							GetTileSize() { return _tileSize; }

private:
	Vec2Int							_mapSize = {};
	int32							_tileSize = {};
	std::vector<std::vector<Tile>>	_tiles;
};

