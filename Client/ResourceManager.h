#pragma once

class Texture;
class Sprite;
class Flipbook;
class Tilemap;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);

	~ResourceManager();
public:
	void				Init(HWND hwnd, fs::path resourcePath);
	void				Clear();

	const fs::path&		GetResourcePath() { return _resourcePath; }

	Texture*			GetTexture(const std::wstring& key) { return _textures[key]; }
	Texture*			LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite*				GetSprite(const std::wstring& key) { return _sprites[key]; }
	Sprite*				CreateSprite(const std::wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Flipbook*			GetFlipbook(const std::wstring& key) { return _flipbooks[key]; }
	Flipbook*			CreateFlipbook(const std::wstring& key);

	Tilemap*			GetTilemap(const std::wstring& key) { return _tilemaps[key]; }
	Tilemap*			CreateTilemap(const std::wstring& key);
	void				SaveTilemap(const std::wstring& key, const std::wstring& path);
	void				SaveTilemapLayer(const std::wstring& key, const std::wstring& path);
	Tilemap*			LoadTilemap(const std::wstring& key, const std::wstring& path);
	Tilemap*			LoadTilemapOld(const std::wstring& key, const std::wstring& path);


private:
	HWND											_hwnd;
	fs::path										_resourcePath;

	std::unordered_map<std::wstring, Texture*>		_textures;
	std::unordered_map<std::wstring, Sprite*>		_sprites;
	std::unordered_map<std::wstring, Flipbook*>		_flipbooks;
	std::unordered_map<std::wstring, Tilemap*>		_tilemaps;
};

