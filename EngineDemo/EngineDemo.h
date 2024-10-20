/// 2023.07.24 
/// �ۼ��� : ��â��
///	���� ���� ���������� Ŭ������ ��� �����ڴ�

#pragma once

#include "resource.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class GameProcess;


/// ������ ���ø����̼��� �����ϱ� ���� �����������
/// Ŭ����ȭ �س�����
class EngineDemo
{
public:
	EngineDemo();
	~EngineDemo();

	/// �뵵: â Ŭ������ ��� �� �� �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
	/// �ּ�:
	///      �� �Լ��� ���� �ڵ��������� ��������� �����ϰ� �� ���α׷� â�� ���� ���� ǥ���մϴ�.
	HRESULT Initialize();

	/// ���� �� ����� �ؾ� �� �͵��� ��Ƴ��´�.
	void Finalize();

	/// �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
	/// �뵵: �� â�� �޽����� ó���մϴ�.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/// PeekMessage�� ���� �������� �޽��� ������ ó���Ѵ�.
	void RunMessageLoop();

private:
	HWND m_hWnd;
	GameProcess* m_GameProcess;
	// ȭ�� ũ��
	const int m_ScreenWidth;
	const int m_ScreenHeight;

	static HCURSOR customCursor;
};