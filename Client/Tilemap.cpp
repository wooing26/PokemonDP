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
				std::wstring data = line.substr(x * 8, 8);
				
				_tiles[y][x].type = static_cast<Tilemap_TYPE>(std::stoi(data.substr(0, 2)));
				if (data.find(L'-') != std::wstring::npos)
				{
					_tiles[y][x].y = -1;
					_tiles[y][x].x = -1;
				}
				else
				{
					_tiles[y][x].y = std::stoi(data.substr(2, 3));
					_tiles[y][x].x = std::stoi(data.substr(5, 3));
				}
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
				ofs.width(2);
				ofs.fill('0');
				ofs << _tiles[y][x].type;
				ofs.width(3);
				ofs.fill('0');
				ofs << _tiles[y][x].y;
				ofs.width(3);
				ofs.fill('0');
				ofs << _tiles[y][x].x;
			}

			ofs << std::endl;
		}

		ofs.close();
	}
}

void Tilemap::LoadFileOld(const std::wstring& path)
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
				std::wstring data = line.substr(x * 6, 6);

				_tiles[y][x].type = static_cast<Tilemap_TYPE>(std::stoi(data.substr(0, 2)));
				_tiles[y][x].y = std::stoi(data.substr(2, 2));
				_tiles[y][x].x = std::stoi(data.substr(4, 2));
			}
		}

		ifs.close();
	}
}

void Tilemap::SaveLayer(const std::wstring& path)
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
				if (_tiles[y][x].x == -1 || _tiles[y][x].y == -1)
					ofs << 0;
				else
					ofs << 1;
			}
			ofs << std::endl;
		}

		ofs.close();
	}
}

void Tilemap::SetTileAll(Tile tile)
{
	for (int32 y = 0; y < _mapSize.y; y++)
	{
		for (int32 x = 0; x < _mapSize.x; x++)
		{
			_tiles[y][x] = tile;
		}
	}
}

void Tilemap::SetTileAt(Tile tile, Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return;

	_tiles[pos.y][pos.x] = tile;
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
			_tiles[y][x] = Tile();
		}
	}
}

void Tilemap::ResizeMap(Vec2Int size)
{
	std::vector<std::vector<Tile>> tiles = std::vector<std::vector<Tile>>(size.y, std::vector<Tile>(size.x));
	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			if (x >= _mapSize.x || y >= _mapSize.y)
				tiles[y][x] = Tile(Tilemap_TYPE::PLAT_Nature, -1, -1);
			else
				tiles[y][x] = _tiles[y][x];
		}
	}

	_tiles.resize(size.y, std::vector<Tile>(size.x));
	_tiles = tiles;
	_mapSize = size;
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}
