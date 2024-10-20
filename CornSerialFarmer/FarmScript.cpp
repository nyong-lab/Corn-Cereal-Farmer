#include "FarmScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Input.h"


#include "StateMachine.h"
#include "FarmFSM.h"

FarmScript::FarmScript()
	: MonoBehaviour(typeid(this).name())
	, m_FarmStateMachine(nullptr)
	, farmState("FarmNoWater")
	, detailState("NoSeed")
	, completeQuestCount(0)
	, isInteraction(false)
	, isDestroyFarm(false)
	, farmNumber(0)
	, fakeSeed(false)
{
}

FarmScript::~FarmScript()
{

}

void FarmScript::Start()
{
	m_FarmStateMachine = new FarmFSM(GetGameObject());
}

void FarmScript::Update(float deltaTime)
{
	m_FarmStateMachine->ChangeDetailState(detailState);
	m_FarmStateMachine->ChangeState(farmState);
	m_FarmStateMachine->Update(deltaTime);
}

void FarmScript::Finalize()
{
	m_FarmStateMachine->Finalize();
	delete m_FarmStateMachine;
}
