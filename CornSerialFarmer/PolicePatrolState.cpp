#include "PolicePatrolState.h"
#include "StateMachine.h"
#include "Input.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "BoxCollider.h"


#include "Police2Script.h"

PolicePatrolState::PolicePatrolState(StateMachine* owner)
	:FSMState(owner, "PolicePatrol")
{

}

PolicePatrolState::~PolicePatrolState()
{

}

void PolicePatrolState::Enter()
{

}

void PolicePatrolState::Update(float deltaTime)
{
	
	int speed = dynamic_cast<Police2Script*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->speed;

	Vector2 pos = m_Machine->m_Owner->GetTransform()->GetLocalPosition();
	float angle = m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->GetLocalRotation();
	
	//오른쪽으로 이동
	if (m_Machine->m_DetailState.compare("MoveRight") == 0)
	{
		pos.x += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceMoveRight", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(-90);

	}
	//왼쪽으로 이동
	if (m_Machine->m_DetailState.compare("MoveLeft") == 0)
	{
		pos.x -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceMoveLeft", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(90);

	}
	//위로 올라감
	if (m_Machine->m_DetailState.compare("MoveBack") == 0)
	{
		pos.y -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceMoveBack", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(180);

	}
	//아래로 내려감
	if (m_Machine->m_DetailState.compare("MoveFront") == 0)
	{
		pos.y += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceMoveFront", true);
		m_Machine->m_Owner->GetObjectChild("police1View")->GetComponent<Transform>()->SetLocalRotation(0);

	}

	m_Machine->m_Owner->GetTransform()->SetLocalPosition(pos);
}

void PolicePatrolState::Exit()
{

}
