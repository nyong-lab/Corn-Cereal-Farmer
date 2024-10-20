#include "pch.h"
#include "ResourceManager.h"
#include "Resource.h"
ResourceManager::ResourceManager()
	: m_Resources{}
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Initialize()
{

}

void ResourceManager::Finalize()
{
	// 리소스 해제
	for (auto& resource : m_Resources)
	{
		resource.second->UnLoad();
		delete resource.second;
	}
}

ResourceManager* ResourceManager::g_Instance = nullptr;
