#include "CutSceneScript.h"
#include "Input.h"
#include "TextRenderer.h"
#include "ImageRenderer.h"
#include "Image.h"
#include "GameplayStatics.h"
#include "ResourceManager.h"

CutSceneScript::CutSceneScript() :
	MonoBehaviour(typeid(this).name())
{
}

CutSceneScript::~CutSceneScript()
{
}

void CutSceneScript::Start()
{
}

void CutSceneScript::BtnCallBack()
{
	if (!m_IsPlaying && m_StringSize < m_Text[m_Index].size())
	{
		m_IsPlaying = true;
	}
	else if (m_StringSize < m_Text[m_Index].size() && m_IsPlaying)
	{
		m_StringSize = static_cast<float>(m_Text[m_Index].size());
	}
	else if (m_StringSize >= m_Text[m_Index].size())
	{
		m_StringSize = 0.f;
		m_Index++;
	}

	if (m_Index >= static_cast<int>(m_Text.size()))
	{
		GameplayStatics::LoadScene(m_NextSceneName);
		return;
	}
}

void CutSceneScript::Update(float deltaTime)
{
	if (!m_IsButtonHandled)
	{
		m_ElipseTime += deltaTime;
		if (m_ElipseTime > 1.f)
		{
			m_SpaceRenderer->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonDown", L"/CutScene/SpaceBar/1_1.png")->GetImage()
			);
			m_ElipseTime -= 1.f;
		}
		else if (m_ElipseTime > .5f)
		{
			m_SpaceRenderer->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage()
			);
		}

	}
	
	if (Input::GetKey(KEY::SPACE))
	{
		m_IsButtonHandled = true;
		m_SpaceRenderer->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonDown", L"/CutScene/SpaceBar/1_1.png")->GetImage()
		);
	}

	if (Input::GetKeyUp(KEY::SPACE))
	{
		m_IsButtonHandled = false;
		BtnCallBack();
	}

	if (m_Index >= static_cast<int>(m_Text.size()))
	{
		return;
	}

	if (m_StringSize < m_Text[m_Index].size() && m_IsPlaying)
	{
		m_StringSize += 20 * deltaTime;
	}

	if (m_StringSize >= m_Text[m_Index].size() && m_IsPlaying)
	{
		m_IsPlaying = false;
	}


	if (m_Index < static_cast<int>(m_Text.size()))
	{
		std::wstring temp;
		temp.assign(m_Text[m_Index].begin(), m_Text[m_Index].begin() + (int)m_StringSize);
		m_TextRenderer->SetText(temp);
		m_ImageRenderer->SetImage(m_CutSceneImage[m_Index]->GetImage());
	}

}

void CutSceneScript::FixedUpdate(float deltaTime)
{
}

void CutSceneScript::Finalize()
{
}
