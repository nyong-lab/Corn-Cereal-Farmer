#include "MoveBodyState.h"
#include "StateMachine.h"
#include "Input.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "FarmerScript.h"

#include "TextRenderer.h"

MoveBodyState::MoveBodyState(StateMachine* owner)
	:FSMState(owner, "MoveBody")
{

}

MoveBodyState::~MoveBodyState()
{

}

void MoveBodyState::Enter()
{

}

void MoveBodyState::Update(float deltaTime)
{
	int speed = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->speed;
	int diagonalSpeed = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->diagonalSpeed;
	float timeOut = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->timeCount;

	Vector2 pos = m_Machine->m_Owner->GetTransform()->GetLocalPosition();
	m_Machine->m_Owner->GetComponent<BoxCollider>()->SetOffset(Vector2{ 20, 20 });
	m_Machine->m_Owner->GetComponent<BoxCollider>()->SetSize(Vector2{ 100.f, 120.f });

	if (Input::GetKey(KEY::D))
	{
		pos.x += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyRight", true);
	}
	if (Input::GetKey(KEY::A))
	{
		pos.x -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyLeft", true);
	}
	if (Input::GetKey(KEY::W))
	{
		pos.y -= speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyRight", true);
	}
	if (Input::GetKey(KEY::S))
	{
		pos.y += speed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyRight", true);
	}

	//대각선
	if (Input::GetKey(KEY::S) && Input::GetKey(KEY::A))
	{
		pos.y += diagonalSpeed * deltaTime;
		pos.x -= diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyLeft", true);
	}
	if (Input::GetKey(KEY::S) && Input::GetKey(KEY::D))
	{
		pos.y += diagonalSpeed * deltaTime;
		pos.x += diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyRight", true);
	}
	if (Input::GetKey(KEY::W) && Input::GetKey(KEY::A))
	{
		pos.y -= diagonalSpeed * deltaTime;
		pos.x -= diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyLeft", true);
	}
	if (Input::GetKey(KEY::W) && Input::GetKey(KEY::D))
	{
		pos.y -= diagonalSpeed * deltaTime;
		pos.x += diagonalSpeed * deltaTime;
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerMoveBodyRight", true);
	}

	//말풍선
	if (timeOut > 7 && timeOut < 9)
	{
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<Animator>()->Play(L"TextBubble", true);
		wstring dateText = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->textOut;
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::BLACK);
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetText(dateText.c_str());
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->SetActivate(true);
		
	}
	else
	{
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->SetActivate(false);
		wstring dateText2 = L" ";
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::WHITE);
		m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetText(dateText2.c_str());
		
	}

	m_Machine->m_Owner->GetTransform()->SetLocalPosition(pos);
	//OutputDebugString(TEXT("MoveBody\n"));
}

void MoveBodyState::Exit()
{
	m_Machine->m_Owner->GetComponent<BoxCollider>()->SetOffset(Vector2{ 0.f,63.f });
	m_Machine->m_Owner->GetComponent<BoxCollider>()->SetSize(Vector2{ 60,35 });

	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->SetActivate(false);
	wstring dateText2 = L" ";
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::WHITE);
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetText(dateText2.c_str());
	
}
