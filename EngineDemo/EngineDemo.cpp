// EngineDemo.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <objbase.h>
#include "framework.h"
#include "EngineDemo.h"
#include "GameProcess.h"
#include "CornSerialFarmer.h"
#include <crtdbg.h>  


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	// 지정된 힙에 대한 기능을 사용하도록 설정합니다.
	// 손상에 대한 종료 기능을 사용하도록 설정합니다. 힙 관리자가 프로세스에서 사용하는 모든 힙에서 오류를 감지하면 Windows 오류 보고 서비스를 호출하고 프로세스를 종료합니다. 
	// by msdn
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(61766);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			EngineDemo* engineDemo = nullptr;
			engineDemo = new EngineDemo;

			if (SUCCEEDED(engineDemo->Initialize()))
			{
				engineDemo->RunMessageLoop();
			}

			engineDemo->Finalize();
			delete engineDemo;
		}
		CoUninitialize();
	}
	
	return 0;
}

EngineDemo::EngineDemo() :
    m_hWnd(nullptr),
	m_GameProcess(nullptr),
	m_ScreenWidth(1920),
	m_ScreenHeight(1080)
{

}

EngineDemo::~EngineDemo()
{

}

HRESULT EngineDemo::Initialize()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"ZICOEngineDemo";
    wcex.hIconSm = nullptr;

	RegisterClassExW(&wcex);

	m_hWnd = CreateWindowW(
		L"ZICOEngineDemo",
		L"ZICO EngineDemo V2",
		WS_POPUP,
		CW_USEDEFAULT, 
        0, 
		m_ScreenWidth,
        m_ScreenHeight, 
        nullptr, 
        nullptr, 
        HINST_THISCOMPONENT,	
        this);



	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
	
	LPCWSTR cursorFilePath = L"cursor.cur";
	customCursor = LoadCursorFromFile(cursorFilePath);

	if (customCursor) {
		// 마우스 커서 변경
		SetCursor(customCursor);

		// 변경된 커서 즉시 표시
		ShowCursor(TRUE);

	}
	else {
		// 커서 로드 실패 처리
	}

	/// 게임엔진 초기화는 이 밑에서 한다.
	m_GameProcess = new GameProcess(m_hWnd);
	
	CornSerialFarmer game(m_GameProcess);
	game.InitializeGame();



	return S_OK;
}



void EngineDemo::Finalize()
{
	m_GameProcess->Finalize();
	delete m_GameProcess;
}

// #include "../D2Dimgui/imgui_impl_win32.h"
// extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EngineDemo::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
// 	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
// 		return true;



	switch (message)
	{
		case WM_SETCURSOR:
			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(customCursor);
				ShowCursor(TRUE);

				return TRUE;
			}
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void EngineDemo::RunMessageLoop()
{
	MSG msg;

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			


			m_GameProcess->GameLoop();
		}
	}
}

HCURSOR EngineDemo::customCursor;
