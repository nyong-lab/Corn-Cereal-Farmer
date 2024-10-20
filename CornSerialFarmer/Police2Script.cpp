#include "Police2Script.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include "StateMachine.h"
#include "PoliceFSM.h"
#include "GameManagerScript.h"

Police2Script::Police2Script()
	: MonoBehaviour(typeid(this).name())
	, m_PoliceStateMachine(nullptr)
	, detailState("MoveFront")
	, police1State("PolicePatrol")
	, timeCount(0)
	, patrolNumber(0)
	, isCatch(false)
	, isRevive(false)
	, xCheck(false)
	, yCheck(false)
	, m_Policemanager(nullptr)
	, m_PoliceTextManager(nullptr)
	, m_ScriptMapKey("")
	, textOut(L"")
	, patrolPath(0)
	, isDead(false)
	, speed(0)
{

}

Police2Script::~Police2Script()
{

}

void Police2Script::Start()
{
	//sponPos = GetTransform()->GetLocalPosition();
	m_PoliceStateMachine = new PoliceFSM(GetGameObject());

	patrolNumber = 1;
	patrolSpot1 = { Vector2(1100, -740), Vector2(1800, -550), Vector2(1800, -50), Vector2(900, -50), Vector2(900, 350) , Vector2(360, 400), Vector2(360, 280), Vector2(-50, 400), Vector2(-50, -250), Vector2(900, -150), Vector2(900, 750), Vector2(1630, 750), Vector2(1630, 300), Vector2(1630, -50), Vector2(2380, -50), Vector2(2380, 300), Vector2(2380, 880), Vector2(3040, 880), Vector2(2380, 880), Vector2(1630, 750), Vector2(1630, 300), Vector2(1630, -50), Vector2(1800, -500), Vector2(1100, -740)};
	patrolSpot2 = { Vector2(1300, 1400), Vector2(1950, 1400), Vector2(1950, 750), Vector2(950, 750), Vector2(900, 400), Vector2(-50, 400), Vector2(-50, 25), Vector2(-50, -250), Vector2(-610, -250), Vector2(-610, 400), Vector2(-340, 400), Vector2(-340, 200), Vector2(-340, 500), Vector2(-630, 400), Vector2(-630, 1350), Vector2(-50, 1350), Vector2(500, 1350), Vector2(360, 300), Vector2(900, 300), Vector2(950, 750), Vector2(1950, 750), Vector2(1950, 1350), Vector2(1300, 1350) };
	
	if (patrolPath == 1)
	{
		gotoSpot = patrolSpot1[0];
		sponPos = Vector2(1100, -1000);
	}
		
	else
	{
		gotoSpot = patrolSpot2[0];
		sponPos = Vector2(1300, 1700);
	}

	speed = 100;
		
}

void Police2Script::Update(float deltaTime)
{
	Vector2 pos = GetTransform()->GetLocalPosition();

	police1State = "PolicePatrol";
	
	//ÁöÁ¤µÈ À§Ä¡·Î ¼øÂû
	//½ÃÃ¼ ¼û±è ½ºÆÌ À§Ä¡·Î ÀÌµ¿
	if (xCheck == true && yCheck == true)
	{
		police1State = "PoliceIdle";
		detailState = "IdleRight";
		timeCount += deltaTime;

		//ÁÂ¿ì·Î º½
		if (timeCount >= 1 && timeCount < 2)
			detailState = "IdleLeft";
		if (timeCount >= 2)
			detailState = "IdleRight";

		if (timeCount >= 3)
		{
			if (patrolPath == 1)
				gotoSpot = patrolSpot1[patrolNumber];
				
			else
				gotoSpot = patrolSpot2[patrolNumber];
				
			xCheck = false;
			yCheck = false;
			timeCount = 0;
			patrolNumber += 1;
		}
	}
	else
	{
		if (gotoSpot.x - 5 <= pos.x && gotoSpot.x + 5 >= pos.x)
			xCheck = true;
		if (gotoSpot.y - 5 <= pos.y && gotoSpot.y + 5 >= pos.y)
			yCheck = true;

		if (xCheck != true)
		{
			if (pos.x > gotoSpot.x)
				detailState = "MoveLeft";
			if (pos.x < gotoSpot.x)
				detailState = "MoveRight";

		}
		if (yCheck != true)
		{
			if (pos.y < gotoSpot.y)
				detailState = "MoveFront";
			if (pos.y > gotoSpot.y)
				detailState = "MoveBack";
		}


	}

	if (isCatch == true)
	{
		police1State = "PoliceCatch";
		m_Policemanager->m_IsGameOver = true;

	}

	///Á×ÀÌ°í »ì¸®°í
	if (m_Policemanager->m_IsDay == true || isDead == true)
	{
		Vector2 pos = GetTransform()->GetLocalPosition();
		pos = Vector2{ -10000, -10000 };
		GetTransform()->SetLocalPosition(pos);
		isRevive = true;
	}

	if (m_Policemanager->m_IsDay == false && isRevive == true && isDead == false && m_Policemanager->isNight == false)
	{
		GetTransform()->SetLocalPosition(sponPos);
		police1State = "PolicePatrol";
		isRevive = false;
		
		patrolNumber = 1;

		if (patrolPath == 1)
		{
			gotoSpot = patrolSpot1[0];
			sponPos = Vector2(1100, -1000);
		}

		else
		{
			gotoSpot = patrolSpot2[0];
			sponPos = Vector2(1300, 1700);
		}
	}

	m_PoliceStateMachine->ChangeDetailState(detailState);
	m_PoliceStateMachine->ChangeState(police1State);
	m_PoliceStateMachine->Update(deltaTime);
}

void Police2Script::FixedUpdate(float deltaTime)
{

}

void Police2Script::Finalize()
{
	m_PoliceStateMachine->Finalize();
	delete m_PoliceStateMachine;
}

void Police2Script::OnCollisionEnter(const Manifold& collision)
{

}

void Police2Script::OnCollisionStay(const Manifold& collision)
{

}

void Police2Script::OnCollisionExit(const Manifold& collision)
{

}
