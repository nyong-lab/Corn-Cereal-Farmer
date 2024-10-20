/// 2023.07.24 
/// 작성자 : 정창도
///	엔진 데모 실행파일을 클래스로 묶어서 만들어보겠다

#pragma once

#include "resource.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class GameProcess;


/// 윈도우 애플리케이션을 실행하기 위한 전역변수들들
/// 클래스화 해놓은것
class EngineDemo
{
public:
	EngineDemo();
	~EngineDemo();

	/// 용도: 창 클래스를 등록 한 후 인스턴스 핸들을 저장하고 주 창을 만듭니다.
	/// 주석:
	///      이 함수를 통해 핸들윈도우을 멤버변수에 저장하고 주 프로그램 창을 만든 다음 표시합니다.
	HRESULT Initialize();

	/// 데모 앱 종료시 해야 할 것들을 모아놓는다.
	void Finalize();

	/// 함수: WndProc(HWND, UINT, WPARAM, LPARAM)
	/// 용도: 주 창의 메시지를 처리합니다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/// PeekMessage를 통해 윈도우의 메시지 루프를 처리한다.
	void RunMessageLoop();

private:
	HWND m_hWnd;
	GameProcess* m_GameProcess;
	// 화면 크기
	const int m_ScreenWidth;
	const int m_ScreenHeight;

	static HCURSOR customCursor;
};