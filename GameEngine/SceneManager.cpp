#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : 
	m_CurrentScene(nullptr)

{

}

SceneManager::~SceneManager()
{
	

}

void SceneManager::Initialize()
{


}

void SceneManager::Finalize()
{
	for (auto& iter : m_Scenes)
	{
		if (iter.second != nullptr)
		{
			iter.second->Exit();
			delete iter.second;
		}

	}

}

void SceneManager::Start()
{
	m_CurrentScene->Start();
}

void SceneManager::Update(float deltaTime)
{
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::FixedUpdate(float deltaTime)
{
	m_CurrentScene->FixedUpdate(deltaTime);
}

void SceneManager::Render()
{
	m_CurrentScene->Render();
}


void SceneManager::DebugRender()
{
	m_CurrentScene->DebugRender();
}

void SceneManager::LoadScene(const string& sceneName)
{
	m_CurrentScene->Exit();
	m_CurrentScene = m_Scenes.find(sceneName)->second;
	assert(m_CurrentScene);
	m_CurrentScene->Resume();
	m_CurrentScene->Enter();
	m_CurrentScene->Start();

}

void SceneManager::SetStartScene(const string& sceneName)
{
	assert(m_Scenes.find(sceneName) != m_Scenes.end() && "씬 추가해주고쓰자");
	m_CurrentScene = m_Scenes.find(sceneName)->second;
	

}

void SceneManager::AddScene(Scene* scene)
{
	m_Scenes.emplace(scene->GetName(), scene);
}

