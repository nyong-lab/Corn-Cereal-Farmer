#pragma once

#include <vector>
#include "resource.h"
#include "stb_image.h"


/// 포인터 전방선언
class D2DEngine1;

/// Object 전방선언
class Object;

class MyRectangle;
class MyHeart;

class ToolDemo
{
public:
	ToolDemo();
	~ToolDemo();

	/// 데모 앱 종료시 해야 할 것들을 모아놓는다.
	void Finalize();

	/// 함수: WndProc(HWND, UINT, WPARAM, LPARAM)
	/// 용도: 주 창의 메시지를 처리합니다.
	//LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/// PeekMessage를 통해 윈도우의 메시지 루프를 처리한다.
	void RunMessageLoop();

	/// Update, Render
	void Update();
	void Render();

	/// 대충 실험을 위한 함수들
	bool AABBCheck(float rect1X, float rect1Width, float rect1Y, float rect1Height, float rect2X, float rect2Width, float rect2Y, float rect2Height);
	void createNewRectangle();

private:
	std::vector<Object*> m_ObjectList;

	int rectangleID;
	int heartID;
};

