#include "pch.h"
#include "GameplayStatics.h"
#include "EventManager.h"

void GameplayStatics::LoadScene(string sceneName)
{
	EventManager::GetInstance()->LoadScene(sceneName);
}

void GameplayStatics::CreateObject(GameObject* gameObject)
{
	EventManager::GetInstance()->CreateObject(gameObject);
}

void GameplayStatics::DestroyObject(GameObject* gameObject)
{
	EventManager::GetInstance()->DestroyObject(gameObject);
}

void GameplayStatics::PauseGame()
{
	EventManager::GetInstance()->SendEvent("PauseGame", nullptr);
}

void GameplayStatics::ResumeGame()
{
	EventManager::GetInstance()->SendEvent("ResumeGame", nullptr);
}

void GameplayStatics::SetTimeScale(float timeScale)
{
	EventManager::GetInstance()->SendEvent("SetTimeScale", timeScale);
}