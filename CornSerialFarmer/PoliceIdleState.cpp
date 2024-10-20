#include "PoliceIdleState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "BoxCollider.h"


PoliceIdleState::PoliceIdleState(StateMachine* owner)
	:FSMState(owner, "PoliceIdle")
{

}

PoliceIdleState::~PoliceIdleState()
{

}

void PoliceIdleState::Enter()
{

}

void PoliceIdleState::Update(float deltaTime)
{
	if (m_Machine->m_DetailState.compare("IdleRight") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleRight", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(-90);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalPosition(Vector2{ 0.f, 0.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetOffset(Vector2{ 120.f, 20.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetSize(Vector2{ 300, 100 });
	}
	if (m_Machine->m_DetailState.compare("IdleLeft") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleLeft", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(90);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalPosition(Vector2{ 0.f, 0.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetOffset(Vector2{ -120.f, 20.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetSize(Vector2{ 300, 100 });

	}
	if (m_Machine->m_DetailState.compare("IdleBack") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleBack", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalPosition(Vector2{ 0.f, -200.f });
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(0);
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetOffset(Vector2{ 0.f, -80.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetSize(Vector2{ 100, 300 });
	}
	if (m_Machine->m_DetailState.compare("IdleFront") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleFront", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(0);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalPosition(Vector2{ 0.f, 0.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetOffset(Vector2{ 0.f, 120.f });
		//m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<BoxCollider>()->SetSize(Vector2{ 100, 300 });
	}
}

void PoliceIdleState::Exit()
{

}
