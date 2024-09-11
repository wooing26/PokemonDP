#include "pch.h"
#include "TileMapScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "FlipbookActor.h"
#include "SpriteActor.h"
#include "TilemapActor.h"

#include <fstream>

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Buildings", L"Sprite\\Tile\\TileSet\\PLAT Buildings.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Mount", L"Sprite\\Tile\\TileSet\\PLAT Mount.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Nature", L"Sprite\\Tile\\TileSet\\PLAT Nature.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Props", L"Sprite\\Tile\\TileSet\\PLAT Props.png");

	GET_SINGLE(ResourceManager)->LoadTexture(L"Buildings", L"Sprite\\Tile\\TileSet\\buildings (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Caves", L"Sprite\\Tile\\TileSet\\caves (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Mounts", L"Sprite\\Tile\\TileSet\\mounts (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Nature", L"Sprite\\Tile\\TileSet\\nature (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Props", L"Sprite\\Tile\\TileSet\\props (HGSS).png");

	GET_SINGLE(ResourceManager)->LoadTexture(L"LucasDown", L"Sprite\\Player\\LucasDown.bmp");

	GET_SINGLE(ResourceManager)->LoadTexture(L"borders", L"Sprite\\Tile\\TileSet\\borders.png");

	GET_SINGLE(ResourceManager)->CreateSprite(L"borders", GET_SINGLE(ResourceManager)->GetTexture(L"borders"), 0, 0);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Buildings", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Buildings"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Mount", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Mount"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Nature", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Nature"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Props", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Props"), 0, 0);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"Buildings", GET_SINGLE(ResourceManager)->GetTexture(L"Buildings"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Caves", GET_SINGLE(ResourceManager)->GetTexture(L"Caves"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Mounts", GET_SINGLE(ResourceManager)->GetTexture(L"Mounts"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Nature", GET_SINGLE(ResourceManager)->GetTexture(L"Nature"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Props", GET_SINGLE(ResourceManager)->GetTexture(L"Props"), 0, 0);

	{
		TilemapActor* actor = new TilemapActor();
		actor->SetPos({ GWinSizeX / 2, 0 });
		_tilemapActor = actor;
		AddActor(actor);

		Tilemap* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
		tm->SetMapSize({ 40, 40 });
		tm->SetTileSize(32);

		actor->SetTilemap(tm);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Nature");
		Vec2Int size = sprite->GetSize();

		SetMapSize(Vec2(size.x, size.y));
		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2});
		AddActor(background);
		_spriteActor = background;
	}

	Super::Init();
}

void TileMapScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Move Camera Pos
	if(GET_SINGLE(InputManager)->GetButtonPress(KeyType::W))
	{
		_cameraPos.y -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::S))
	{
		_cameraPos.y += _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		_cameraPos.x -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		_cameraPos.x += _speed * deltaTime;
	}

	// Edit Tilemap
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	if (IsMouseInSelect(mousePos))
	{
		if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::LeftMouse))
		{
			Vec2 selectedPos = { (mousePos.x + (_cameraPos.x - GWinSizeX / 2)), (mousePos.y + (_cameraPos.y - GWinSizeY / 2)) };
			
			if (0 <= selectedPos.x && selectedPos.x <= _mapSize.x
				&& 0 <= selectedPos.y && selectedPos.y <= _mapSize.y)
			{
				_selectedTilePos.x = selectedPos.x / _tileSize;
				_selectedTilePos.y = selectedPos.y / _tileSize;
			}
		}
	}
	else if (IsMouseInEdit(mousePos))
	{
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LeftMouse))
		{
			_tilemapActor->SetTileAt({ _tilemapLayer,_selectedTilePos.x, _selectedTilePos.y });
		}
	}
	
	// Save or Load Tilemap
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Sprite\\Tile\\Tilemap01.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Sprite\\Tile\\Tilemap01.txt");
	}

	// Change Sprite
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_1))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Buildings"));
		_tilemapLayer = TileMap_LAYER::PLAT_Buildings;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_2))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Mount"));
		_tilemapLayer = TileMap_LAYER::PLAT_Mount;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_3))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Nature"));
		_tilemapLayer = TileMap_LAYER::PLAT_Nature;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_4))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Props"));
		_tilemapLayer = TileMap_LAYER::PLAT_Props;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_5))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Buildings"));
		_tilemapLayer = TileMap_LAYER::Buildings;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_6))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Caves"));
		_tilemapLayer = TileMap_LAYER::Caves;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_7))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Mounts"));
		_tilemapLayer = TileMap_LAYER::Mounts;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_8))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Nature"));
		_tilemapLayer = TileMap_LAYER::Nature;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_9))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Props"));
		_tilemapLayer = TileMap_LAYER::Props;
	}

	GET_SINGLE(SceneManager)->SetCameraPos(_cameraPos);
}

