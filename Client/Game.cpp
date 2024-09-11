#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{
}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	_CrtDumpMemoryLeaks();				// 메모리 누수 찾기
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(hdc);									// hdc와 호환되는 DC 생성
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom);	// hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);				// dcBack과 비트맵 연결
	::DeleteObject(prev);

	LoadFont();

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, L"..\\Resources");

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::EditScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	GET_SINGLE(SceneManager)->Render(hdcBack);

	uint32 fps = GET_SINGLE(TimeManager)->GetFPS();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();		
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		Utils::DrawTextSize(hdcBack, Vec2Int(10, 10), 20, str);
	}
	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		Utils::DrawTextSize(hdcBack, Vec2Int(550, 10), 20, str);
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY);		// 비트 블릿 : 고속 복사
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, BLACKNESS);				// hdcBack을 검은색으로 만들어 줌
}

void Game::LoadFont()
{
	// 폰트 받아오기
	if (::AddFontResourceEx(L"..\\Resources\\font\\PokePT_Wansung.ttf", FR_PRIVATE, 0) == 0)
	{
		::MessageBox(_hwnd, L"..\\Resources\\font\\PokePT_Wansung.ttf", L"Font Load Failed", NULL);
	}
	
	// 폰트 생성
	HFONT hFont = ::CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PokePT_Wansung" // 폰트 이름
	);

	HFONT hOldFont = (HFONT)::SelectObject(hdcBack, hFont);
	::DeleteObject(hOldFont);
}
