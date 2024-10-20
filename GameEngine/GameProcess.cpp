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
// 	// �ػ󵵿� �°� ������ ũ�� ����
// 	RECT rt = { 0, 0, (long)1920, (long)1080 };
// 	AdjustWindowRect(&rt, WS_POPUP, false);
// 	SetWindowPos(m_hWnd, nullptr, 0 /*WinPosX - 10*/, 0/*WinPosY*/, rt.right - rt.left, rt.bottom - rt.top, 0);

	// �׷��Ƚ����� ����� �ʱ�ȭ
	m_GraphicsEngine->Initialize(m_hWnd);
	
	/// �Է� �ʱ�ȭ
	m_Input->Initialize();

	/// Ÿ�ӸŴ��� �ʱ�ȭ
	m_TimeManager->Initailize();

	/// �ŸŴ��� �ʱ�ȭ
	m_SceneManager->Initialize();

	/// �ݸ��� �Ŵ��� �ʱ�ȭ
	m_CollisionManager->Initialize(m_SceneManager);

	/// UI �Ŵ��� �ʱ�ȭ
	m_UIManager->Initialize(m_SceneManager);

	/// �̺�Ʈ �Ŵ��� �ʱ�ȭ
	EventManager::GetInstance()->Initialize(m_SceneManager, m_CollisionManager, m_TimeManager);

	/// ���� �Ŵ��� �ʱ�ȭ
	SoundManager::GetInstance()->Initialize();

	m_SceneManager->GetCurrentScene()->Enter();
	m_SceneManager->GetCurrentScene()->Start();
	m_CollisionManager->Enter();
	return S_OK;
}

void GameProcess::Finalize()
{
	Input::ReleaseInstance();

	// �׷��Ƚ����� ����� ����
	m_GraphicsEngine->Finalize();
	GraphicsEngine::Destroy();
	
	/// Ÿ�ӸŴ��� �޸� ����
	delete m_TimeManager;

	/// �ŸŴ��� �޸� ����
	/// �̺�Ʈ�Ŵ��� ����
	EventManager::GetInstance()->Finalize();
	EventManager::GetInstance()->ReleaseInstance();
	/// �̺�Ʈ�� dll�̱⶧���� �� ������� �̺�Ʈ ���� �������Ѵ�.
	/// �ŸŴ����� �ڵ������� �ִµ� �ŸŴ��� ���� ����������
	/// dll������ ��� ������ ���.
	m_SceneManager->Finalize();
	delete m_SceneManager;

	/// ���ҽ� �Ҵ� ���� �� 
	/// ���ҽ��Ŵ��� ����
	ResourceManager::GetInstance()->Finalize();
	ResourceManager::ReleaseInstance();

	/// �ݸ��� �Ŵ��� ����
	m_CollisionManager->Finalize();;
	delete m_CollisionManager;

	/// ����Ŵ��� ����
	SoundManager::GetInstance()->Finalize();
	SoundManager::ReleaseInstance();

	/// UI�Ŵ��� ����
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
	/// �Ŵ����� ������Ʈ�Ѵ�
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

