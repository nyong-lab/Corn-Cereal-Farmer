#include "PoliceCatchState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"

PoliceCatchState::PoliceCatchState(StateMachine* owner)
	:FSMState(owner, "PoliceCatch")
{

}

PoliceCatchState::~PoliceCatchState()
{

}

void PoliceCatchState::Enter()
{
	m_Machine->m_Owner->GetObjectChild("police1TextBubble")->GetComponent<Animator>()->Play(L"ExclamationMark", true);
	m_Machine->m_Owner->GetObjectChild("police1TextBubble")->SetActivate(true);
}

void PoliceCatchState::Update(float deltaTime)
{
	m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceFind", true);
}

void PoliceCatchState::Exit()
{
	m_Machine->m_Owner->GetObjectChild("police1TextBubble")->SetActivate(false);
}
