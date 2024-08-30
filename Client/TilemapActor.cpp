#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"

#include <fstream>

bool SaveHDCToBMP(HDC hdc, int width, int height, const char* filePath);

TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{
	
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
	
	std::wstring texture[TileMap_LAYER::MAXCOUNT] = { L"PLAT_Buildings", L"PLAT_Mount", L"PLAT_Nature", L"PLAT_Props" };
	
	for (int32 i = 0; i < TileMap_LAYER::MAXCOUNT; i++)
	{
		_sprites[i] = GET_SINGLE(ResourceManager)->GetSprite(texture[i]);
	}
}

void TilemapActor::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Up))
	{
		_pos.y += _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Down))
	{
		_pos.y -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Left))
	{
		_pos.x -= _speed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Right))
	{
		_pos.x += _speed * deltaTime;
	}
}

void TilemapActor::Render(HDC hdc)
{	
	Super::Render(hdc);

	if (_tilemap == nullptr)
		return;

	if (_showDebug == false)
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	int32 left = max(GWinSizeX / 2, _pos.x) - _pos.x;
	int32 top = max(0, _pos.y) - _pos.y;
	int32 right = min(GWinSizeX, _pos.x + mapSize.x * TILE_SIZEX) - _pos.x;
	int32 bottom = min(GWinSizeY, _pos.y + mapSize.y * TILE_SIZEY) - _pos.y;

	int32 startX = left / TILE_SIZEX;
	int32 startY = top / TILE_SIZEY;
	int32 endX = right / TILE_SIZEX;
	int32 endY = bottom / TILE_SIZEY;

	for (int32 y = startY; y < endY; y++)
	{
		for (int32 x = startX; x < endX; x++)
		{
			::TransparentBlt(hdc,
				_pos.x + x * TILE_SIZEX,
				_pos.y + y * TILE_SIZEY,
				TILE_SIZEX,
				TILE_SIZEY,
				_sprites[tiles[y][x].layer]->GetDC(),
				tiles[y][x].x * TILE_SIZEX,
				tiles[y][x].y * TILE_SIZEY,
				TILE_SIZEX,
				TILE_SIZEY,
				_sprites[tiles[y][x].layer]->GetTransparent());
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::I))
	{
		SaveHDCToBMP(hdc, GWinSizeX, GWinSizeY, "..\\Resources\\Sprite\\Background\\test.bmp");
	}
}

void TilemapActor::SetTileAt(Tile tile)
{
	
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x - _pos.x;
		int32 posY = mousePos.y - _pos.y;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;
		
		_tilemap->SetTileAt(tile, { x, y });
	}

}

bool SaveHDCToBMP(HDC hdc, int width, int height, const char* filePath) {
	// ȣȯ ������ ��Ʈ�� ����
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
	if (!hBitmap) {
		return false;
	}

	// HDC�� ȣȯ�Ǵ� �޸� DC ����
	HDC hMemDC = CreateCompatibleDC(hdc);
	if (!hMemDC) {
		DeleteObject(hBitmap);
		return false;
	}

	// �޸� DC�� ȣȯ ��Ʈ�� ����
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// HDC�� ������ �޸� DC�� ����
	BitBlt(hMemDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

	// BITMAPINFO ����ü ����
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;  // 24��Ʈ �÷�
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// ��Ʈ�� ������ �޸� �Ҵ�
	int bmpDataSize = ((width * 24 + 31) / 32) * 4 * height;  // �� ũ��� 4����Ʈ�� ������� ��
	BYTE* bmpData = new BYTE[bmpDataSize];
	if (!bmpData) {
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		return false;
	}

	// ��Ʈ�� ������ ��������
	GetDIBits(hMemDC, hBitmap, 0, height, bmpData, &bmpInfo, DIB_RGB_COLORS);

	// .bmp ���� ���� (ofstream ���)
	std::ofstream file(filePath, std::ios::out | std::ios::binary);
	if (!file) {
		delete[] bmpData;
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		return false;
	}

	// BITMAPFILEHEADER �ۼ�
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfType = 0x4D42;  // ��Ʋ ��������� 'BM'
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + bmpDataSize;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;

	file.write(reinterpret_cast<char*>(&bmpFileHeader), sizeof(BITMAPFILEHEADER));

	// BITMAPINFOHEADER �ۼ�
	file.write(reinterpret_cast<char*>(&bmpInfo.bmiHeader), sizeof(BITMAPINFOHEADER));

	// ��Ʈ�� ������ �ۼ�
	file.write(reinterpret_cast<char*>(bmpData), bmpDataSize);

	// ���� �۾�
	file.close();
	delete[] bmpData;
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return true;
}
