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

	_CrtDumpMemoryLeaks();				// �޸� ���� ã��
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(hdc);									// hdc�� ȣȯ�Ǵ� DC ����
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);				// dcBack�� ��Ʈ�� ����
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, L"..\\Resources");

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::BattleScene);
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
		Utils::DrawText(hdcBack, Vec2Int(10, 10), str);
	}
	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		Utils::DrawText(hdcBack, Vec2Int(550, 10), str);
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY);		// ��Ʈ �� : ��� ����
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, BLACKNESS);				// hdcBack�� ���������� ����� ��
}
