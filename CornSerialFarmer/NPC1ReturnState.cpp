#include "NPC1ReturnState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "BoxCollider.h"

NPC1ReturnState::NPC1ReturnState(StateMachine* owner)
	:FSMState(owner, "NPC1Return")
{

}
 
NPC1ReturnState::~NPC1ReturnState()
{

}

void NPC1ReturnState::Enter()
{

}

void NPC1ReturnState::Update(float deltaTime)
{
	Vector2 pos = m_Machine->m_Owner->GetTransform()->GetLocalPosition();
	const float speed = 150.f;

	//오른쪽으로 이동
	if (m_Machine->m_DetailState.compare("MoveRight") == 0)
	{
		pos.x += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCMoveRight", true);
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetOffset(Vector2{ 90.f, 20.f });
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetSize(Vector2{ 120, 60 });

	}

	//왼쪽으로 이동
	if (m_Machine->m_DetailState.compare("MoveLeft") == 0)
	{
		pos.x -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCMoveLeft", true);
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetOffset(Vector2{ -90.f, 20.f });
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetSize(Vector2{ 120, 60 });

	}
	//위로 올라감
	if (m_Machine->m_DetailState.compare("MoveBack") == 0)
	{
		pos.y -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCMoveBack", true);
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetOffset(Vector2{ 0.f, -80.f });
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetSize(Vector2{ 60, 120 });
	}
	//아래로 내려감
	if (m_Machine->m_DetailState.compare("MoveFront") == 0)
	{
		pos.y += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCMoveFront", true);
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetOffset(Vector2{ 0.f, 120.f });
		m_Machine->m_Owner->GetObjectChild("NPCView")->GetComponent<BoxCollider>()->SetSize(Vector2{ 60, 120 });
	}
	//정지상태
	if (m_Machine->m_DetailState.compare("IdleFront") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCIdleFront", true);
	}

	m_Machine->m_Owner->GetTransform()->SetLocalPosition(pos);
}

void NPC1ReturnState::Exit()
{

}
