#include "BlackCatMoveState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"
#include "BoxCollider.h"

BlackCatMoveState::BlackCatMoveState(StateMachine* owner)
	:FSMState(owner, "BlackCatMove")
{

}

BlackCatMoveState::~BlackCatMoveState()
{
}

void BlackCatMoveState::Enter()
{
}

void BlackCatMoveState::Update(float deltaTime)
{
	Vector2 pos = m_Machine->m_Owner->GetTransform()->GetLocalPosition();
	const float speed = 100;
	//오른쪽으로 이동
	if (m_Machine->m_DetailState.compare("MoveRight") == 0)
	{
		pos.x += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatMoveRight", true);

	}

	//왼쪽으로 이동
	if (m_Machine->m_DetailState.compare("MoveLeft") == 0)
	{
		pos.x -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatMoveLeft", true);
		
	}
	//위로 올라감
	if (m_Machine->m_DetailState.compare("MoveBack") == 0)
	{
		pos.y -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatMoveBack", true);
		
	}
	//아래로 내려감
	if (m_Machine->m_DetailState.compare("MoveFront") == 0)
	{
		pos.y += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatMoveFront", true);
		
	}

	m_Machine->m_Owner->GetTransform()->SetLocalPosition(pos);
}

void BlackCatMoveState::Exit()
{
}
