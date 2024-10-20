#include "PoliceScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include "StateMachine.h"
#include "PoliceFSM.h"
#include "GameManagerScript.h"
#include "GameOverWindow.h"
#include "PopupWindowBackground.h"
#include "GameplayStatics.h"

PoliceScript::PoliceScript()
	: MonoBehaviour(typeid(this).name())
	, m_PoliceStateMachine(nullptr)
	, detailState("MoveFront")
	, police1State("PolicePatrol")
	, timeCount(0)
	, randomPatrolNumber(0)
	, isCatch(false)
	, isRevive(false)
	, xCheck(false)
	, yCheck(false)
	, m_Policemanager(nullptr)
	, m_PoliceTextManager(nullptr)
	, m_ScriptMapKey("")
	, textOut(L"")
	, isBuildingCollision(false)
	, backCount(0)
	, randomBackNumber(0)
	, isDead(true)
	, speed(0)
{

}

PoliceScript::~PoliceScript()
{

}

void PoliceScript::Start()
{
	sponPos = GetTransform()->GetLocalPosition();
	m_PoliceStateMachine = new PoliceFSM(GetGameObject());

	//ÀÓ½Ã·Î ½ÃÃ¼ ¼û±è Àå¼Ò¸¦ Á¤ÇØµÐ´Ù
	patrolSpot1 = Vector2{  360,  280 };	//Áý
	patrolSpot2 = Vector2{ -340,  280 };	//Ã¢°í A
	patrolSpot3 = Vector2{  -50, 1350 };	//Ã¢°í B
	patrolSpot4 = Vector2{ 1630, 1350 };	//Ã¢°í C
	patrolSpot  = Vector2{ 3040,  880 };	//Ã¢°í D

	//ÇÊ¿äÇÑ ÀÌº¥Æ® ¸Þ´ÏÀú »ý¼º

	speed = 300;
}

void PoliceScript::Update(float deltaTime)
{
	Vector2 pos = GetTransform()->GetLocalPosition();

	police1State = "PoliceTrace";

	//½ÃÃ¼ ¼û±è ½ºÆÌ À§Ä¡·Î ÀÌµ¿
	if (xCheck == true && yCheck == true)
	{
		police1State = "PoliceIdle";
		detailState = "IdleRight";
		timeCount += deltaTime;

		//ÁÂ¿ì·Î º½
		if(timeCount >= 1 && timeCount < 2)
			detailState = "IdleLeft";
		if (timeCount >= 2)
			detailState = "IdleRight";
		
		if (timeCount >= 3)
		{
			randomPatrolNumber = rand() % 4;
			
			if (randomPatrolNumber == 0)
				patrolSpot = patrolSpot1;
			else if (randomPatrolNumber == 1)
				patrolSpot = patrolSpot2;
			else if (randomPatrolNumber == 2)
				patrolSpot = patrolSpot3;
			else if (randomPatrolNumber == 3)
				patrolSpot = patrolSpot4;

			xCheck = false;
			yCheck = false;
			timeCount = 0;
		}
	}
	else
	{
		//°Ç¹°°ú ºÎµúÈû (1ÃÊ ¸ØÃã ÈÄ ÈÄÁø)
		if (isBuildingCollision == true)
		{
			if (backCount == 0)
			{
				randomBackNumber = rand() % 4;

				if (randomBackNumber == 0 && detailState.compare("MoveFront") != 0)
					detailState = "MoveFront";
				else if (randomBackNumber == 1 && detailState.compare("MoveRight") != 0)
					detailState = "MoveRight";
				else if (randomBackNumber == 2 && detailState.compare("MoveLeft") != 0)
					detailState = "MoveLeft";
				else if (randomBackNumber == 3 && detailState.compare("MoveBack") != 0)
					detailState = "MoveBack";
				else
					backCount--;
			}
	
			backCount++;

			if (backCount > 80)
			{
				isBuildingCollision = false;
				backCount = 0;

			}

		}
		else
		{
			if (patrolSpot.x - 5 <= pos.x && patrolSpot.x + 5 >= pos.x)
				xCheck = true;
			if (patrolSpot.y - 5 <= pos.y && patrolSpot.y + 5 >= pos.y)
				yCheck = true;

			if (xCheck != true)
			{
				if (pos.x > patrolSpot.x)
					detailState = "MoveLeft";
				if (pos.x < patrolSpot.x)
					detailState = "MoveRight";

			}
			if (yCheck != true)
			{
				if (pos.y < patrolSpot.y)
					detailState = "MoveFront";
				if (pos.y > patrolSpot.y)
					detailState = "MoveBack";
			}
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
		police1State = "PoliceTrace";
		isRevive = false;
	}


	m_PoliceStateMachine->ChangeDetailState(detailState);
	m_PoliceStateMachine->ChangeState(police1State);
	m_PoliceStateMachine->Update(deltaTime);
}

void PoliceScript::FixedUpdate(float deltaTime)
{

}

void PoliceScript::Finalize()
{
	m_PoliceStateMachine->Finalize();
	delete m_PoliceStateMachine;
}

void PoliceScript::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING || collision.otherObject->GetObjectType() == OBJECT_TYPE::TREE)
	{
		isBuildingCollision = true;
	}
}

void PoliceScript::OnCollisionStay(const Manifold& collision)
{

}

void PoliceScript::OnCollisionExit(const Manifold& collision)
{

}


