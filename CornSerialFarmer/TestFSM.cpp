#include "TestFSM.h"

#include "GameObject.h"
#include "Transform.h"

TestFSM::TestFSM(GameObject* owner)
	: m_IdleState(this)
	, m_WalkState(this)
	, m_TalkState(this)
	, m_WateringState(this)
	, m_MoveBodyState(this)
	, m_HarvestState(this)
	, m_InteractionState(this)
	
{
	//변수 할당
	m_Owner = owner;


	//상태추가 (map에 저장)
	AddState(&m_IdleState);
	AddState(&m_WalkState);
	AddState(&m_TalkState);
	AddState(&m_WateringState);
	AddState(&m_MoveBodyState);
	AddState(&m_HarvestState);
	AddState(&m_InteractionState);

	//초기 상태 지정
	string initState = "Idle";
	SetInitialState(initState);
	m_DetailState = "IdleFront";
}

TestFSM::~TestFSM()
{

}

void TestFSM::Update(float deltaTime)
{

	StateMachine::Update(deltaTime);
}
