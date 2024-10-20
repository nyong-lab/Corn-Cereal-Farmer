#include "WalkState.h"
#include "StateMachine.h"
#include "Input.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "FarmerScript.h"

#include <typeinfo>


WalkState::WalkState(StateMachine* owner)
	:FSMState(owner, "Walk")
{
	//const type_info& _info = typeid(this);
	//m_FSMState = _info.name();
}

WalkState::~WalkState()
{

}

void WalkState::Enter()
{
	
}
void WalkState::Update(float deltaTime)
{
	int speed = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->speed;
	int diagonalSpeed = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->diagonalSpeed;

	/*int speed = 1500;
	int diagonalSpeed = 1000;*/

	Vector2 pos = m_Machine->m_Owner->GetTransform()->GetLocalPosition();
	
	if (m_Machine->m_DetailState.compare("WalkRight") == 0)
	{
		pos.x += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkRight", true);
	}
	if (m_Machine->m_DetailState.compare("WalkLeft") == 0)
	{
		pos.x -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkLeft", true);
	}
	if (m_Machine->m_DetailState.compare("WalkBack") == 0)
	{
		pos.y -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkBack", true);
	}
	if (m_Machine->m_DetailState.compare("WalkFront") == 0)
	{
		pos.y += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkFront", true);
	}

	//´ë°¢¼±
	if (m_Machine->m_DetailState.compare("WalkDownLeft") == 0)
	{
		pos.y += diagonalSpeed * deltaTime;
		pos.x -= diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkLeft", true);
	}
	if (m_Machine->m_DetailState.compare("WalkDownRight") == 0)
	{
		pos.y += diagonalSpeed * deltaTime;
		pos.x += diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkRight", true);
	}
	if (m_Machine->m_DetailState.compare("WalkUpLeft") == 0)
	{
		pos.y -= diagonalSpeed * deltaTime;
		pos.x -= diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkLeft", true);
	}
	if (m_Machine->m_DetailState.compare("WalkUpRight") == 0)
	{
		pos.y -= diagonalSpeed * deltaTime;
		pos.x += diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWalkRight", true);
	}


	m_Machine->m_Owner->GetTransform()->SetLocalPosition(pos);
	//OutputDebugString(TEXT("Walk\n"));
}

void WalkState::Exit()
{

}


