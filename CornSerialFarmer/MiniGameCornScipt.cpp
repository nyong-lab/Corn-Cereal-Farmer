#include "MiniGameCornScipt.h"
#include "Input.h"
#include "Transform.h"
#include "../Math/Mathf.h"
#include "ImageRenderer.h"
#include "EventManager.h"

MiniGameCornScipt::MiniGameCornScipt() :
	MonoBehaviour(typeid(this).name()),
	m_IsSelected(false)
{
}

MiniGameCornScipt::~MiniGameCornScipt()
{
}

void MiniGameCornScipt::Start()
{
}

void MiniGameCornScipt::Update(float deltaTime)
{

	if (BASKETBOUND.Contains(m_Transform->GetWorldPosition()) && !m_IsComplete && !m_IsSelected)
	{
		m_Renderer->FadeOut(0.5f);
		m_IsComplete = true;
		EventManager::GetInstance()->SendEvent("CornComplete", nullptr);
	}

	Vector2 mousePos = Input::GetMousePos();
	if (Input::GetKeyDown(KEY::LBTN) && !m_IsComplete)
	{

		Vector2 pos = { m_Transform->GetWorldMatrix().dx, m_Transform->GetWorldMatrix().dy };
		Vector2 size = m_Transform->GetSize();
		
		float clampX = Mathf::Clamp(mousePos.x, pos.x - size.x / 2.f, pos.x + size.x / 2.f);
		float clampY = Mathf::Clamp(mousePos.y, pos.y - size.y / 2.f, pos.y + size.y / 2.f);

		if (mousePos == Vector2(clampX, clampY))
		{
			m_IsSelected = true;
			m_ClickOffset = mousePos - pos;
		}
	}

	if (Input::GetKeyUp(KEY::LBTN) && !m_IsComplete)
	{
		
		if (m_IsSelected)
		{
			m_IsSelected = false;
			m_ClickOffset = Vector2{ 0.f, 0.f };
		}
	}

	if (m_IsSelected)
	{
		m_Transform->SetLocalPosition({mousePos.x - m_ClickOffset.x - 960,mousePos.y - m_ClickOffset.y - 540});
	}

}

void MiniGameCornScipt::FixedUpdate(float deltaTime)
{
}

void MiniGameCornScipt::Finalize()
{
}
