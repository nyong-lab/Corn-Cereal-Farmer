/// 2023.07.25
/// 작성자: 정창도
/// 게임의 메인 루프를 담당하는 클래스

#pragma once
#include <vector>


#include <windows.h>
/// 포인터 전방선언

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
	/// 핸들 윈도우를 받아 초기화한다.

	HRESULT Initialize();

	/// 명시적으로 게임프로세스 종료 시 호출시킨다.
	void Finalize();

	/// 게임의 업데이트와 렌더가 들어있는 게임루프
	void GameLoop();

	/// 업데이트랑 렌더
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

