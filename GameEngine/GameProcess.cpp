#include "pch.h"
#include "GameProcess.h"

#include "Input.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

#include "Resource.h"

#include "Image.h"
#include "Font.h"
#include "CollisionManager.h"

#include "Animator.h"
#include "Animation.h"

#include "ResourceManager.h"
#include "EventManager.h"

#include "UIManager.h"
#include "UI.h"
#include "Scene.h"
#include "SoundManager.h"

GameProcess::GameProcess(HWND hWnd) :
	m_hWnd(hWnd),
	m_Input(nullptr),
	m_TimeManager(nullptr),
	m_GraphicsEngine(nullptr),
	m_SceneManager(nullptr),
	m_ResourceManager(nullptr),
	m_CollisionManager(nullptr),
	m_UIManager(nullptr),
	m_SoundManager(nullptr),
	m_ShowDebug(false)
{
	m_GraphicsEngine = GraphicsEngine::GetInstance();
	m_Input = Input::GetInstance();
	m_TimeManager = new TimeManager;
	m_SceneManager = new SceneManager;
	m_CollisionManager = new CollisionManager;
	m_UIManager = new UIManager;
	m_ResourceManager = ResourceManager::GetInstance();
	m_SoundManager = SoundManager::GetInstance();
}


GameProcess::~GameProcess()
{


}

HRESULT GameProcess::Initialize()
{
// 	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
// 	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
// 	int WinPosX = screenWidth / 2 - 1920 / 2;
// 	int WinPosY = screenHeight / 2 - 1080 / 2;
// 
// 	// 해상도에 맞게 윈도우 크기 조정
// 	RECT rt = { 0, 0, (long)1920, (long)1080 };
// 	AdjustWindowRect(&rt, WS_POPUP, false);
// 	SetWindowPos(m_hWnd, nullptr, 0 /*WinPosX - 10*/, 0/*WinPosY*/, rt.right - rt.left, rt.bottom - rt.top, 0);

	// 그래픽스엔진 명시적 초기화
	m_GraphicsEngine->Initialize(m_hWnd);
	
	/// 입력 초기화
	m_Input->Initialize();

	/// 타임매니저 초기화
	m_TimeManager->Initailize();

	/// 신매니저 초기화
	m_SceneManager->Initialize();

	/// 콜리전 매니저 초기화
	m_CollisionManager->Initialize(m_SceneManager);

	/// UI 매니저 초기화
	m_UIManager->Initialize(m_SceneManager);

	/// 이벤트 매니저 초기화
	EventManager::GetInstance()->Initialize(m_SceneManager, m_CollisionManager, m_TimeManager);

	/// 사운드 매니저 초기화
	SoundManager::GetInstance()->Initialize();

	m_SceneManager->GetCurrentScene()->Enter();
	m_SceneManager->GetCurrentScene()->Start();
	m_CollisionManager->Enter();
	return S_OK;
}

void GameProcess::Finalize()
{
	Input::ReleaseInstance();

	// 그래픽스엔진 명시적 해제
	m_GraphicsEngine->Finalize();
	GraphicsEngine::Destroy();
	
	/// 타임매니저 메모리 해제
	delete m_TimeManager;

	/// 신매니저 메모리 해제
	/// 이벤트매니저 해제
	EventManager::GetInstance()->Finalize();
	EventManager::GetInstance()->ReleaseInstance();
	/// 이벤트가 dll이기때문에 잘 지우려면 이벤트 먼저 지워야한다.
	/// 신매니저에 코드조각이 있는데 신매니저 먼저 지워버리면
	/// dll연결을 끊어서 오류가 뜬다.
	m_SceneManager->Finalize();
	delete m_SceneManager;

	/// 리소스 할당 해제 및 
	/// 리소스매니저 해제
	ResourceManager::GetInstance()->Finalize();
	ResourceManager::ReleaseInstance();

	/// 콜리전 매니저 해제
	m_CollisionManager->Finalize();;
	delete m_CollisionManager;

	/// 사운드매니저 해제
	SoundManager::GetInstance()->Finalize();
	SoundManager::ReleaseInstance();

	/// UI매니저 해제
	delete m_UIManager;

}

void GameProcess::GameLoop()
{

	Update();
	
	Render();

	EventManager::GetInstance()->ProcessEvents();
	
}

void GameProcess::Update()
{
	/// 매니저를 업데이트한다
	m_Input->Update();

	m_TimeManager->Update();
	float deltaTime = m_TimeManager->GetDeltaTime();

	m_UIManager->Update();

	m_SceneManager->Update(deltaTime);

	int count = 0;

	m_SceneManager->FixedUpdate(deltaTime);
	m_CollisionManager->Update();

	m_SoundManager->Update();	
}

void GameProcess::Render()
{
 	
	GraphicsEngine::GetInstance()->BeginRender();

	m_SceneManager->Render();
	
	if (ShowDebug())
	{
		m_SceneManager->DebugRender();
	}

	GraphicsEngine::GetInstance()->EndRender();

}

bool GameProcess::ShowDebug()
{
	if (Input::GetKeyDown(KEY::F4))
	{
		m_ShowDebug = !m_ShowDebug;
	}

	return m_ShowDebug;
}

