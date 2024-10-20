#include "WildBoarScript.h"


#include "GameManagerScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Define.h"
#include "Animator.h"
#include "Animation.h"
#include "FarmScript.h"


WildBoarScript::WildBoarScript()
	:MonoBehaviour(typeid(this).name())
	, m_IsCollision(false)
	, m_IsClear(false)
	, m_RightEnd(false)
	, m_PauseUpdate(false)
	, m_GameManager(nullptr)
{

}

WildBoarScript::~WildBoarScript()
{

}



void WildBoarScript::Update(float deltaTime)
{
	if (!m_PauseUpdate)
	{
		// 客府啊府
		if (m_GameManager != nullptr)
		{
			if (m_GameManager->isNight == false && m_GameManager->m_IsDay == false)
			{
				Vector2 position = GetGameObject()->GetTransform()->GetLocalPosition();
				if (!m_IsCollision)
				{
					position.x += 400 * deltaTime;

				}
				else if (m_IsCollision)
				{
					if (m_IsClear)
					{
						GetGameObject()->GetObjectChild("wildBoarExclamationMark")->SetActivate(false);
						GetGameObject()->GetComponent<Animator>()->Play(L"WildBoarLeftRun", true);
						if (position.x > -2500.f + 960.f)
						{
							position.x -= 800 * deltaTime;
						}
						else
						{
							m_IsClear = false;
							GetTransform()->SetLocalPosition(Vector2{ -2000.f, -150.f } + Vector2{ 960.f, 540.f });
							GetGameObject()->SetActivate(false);
							m_IsCollision = true;
							m_PauseUpdate = true;
							return;
						}
					}

					else if (!m_RightEnd)
					{
						GetGameObject()->GetComponent<Animator>()->Play(L"WildBoarRightRun", true);
						if (position.x < 1100.f + 960.f)
						{
							position.x += 300 * deltaTime;
						}
						else
						{
							m_RightEnd = true;
						}
					}
					else if (m_RightEnd)
					{
						GetGameObject()->GetComponent<Animator>()->Play(L"WildBoarLeftRun", true);
						if (position.x > 230.f + 960.f)
						{
							position.x -= 300 * deltaTime;
						}
						else
						{
							m_RightEnd = false;
						}
					}
				}

				GetGameObject()->GetTransform()->SetLocalPosition(position);
			}
		}
	}
	

	// 力磊府
	/*if (!m_IsCollision)
	{
		Vector2 position = GetGameObject()->GetTransform()->GetLocalPosition();
		position.x += 300 * deltaTime;
		GetGameObject()->GetTransform()->SetLocalPosition(position);
	}*/
}

void WildBoarScript::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::FARM)
	{
		if (!m_IsCollision)
		{
			m_IsCollision = true;

			GetGameObject()->GetObjectChild("wildBoarExclamationMark")->SetActivate(true);
		}
	}
}

void WildBoarScript::OnCollisionStay(const Manifold& collision)
{

}

void WildBoarScript::OnCollisionExit(const Manifold& collision)
{

}

