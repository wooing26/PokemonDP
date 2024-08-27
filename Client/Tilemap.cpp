#include "pch.h"
#include "Tilemap.h"
#include <iostream>
#include <fstream>

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::LoadFile(const std::wstring& path)
{
	// C++ 스타일
	{
		std::wifstream ifs;

		ifs.open(path);

		ifs >> _mapSize.x >> _mapSize.y;

		SetMapSize(_mapSize);

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			std::wstring line;
			ifs >> line;

			for (int32 x = 0; x < _mapSize.x; x++)
			{
				_tiles[y][x].value = line[x] - L'0';
			}
		}

		ifs.close();
	}
	
}

void Tilemap::SaveFile(const std::wstring& path)
{
	
	// C++ 스타일
	{
		std::wofstream ofs;

		ofs.open(path);

		ofs << _mapSize.x << std::endl;
		ofs << _mapSize.y << std::endl;

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				ofs << _tiles[y][x].value;
			}

			ofs << std::endl;
		}

		ofs.close();
	}
}

Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = std::vector<std::vector<Tile>>(size.y, std::vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{0};
		}
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}
