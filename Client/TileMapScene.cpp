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
#include "LayerPanel.h"

#include <fstream>

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::Init()
{
	//GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Buildings", L"Sprite\\Background\\Sinnoh_Route_201_Pt.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Buildings", L"Sprite\\Tile\\TileSet\\PLAT Buildings.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Mount", L"Sprite\\Tile\\TileSet\\PLAT Mount.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Nature", L"Sprite\\Tile\\TileSet\\PLAT Nature.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PLAT_Props", L"Sprite\\Tile\\TileSet\\PLAT Props.png");

	GET_SINGLE(ResourceManager)->LoadTexture(L"Buildings", L"Sprite\\Tile\\TileSet\\buildings (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Caves", L"Sprite\\Tile\\TileSet\\caves (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Mounts", L"Sprite\\Tile\\TileSet\\mounts (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Nature", L"Sprite\\Tile\\TileSet\\nature (HGSS).png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Props", L"Sprite\\Tile\\TileSet\\props (HGSS).png");

	// Tree
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tree", L"Sprite\\Tile\\TileSet\\Tree.bmp");
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Layer_tag", L"Sprite\\Tile\\TileSet\\terrain_tag.png");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Layer_button", L"Sprite\\Tile\\LayerButton.bmp");
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Buildings", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Buildings"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Mount", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Mount"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Nature", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Nature"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"PLAT_Props", GET_SINGLE(ResourceManager)->GetTexture(L"PLAT_Props"), 0, 0);
	
	GET_SINGLE(ResourceManager)->CreateSprite(L"Buildings", GET_SINGLE(ResourceManager)->GetTexture(L"Buildings"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Caves", GET_SINGLE(ResourceManager)->GetTexture(L"Caves"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Mounts", GET_SINGLE(ResourceManager)->GetTexture(L"Mounts"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Nature", GET_SINGLE(ResourceManager)->GetTexture(L"Nature"), 0, 0);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Props", GET_SINGLE(ResourceManager)->GetTexture(L"Props"), 0, 0);

	GET_SINGLE(ResourceManager)->CreateSprite(L"Tree", GET_SINGLE(ResourceManager)->GetTexture(L"Tree"), 0, 0);

	for (int32 i = 0; i < 4; i++)
	{
		std::wstring spriteName = std::format(L"LayerTag_{0}", i);
		GET_SINGLE(ResourceManager)->CreateSprite(spriteName, GET_SINGLE(ResourceManager)->GetTexture(L"Layer_tag"), i * 32, 0, 32, 32);
	}

	for (int32 i = 0; i < 4; i++)
	{
		std::wstring spriteName = std::format(L"Layer_{0}", i + 1);
		GET_SINGLE(ResourceManager)->CreateSprite(spriteName + L"On", GET_SINGLE(ResourceManager)->GetTexture(L"Layer_button"), i * 92, 0, 92, 28);
		GET_SINGLE(ResourceManager)->CreateSprite(spriteName + L"Off", GET_SINGLE(ResourceManager)->GetTexture(L"Layer_button"), i * 92, 28, 92, 28);
	}
	
	for (int32 i = 0; i < 4; i++)
	{
		TilemapActor* actor = new TilemapActor();
		actor->SetPos({ GWinSizeX / 2, 0 });
		_tilemapActor[i] = actor;
		AddActor(actor);

		Tilemap* tm = GET_SINGLE(ResourceManager)->CreateTilemap(std::format(L"Tilemap_0{}", i + 1));
		tm->SetMapSize({ 80, 40 });
		tm->SetTileSize(32);
		if (i > 0)
			tm->SetTileAll({ _tilemapType, -1, -1 });

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

	{
		std::shared_ptr<LayerPanel> ui = std::make_shared<LayerPanel>();

		ui->SetPos({ GWinSizeX / 2, 0 });
		_layerPanel = ui;

		AddUI(ui);
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
	EditTilemap();
	
	
	// Save or Load Tilemap
	SaveLoadTilemap();

	// Change Sprite
	ChangeSprite();

	GET_SINGLE(SceneManager)->SetCameraPos(_cameraPos);
}

void TileMapScene::Render(HDC hdc)
{
	Super::Render(hdc);

	// Tilemap 선택 Layer 이미지 추출
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::I))
	{
		Tilemap* tm = _tilemapActor[_selectedLayer]->GetTilemap();
		std::string path = std::format("..\\Resources\\Sprite\\Tilemap\\Image\\TilemapLayer0{}.bmp", _selectedLayer + 1);
		SaveHDCToBMP(hdc, tm->GetMapSize().x * _tileSize, tm->GetMapSize().y * _tileSize, path.c_str());
	}

	// Sprite 이미지 격자무늬 그리기
	DrawTileLine(hdc);

	// Tilemap 마우스 위치 사각형 그리기
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	if (IsMouseInEdit(mousePos))
	{
		Vec2 pos = _tilemapActor[0]->GetPos();
		Vec2Int tilePos = { (int32)(mousePos.x - pos.x) / _tileSize, (int32)(mousePos.y - pos.y) / _tileSize };
		
		tilePos *= _tileSize;
		tilePos.x = tilePos.x + pos.x;
		tilePos.y = tilePos.y + pos.y;
		if (_tilemapType == Tilemap_TYPE::Tree)
		{
			tilePos.x += _tileSize;
			tilePos.y += _tileSize;
			Utils::DrawRect(hdc, tilePos, _tileSize * 2, _tileSize * 2);
		}
		else
		{
			tilePos.x += _tileSize / 2;
			tilePos.y += _tileSize / 2;
			Utils::DrawRect(hdc, tilePos, _tileSize, _tileSize);
		}
		
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

void TileMapScene::DrawTileLine(HDC hdc)
{
	int32 MaxX = min(_mapSize.x - (_cameraPos.x - GWinSizeX / 2) + 1, GWinSizeX / 2);
	int32 MaxY = min(_mapSize.y - (_cameraPos.y - GWinSizeY / 2) + 1, GWinSizeY);

	Vec2Int from = Vec2Int{ -((int32)_cameraPos.x - GWinSizeX / 2), -((int32)_cameraPos.y - GWinSizeY / 2) };
	Vec2Int to = from;
	to.y += _mapSize.y;

	while (from.x <= MaxX)
	{
		if (from.x >= 0)
			Utils::DrawLineColored(hdc, from, to, RGB(255, 255, 255));

		from.x += _tileSize;
		to.x += _tileSize;
	}

	from = Vec2Int{ -((int32)_cameraPos.x - GWinSizeX / 2), -((int32)_cameraPos.y - GWinSizeY / 2) };
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

bool TileMapScene::IsMouseInLayerButton(POINT mousePos)
{
	RECT rect = _layerPanel->GetRect();

	return ::PtInRect(&rect, mousePos);
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

void TileMapScene::EditTilemap()
{
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
			else
			{
				_selectedTilePos.x = -1;
				_selectedTilePos.y = -1;
			}
		}
	}
	else if (IsMouseInLayerButton(mousePos))
	{
		if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::LeftMouse))
		{
			_selectedLayer = _layerPanel->GetSelectedLayer();
		}
	}
	else if (IsMouseInEdit(mousePos))
	{
		if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LeftMouse))
		{
			if (_tilemapType == Tilemap_TYPE::Tree)
			{
				_tilemapActor[_selectedLayer]->SetTileGroup({ _tilemapType,_selectedTilePos.x, _selectedTilePos.y }, {2, 2});
			}
			else
			{
				_tilemapActor[_selectedLayer]->SetTileAt({ _tilemapType,_selectedTilePos.x, _selectedTilePos.y });
			}
		}
	}
}

