#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void ResourceManager::Clear()
{
	for (auto& item : _textures)
		SAFE_DELETE(item.second);

	_textures.clear();

	for (auto& item : _sprites)
		SAFE_DELETE(item.second);

	_sprites.clear();

	for (auto& item : _flipbooks)
		SAFE_DELETE(item.second);

	_flipbooks.clear();

	for (auto& item : _tilemaps)
		SAFE_DELETE(item.second);

	_tilemaps.clear();
}

Texture* ResourceManager::LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	fs::path fullpath = _resourcePath / path;
	Texture* texture = new Texture();

	std::wstring ext = path.substr(path.find_last_of(L".") + 1);
	
	if (ext == L"png")
		texture->LoadPng(_hwnd, fullpath.c_str());
	else if (ext == L"bmp")
		texture->LoadBmp(_hwnd, fullpath.c_str());

	texture->SetTransparent(transparent);
	_textures[key] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const std::wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;

	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const std::wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;

	return fb;
}

Tilemap* ResourceManager::CreateTilemap(const std::wstring& key)
{
	if (_tilemaps.find(key) != _tilemaps.end())
		return _tilemaps[key];

	Tilemap* tm = new Tilemap();
	_tilemaps[key] = tm;

	return tm;
}

void ResourceManager::SaveTilemap(const std::wstring& key, const std::wstring& path)
{
	Tilemap* tm = GetTilemap(key);

	fs::path fullPath = _resourcePath / path;
	tm->SaveFile(fullPath);
}

void ResourceManager::SaveTilemapLayer(const std::wstring& key, const std::wstring& path)
{
	Tilemap* tm = GetTilemap(key);

	fs::path fullPath = _resourcePath / path;
	tm->SaveLayer(fullPath);
}

Tilemap* ResourceManager::LoadTilemap(const std::wstring& key, const std::wstring& path)
{
	Tilemap* tm = nullptr;

	if (_tilemaps.find(key) == _tilemaps.end())
		_tilemaps[key] = new Tilemap();

	tm = _tilemaps[key];

	fs::path fullPath = _resourcePath / path;
	tm->LoadFile(fullPath);

	return tm;
}

Tilemap* ResourceManager::LoadTilemapOld(const std::wstring& key, const std::wstring& path)
{
	Tilemap* tm = nullptr;

	if (_tilemaps.find(key) == _tilemaps.end())
		_tilemaps[key] = new Tilemap();

	tm = _tilemaps[key];

	fs::path fullPath = _resourcePath / path;
	tm->LoadFileOld(fullPath);

	return tm;
}
