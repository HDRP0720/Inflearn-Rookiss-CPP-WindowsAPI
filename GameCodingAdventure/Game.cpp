#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

Game::Game()
{

}

Game::~Game()
{
	GET_SINGLETON(SceneManager)->Clear();

	// TODO: 할일-주의 마지막 라인에 존재해야함
	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	// Double Buffering
	::GetClientRect(hwnd, &_rect);
	_hdcBack = ::CreateCompatibleDC(_hdc);
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	::DeleteObject(prev);

	GET_SINGLETON(TimeManager)->Init();
	GET_SINGLETON(InputManager)->Init(hwnd);
	GET_SINGLETON(SceneManager)->Init();

	GET_SINGLETON(SceneManager)->ChangeScene(SceneType::DevScene);
}

void Game::Update()
{
	GET_SINGLETON(TimeManager)->Update();
	GET_SINGLETON(InputManager)->Update();
	GET_SINGLETON(SceneManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLETON(TimeManager)->GetFPS();
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	// Mouse Position 확인
	{
		POINT mousePos = GET_SINGLETON(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Frame 관리
	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime));
		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	GET_SINGLETON(SceneManager)->Render(_hdcBack);

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
