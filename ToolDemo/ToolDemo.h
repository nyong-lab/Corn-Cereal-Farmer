#pragma once

#include <vector>
#include "resource.h"
#include "stb_image.h"


/// ������ ���漱��
class D2DEngine1;

/// Object ���漱��
class Object;

class MyRectangle;
class MyHeart;

class ToolDemo
{
public:
	ToolDemo();
	~ToolDemo();

	/// ���� �� ����� �ؾ� �� �͵��� ��Ƴ��´�.
	void Finalize();

	/// �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
	/// �뵵: �� â�� �޽����� ó���մϴ�.
	//LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/// PeekMessage�� ���� �������� �޽��� ������ ó���Ѵ�.
	void RunMessageLoop();

	/// Update, Render
	void Update();
	void Render();

	/// ���� ������ ���� �Լ���
	bool AABBCheck(float rect1X, float rect1Width, float rect1Y, float rect1Height, float rect2X, float rect2Width, float rect2Y, float rect2Height);
	void createNewRectangle();

private:
	std::vector<Object*> m_ObjectList;

	int rectangleID;
	int heartID;
};