void TileMapScene::Render(HDC hdc)
{
	Super::Render(hdc);

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::I))
	{
		Vec2 pos = _tilemapActor->GetPos();
		_tilemapActor->SetPos({0, 0});

		_tilemapActor->SetShowAll(true);

		_tilemapActor->Render(hdc);
		Tilemap* tm = _tilemapActor->GetTilemap();

		SaveHDCToBMP(hdc, tm->GetMapSize().x * _tileSize, tm->GetMapSize().y * _tileSize, "..\\Resources\\Sprite\\Background\\test.bmp");

		_tilemapActor->SetShowAll(false);
		_tilemapActor->SetPos(pos);
	}

	int32 MaxX = min(_mapSize.x - (_cameraPos.x - GWinSizeX / 2) + 1, GWinSizeX / 2);
	int32 MaxY = min(_mapSize.y - (_cameraPos.y - GWinSizeY / 2) + 1, GWinSizeY);

	Vec2Int from = Vec2Int{ - ((int32)_cameraPos.x - GWinSizeX / 2), - ((int32)_cameraPos.y - GWinSizeY / 2) };
	Vec2Int to = from;
	to.y += _mapSize.y;

	while (from.x <= MaxX)
	{	
		if (from.x >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
		
		from.x += _tileSize;
		to.x += _tileSize;
	}

	from = Vec2Int{ - ((int32)_cameraPos.x - GWinSizeX / 2), - ((int32)_cameraPos.y - GWinSizeY / 2) };
	to = from;
	to.x += _mapSize.x;
	if (to.x > GWinSizeX / 2)
		to.x = GWinSizeX / 2;
	while (from.y <= MaxY)
	{
		if (from.y >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));
		
		from.y += _tileSize;
		to.y += _tileSize;
	}
}

void TileMapScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);
}

void TileMapScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);
}

bool TileMapScene::IsMouseInSelect(POINT mousePos)
{
	RECT rect =
	{
		0,
		0,
		GWinSizeX / 2,
		GWinSizeY 
	};

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}

bool TileMapScene::IsMouseInEdit(POINT mousePos)
{
	RECT rect =
	{ 
		GWinSizeX / 2,
		0,
		GWinSizeX,
		GWinSizeY 
	};

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}

void TileMapScene::ChangeSelectedSprite(Sprite* sprite)
{
	Vec2Int size = sprite->GetSize();

	SetMapSize(Vec2(size.x, size.y));
	_spriteActor->SetSprite(sprite);
	_spriteActor->SetPos(Vec2{ (float)size.x / 2, (float)size.y / 2 });

	_selectedTilePos = { 0, 0 };

	_cameraPos = { GWinSizeX / 2, GWinSizeY / 2 };
}

bool TileMapScene::SaveHDCToBMP(HDC hdc, int width, int height, const char* filePath)
{
	// 호환 가능한 비트맵 생성
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
	if (!hBitmap) {
		return false;
	}

	// HDC와 호환되는 메모리 DC 생성
	HDC hMemDC = CreateCompatibleDC(hdc);
	if (!hMemDC) {
		DeleteObject(hBitmap);
		return false;
	}

	// 메모리 DC에 호환 비트맵 선택
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// HDC의 내용을 메모리 DC에 복사
	BitBlt(hMemDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

	// BITMAPINFO 구조체 생성
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;							// 24비트 컬러
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// 비트맵 데이터 메모리 할당
	int bmpDataSize = ((width * 24 + 31) / 32) * 4 * height;	// 행 크기는 4바이트의 배수여야 함
	BYTE* bmpData = new BYTE[bmpDataSize];
	if (!bmpData) {
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		return false;
	}

	// 비트맵 데이터 가져오기
	GetDIBits(hMemDC, hBitmap, 0, height, bmpData, &bmpInfo, DIB_RGB_COLORS);

	// .bmp 파일 생성 (ofstream 사용)
	std::ofstream file(filePath, std::ios::out | std::ios::binary);
	if (!file) {
		delete[] bmpData;
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		return false;
	}

	// BITMAPFILEHEADER 작성
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfType = 0x4D42;  // 리틀 엔디언으로 'BM'
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + bmpDataSize;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;

	file.write(reinterpret_cast<char*>(&bmpFileHeader), sizeof(BITMAPFILEHEADER));

	// BITMAPINFOHEADER 작성
	file.write(reinterpret_cast<char*>(&bmpInfo.bmiHeader), sizeof(BITMAPINFOHEADER));

	// 비트맵 데이터 작성
	file.write(reinterpret_cast<char*>(bmpData), bmpDataSize);

	// 정리 작업
	file.close();
	delete[] bmpData;
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return true;
}