void TileMapScene::SaveLoadTilemap()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Sprite\\Tilemap\\Text\\Tilemap01.txt");
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_02", L"Sprite\\Tilemap\\Text\\Tilemap02.txt");
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_03", L"Sprite\\Tilemap\\Text\\Tilemap03.txt");
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_04", L"Sprite\\Tilemap\\Text\\Tilemap04.txt");
		GET_SINGLE(ResourceManager)->SaveTilemapLayer(L"Tilemap_03", L"Sprite\\Tilemap\\Text\\TilemapLayer.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Sprite\\Tilemap\\Text\\Tilemap01.txt");
		Tilemap* tm = _tilemapActor[0]->GetTilemap();
		Vec2Int mapSize = tm->GetMapSize();

		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_02", L"Sprite\\Tilemap\\Text\\Tilemap02.txt");
		Tilemap* tm2 = _tilemapActor[1]->GetTilemap();
		tm2->ResizeMap(mapSize);
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_03", L"Sprite\\Tilemap\\Text\\Tilemap03.txt");
		Tilemap* tm3 = _tilemapActor[2]->GetTilemap();
		tm3->ResizeMap(mapSize);
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_04", L"Sprite\\Tilemap\\Text\\Tilemap04.txt");
		Tilemap* tm4 = _tilemapActor[3]->GetTilemap();
		tm4->ResizeMap(mapSize);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::B))
	{
		GET_SINGLE(ResourceManager)->LoadTilemapOld(L"Tilemap_01", L"Sprite\\Tilemap\\Text\\Tilemap01.txt");
		Tilemap* tm = _tilemapActor[0]->GetTilemap();
		Vec2Int mapSize = tm->GetMapSize();

		GET_SINGLE(ResourceManager)->LoadTilemapOld(L"Tilemap_02", L"Sprite\\Tilemap\\Text\\Tilemap02.txt");
		Tilemap* tm2 = _tilemapActor[1]->GetTilemap();
		tm2->ResizeMap(mapSize);
		GET_SINGLE(ResourceManager)->LoadTilemapOld(L"Tilemap_03", L"Sprite\\Tilemap\\Text\\Tilemap03.txt");
		Tilemap* tm3 = _tilemapActor[2]->GetTilemap();
		tm3->ResizeMap(mapSize);
		GET_SINGLE(ResourceManager)->LoadTilemapOld(L"Tilemap_04", L"Sprite\\Tilemap\\Text\\Tilemap04.txt");
		Tilemap* tm4 = _tilemapActor[3]->GetTilemap();
		tm4->ResizeMap(mapSize);
	}
}

