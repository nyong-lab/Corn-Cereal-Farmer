#include "FarmFSM.h"

#include "GameObject.h"

FarmFSM::FarmFSM(GameObject* owner)
	: m_FarmWaterState(this)
	, m_FarmNoWaterState(this)
{
	m_Owner = owner;

	AddState(&m_FarmWaterState);
	AddState(&m_FarmNoWaterState);

	string initState = "FarmNoWater";
	SetInitialState(initState);
	m_DetailState = "NoSeed";
}

FarmFSM::~FarmFSM()
{
}

void FarmFSM::Update(float deltaTime)
{
	StateMachine::Update(deltaTime);
}
