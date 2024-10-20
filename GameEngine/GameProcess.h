/// 2023.07.25
/// �ۼ���: ��â��
/// ������ ���� ������ ����ϴ� Ŭ����

#pragma once
#include <vector>


#include <windows.h>
/// ������ ���漱��

class Input;
class TimeManager;
class ResourceManager;
class GraphicsEngine;
class SceneManager;
class CollisionManager;
class GameObject;
class UIManager;
class SoundManager;

class GameProcess
{

public:

	GameProcess(HWND hWnd);
	~GameProcess();

public:
	/// �ڵ� �����츦 �޾� �ʱ�ȭ�Ѵ�.

	HRESULT Initialize();

	/// ��������� �������μ��� ���� �� ȣ���Ų��.
	void Finalize();

	/// ������ ������Ʈ�� ������ ����ִ� ���ӷ���
	void GameLoop();

	/// ������Ʈ�� ����
	void Update();
	void Render();

public:
	SceneManager* GetSceneManager() { return m_SceneManager; }
	
	bool ShowDebug();

private:
	bool m_ShowDebug;
	const float fps = 60;
	float accumulator = 0;
	HWND m_hWnd;

	Input* m_Input;
	TimeManager* m_TimeManager;
	GraphicsEngine* m_GraphicsEngine;
	SceneManager* m_SceneManager;
	ResourceManager* m_ResourceManager;
	CollisionManager* m_CollisionManager;
	UIManager* m_UIManager;
	SoundManager* m_SoundManager;
};