void TileMapScene::ChangeSprite()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_1))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Buildings"));
		_tilemapType = Tilemap_TYPE::PLAT_Buildings;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_2))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Mount"));
		_tilemapType = Tilemap_TYPE::PLAT_Mount;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_3))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Nature"));
		_tilemapType = Tilemap_TYPE::PLAT_Nature;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_4))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PLAT_Props"));
		_tilemapType = Tilemap_TYPE::PLAT_Props;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_5))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Buildings"));
		_tilemapType = Tilemap_TYPE::Buildings;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_6))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Caves"));
		_tilemapType = Tilemap_TYPE::Caves;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_7))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Mounts"));
		_tilemapType = Tilemap_TYPE::Mounts;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_8))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Nature"));
		_tilemapType = Tilemap_TYPE::Nature;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_9))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Props"));
		_tilemapType = Tilemap_TYPE::Props;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::T))
	{
		ChangeSelectedSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tree"));
		_tilemapType = Tilemap_TYPE::Tree;
	}
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

bool TileMapScene::SaveHDCToBMP(HDC hdc, int32 width, int32 height, const char* filePath)
{
	// 호환 가능한 비트맵 생성 (비어 있는 상태)
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, width, height);
	if (!hBitmap) {
		return false;
	}

	// HDC와 호환되는 메모리 DC 생성
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	if (!hMemDC) {
		::DeleteObject(hBitmap);
		return false;
	}

	// 메모리 DC에 호환 비트맵 선택
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

	// 메모리 DC 초기화: 배경을 흰색(또는 다른 원하는 색)으로 설정
	HBRUSH hBrush = ::CreateSolidBrush(RGB(255, 0, 255));  // 마젠타색으로 초기화
	RECT rc = { 0, 0, width, height };
	::FillRect(hMemDC, &rc, hBrush);
	::DeleteObject(hBrush);  // 브러시 해제

	// 원하는 이미지만 그리기
	{
		Vec2 pos = _tilemapActor[_selectedLayer]->GetPos();
		_tilemapActor[_selectedLayer]->SetPos({ 0, 0 });

		_tilemapActor[_selectedLayer]->SetShowAll(true);

		_tilemapActor[_selectedLayer]->Render(hMemDC);
		Tilemap* tm = _tilemapActor[_selectedLayer]->GetTilemap();

		_tilemapActor[_selectedLayer]->SetShowAll(false);
		_tilemapActor[_selectedLayer]->SetPos(pos);
	}

	// BITMAPINFO 구조체 생성
	BITMAPINFO bmpInfo;
	::ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;                          // 24비트 컬러
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// 비트맵 데이터 메모리 할당
	int32 bmpDataSize = ((width * 24 + 31) / 32) * 4 * height;  // 행 크기는 4바이트의 배수여야 함
	BYTE* bmpData = new BYTE[bmpDataSize];
	if (!bmpData) {
		::SelectObject(hMemDC, hOldBitmap);
		::DeleteDC(hMemDC);
		::DeleteObject(hBitmap);
		return false;
	}

	// 비트맵 데이터 가져오기
	::GetDIBits(hMemDC, hBitmap, 0, height, bmpData, &bmpInfo, DIB_RGB_COLORS);

	// .bmp 파일 생성 (ofstream 사용)
	std::ofstream file(filePath, std::ios::out | std::ios::binary);
	if (!file) {
		delete[] bmpData;
		::SelectObject(hMemDC, hOldBitmap);
		::DeleteDC(hMemDC);
		::DeleteObject(hBitmap);
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
	::SelectObject(hMemDC, hOldBitmap);
	::DeleteDC(hMemDC);
	::DeleteObject(hBitmap);

	return true;
}
