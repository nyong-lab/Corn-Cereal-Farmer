/// [2023/07/28] 박연하
/// ----------------------
/// 그래픽스 엔진 데모용 메인 정리

#include <windows.h>
#include "GraphicsEngine.h"

/// <summary>
/// 여기에 테스트 할 코드를 적으면 된다
/// </summary>
void Render()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::GetInstance();
	//----------------------------------------------------------------

	//graphicsEngine->SetBackgroundColor(0.143f, 0.155f, 0.178f, 1.f);
	graphicsEngine->SetBackgroundColor(0.143f, 0.155f, 0.5f, 1.f);

	/// PRIMITIVE & COLOR
	graphicsEngine->DrawRectangle(Vector2(100, 125), Vector2(50, 50), COLOR::LEMON, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 175), Vector2(50, 50), COLOR::ORANGE, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 225), Vector2(50, 50), COLOR::BABYPINK, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 275), Vector2(50, 50), COLOR::PINKLAVENDER, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 325), Vector2(50, 50), COLOR::LAVENDER, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 375), Vector2(50, 50), COLOR::BABYBLUE, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 425), Vector2(50, 50), COLOR::SKYBLUE, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 475), Vector2(50, 50), COLOR::MINT, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 525), Vector2(50, 50), COLOR::APPLEGREEN, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 575), Vector2(50, 50), COLOR::WHITE, 2.f);
	graphicsEngine->DrawRectangle(Vector2(100, 625), Vector2(50, 50), COLOR::BLACK, 2.f);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int APIENTRY wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPWSTR    lpCmdLine,
	_In_     int       nCmdShow
)
{
	LPCWSTR gameName = L"[ZICO] Graphics Engine Demo";
	WNDCLASS wndclass = {};

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = gameName;

	// 윈도 클래스 등록
	RegisterClassW(&wndclass);

	// 윈도 생성
	HWND hWnd = CreateWindow(
		gameName,
		gameName,
		WS_OVERLAPPEDWINDOW,
		100, 100, 1080, 1080,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return S_FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	GraphicsEngine::GetInstance()->Initialize(hWnd);

	// 메시지 루프
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			GraphicsEngine::GetInstance()->BeginRender();
			Render();
			GraphicsEngine::GetInstance()->EndRender();
		}
	}

	return (int)msg.wParam;
}

