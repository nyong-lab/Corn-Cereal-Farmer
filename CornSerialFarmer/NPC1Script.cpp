#include "NPC1Script.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>
#include "../GraphicsEngine/GraphicsEngine.h"

#include "StateMachine.h"
#include "NPC1FSM.h"

#include "FarmerScript.h"
#include "GameManagerScript.h"
#include "TextManagerScript.h"


NPC1Script::NPC1Script()
	: MonoBehaviour(typeid(this).name())
	, m_NPC1StateMachine(nullptr)
	, directionCheck(1)
	, NPC1state("NPC1Patrol")
	, detailState("MoveFront")
	, count(0)
	, timeCount(0)
	, deltaTime(0)
	, playerCollisionCheck(false)
	, deadBodyCollisionCheck(false)
	, isTalking(false)
	, isReturn(false)
	, isFind(false)
	, isRevive(false)
	, isPlayerTalking(false)
	, isDead(false)
	, m_NPC1Manager(nullptr)
	, m_NPC1TextManager(nullptr)
	, conversation(0)
	, m_ScriptMapKey("")
	, textOut(L"")
	, xCheck(false)
	, yCheck(false)
	, patrolNumber(0)
	, patrolPath(0)
{

}

NPC1Script::~NPC1Script()
{

}

void NPC1Script::Start()
{

	m_NPC1StateMachine = new NPC1FSM(GetGameObject());

	//필요한 이벤트 메니저 생성
	EventManager::GetInstance()->RegisterClient("NPC1Talk", MakeCallInfo(&NPC1Script::TalkingState));
	EventManager::GetInstance()->RegisterClient("NPC1Check", MakeCallInfo(&NPC1Script::FindBodyState));

	patrolNumber = 1;
	
	//순찰 경로 설정
	patrolSpot1 = { Vector2(1100, -740), Vector2(1800, -450), Vector2(1800, -50), Vector2(2700, -50), Vector2(2700, 690), Vector2(900, -50), Vector2(900, 300), Vector2(-610, 300), Vector2(-610, -150), Vector2(1800, -150), Vector2(1800, -450),Vector2(1100, -740) };
	patrolSpot2 = { Vector2(1300, 1400), Vector2(1950, 1400), Vector2(1950, 690), Vector2(900, 690), Vector2(900, 300), Vector2(-610, 300), Vector2(-610, 1250), Vector2(500, 1250), Vector2(360, 300), Vector2(900, 400), Vector2(900, 690), Vector2(1950, 690), Vector2(1950, 1400), Vector2(1300, 1400), Vector2(1300, 1700) };
	patrolSpot3 = { Vector2(1100, -740), Vector2(1800, -450), Vector2(1800, -250), Vector2(-610, -250), Vector2(-610, 1250), Vector2(1950, 1250), Vector2(1950, 750), Vector2(2700, 750), Vector2(2700, -250), Vector2(1800, -250), Vector2(1800, -450),Vector2(1100, -740) };
	patrolSpot4 = { Vector2(1300, 1400), Vector2(1950, 1400), Vector2(1950, 690), Vector2(2380, 690), Vector2(2380, -50), Vector2(900, -50), Vector2(900, 200), Vector2(-610, 200), Vector2(-610, 800), Vector2(-360, 800), Vector2(-360, 300), Vector2(900, 300), Vector2(900, 680), Vector2(1950, 680), Vector2(1950, 1350), Vector2(1300, 1350), Vector2(1300, 1700)};
	patrolSpot5 = { Vector2(1300, 1400), Vector2(1950, 1400), Vector2(1950, 690), Vector2(1950,-50), Vector2(-50,-50), Vector2(-50,400), Vector2(2600,400), Vector2(2600,690), Vector2(1950,690),Vector2(1950, 1400), Vector2(1300, 1400) };

	if (patrolPath == 1)
	{
		gotoSpot = patrolSpot1[0];
		sponPos = Vector2(1100, -940);
		patrolEnd = patrolSpot1.size();
	}

	else if(patrolPath == 2)
	{
		gotoSpot = patrolSpot2[0];
		sponPos = Vector2(1300, 1600);
		patrolEnd = patrolSpot2.size();
	}

	else if (patrolPath == 3)
	{
		gotoSpot = patrolSpot3[0];
		sponPos = Vector2(1100, -940);
		patrolEnd = patrolSpot3.size();
	}

	else if (patrolPath == 4)
	{
		gotoSpot = patrolSpot4[0];
		sponPos = Vector2(1300, 1600);
		patrolEnd = patrolSpot4.size();
	}

	else if (patrolPath == 5)
	{
		gotoSpot = patrolSpot5[0];
		sponPos = Vector2(1300, 1600);
		patrolEnd = patrolSpot5.size();
	}
}

void NPC1Script::Update(float deltaTime)
{
	Vector2 pos = GetTransform()->GetLocalPosition();
	this->deltaTime = deltaTime;

	if (isFind == true)	//시체 위치로 이동
	{
		NPC1state = "NPC1Find";

		if (xCheck == true && yCheck == true)
		{
			//GameOver
			NPC1state = "NPC1Idle";
			timeCount = 0;
			m_NPC1Manager->m_IsGameOver = true;
		}
		else
		{

			if (bodyPos.x - 1 <= pos.x && bodyPos.x + 1 > pos.x)
				xCheck = true;

			if (bodyPos.y - 1 <= pos.y && bodyPos.y + 1 > pos.y)
				yCheck = true;

			if (xCheck != true)
			{
				if (pos.x > bodyPos.x)
					detailState = "MoveLeft";
				if (pos.x < bodyPos.x)
					detailState = "MoveRight";
			}

			if (yCheck != true)
			{
				if (pos.y < bodyPos.y)
					detailState = "MoveFront";
				if (pos.y > bodyPos.y)
					detailState = "MoveBack";
			}
		}
	}

	else if (isReturn == true)	//스폰지점으로 돌아가기
	{
		NPC1state = "NPC1Return";

		if (xCheck == true && yCheck == true)
		{
			//순찰위치로 이동 후 
			detailState = "IdleFront";
			timeCount = deltaTime + timeCount;

			if (timeCount > 3)
			{
				timeCount = 0;
				isReturn = false;
				directionCheck = 1;
				count = 0;
				xCheck = false;
				yCheck = false;
				NPC1state = "NPC1Patrol";

				if(patrolPath == 1)
					gotoSpot = patrolSpot1[0];
				if (patrolPath == 2)
					gotoSpot = patrolSpot2[0];
				if (patrolPath == 3)
					gotoSpot = patrolSpot3[0];
				if (patrolPath == 4)
					gotoSpot = patrolSpot4[0];
				if (patrolPath == 5)
					gotoSpot = patrolSpot5[0];

				patrolNumber = 0;
			}
		}
		else
		{

			if (sponPos.x - 1 <= pos.x && sponPos.x + 1 > pos.x)
				xCheck = true;

			if (sponPos.y - 1 <= pos.y && sponPos.y + 1 > pos.y)
				yCheck = true;

			if (xCheck != true)
			{
				if (pos.x > sponPos.x)
					detailState = "MoveLeft";
				if (pos.x < sponPos.x)
					detailState = "MoveRight";
			}

			if (yCheck != true)
			{
				if (pos.y < sponPos.y)
					detailState = "MoveFront";
				if (pos.y > sponPos.y)
					detailState = "MoveBack";
			}
		}
	}

	else if (isTalking == true)	//플레이어와 대화
	{
		EventManager::GetInstance()->SendEvent("NPC1Talk", nullptr);
	}

	else if (playerCollisionCheck == true)	//플레이어랑 부딪힘
	{
		if (conversation == 0)
		{
			NPC1state = "NPC1Idle";
			if (Input::GetKey(KEY::SPACE))
			{
				isTalking = true;
				timeCount = 0;
				conversation = 1;
				int num = rand() % 3;
				textOut = m_NPC1TextManager->ScriptMap[m_ScriptMapKey][num];
			}
		}
		if (directionCheck == 1)
			detailState = "IdleRight";
		if (directionCheck == 2)
			detailState = "IdleFront";
		if (directionCheck == 3)
			detailState = "IdleLeft";
		if (directionCheck == 4)
			detailState = "IdleBack";
	}

	else if (deadBodyCollisionCheck == true)	//시체 발견
	{
		NPC1state = "NPC1Check";
		EventManager::GetInstance()->SendEvent("NPC1Check", nullptr);

		timeCount = deltaTime + timeCount;

		if (directionCheck == 1)
			detailState = "IdleRight";
		if (directionCheck == 2)
			detailState = "IdleFront";
		if (directionCheck == 3)
			detailState = "IdleLeft";
		if (directionCheck == 4)
			detailState = "IdleBack";
	}

	else
	{
		NPC1state = "NPC1Patrol";

		//지정된 위치로 순찰
		if (xCheck == true && yCheck == true)
		{
			if (patrolPath == 1)
				gotoSpot = patrolSpot1[patrolNumber];

			else if(patrolPath == 2)
				gotoSpot = patrolSpot2[patrolNumber];

			else if (patrolPath == 3)
				gotoSpot = patrolSpot3[patrolNumber];

			else if (patrolPath == 4)
				gotoSpot = patrolSpot4[patrolNumber];

			else if (patrolPath == 5)
				gotoSpot = patrolSpot5[patrolNumber];


			xCheck = false;
			yCheck = false;
			patrolNumber += 1;

			if (patrolNumber == patrolEnd)
				patrolNumber = 0;
		}
		else
		{
			if (gotoSpot.x - 5 <= pos.x && gotoSpot.x + 5 >= pos.x)
				xCheck = true;
			if (gotoSpot.y - 5 <= pos.y && gotoSpot.y + 5 >= pos.y)
				yCheck = true;

			if (yCheck != true)
			{
				if (pos.y < gotoSpot.y)
					detailState = "MoveFront";
				if (pos.y > gotoSpot.y)
					detailState = "MoveBack";
			}

			if (xCheck != true)
			{
				if (pos.x > gotoSpot.x)
					detailState = "MoveLeft";
				if (pos.x < gotoSpot.x)
					detailState = "MoveRight";

			}
			


		}

	}

	if (m_NPC1Manager->m_IsDay == false || isDead == true)
	{
		Vector2 pos = GetTransform()->GetLocalPosition();
		pos = Vector2{ -10000, -10000 };
		GetTransform()->SetLocalPosition(pos);
		isRevive = true;
		isPlayerTalking = false;
		isTalking = false;
		playerCollisionCheck = false;
		conversation = 0;
	}
	if (m_NPC1Manager->m_IsDay == true && isRevive == true && isDead == false && m_NPC1Manager->isMorning == false)
	{
		GetTransform()->SetLocalPosition(sponPos);
		isRevive = false;

		//필요한 초기화
		NPC1state = "NPC1Patrol";
		detailState = "MoveFront";
		
		count = 0;
		timeCount = 0;
		playerCollisionCheck = false;
		deadBodyCollisionCheck = false;
		isTalking = false;
		isReturn = false;
		isFind = false;
		isPlayerTalking = false;
		conversation = 0;
		xCheck = false;
		yCheck = false;

		if (patrolPath == 1)
			gotoSpot = patrolSpot1[0];
		if (patrolPath == 2)
			gotoSpot = patrolSpot2[0];
		if (patrolPath == 3)
			gotoSpot = patrolSpot3[0];
		if (patrolPath == 4)
			gotoSpot = patrolSpot4[0];
		if (patrolPath == 5)
			gotoSpot = patrolSpot5[0];

		patrolNumber = 0;
		
	}

	m_NPC1StateMachine->ChangeDetailState(detailState);
	m_NPC1StateMachine->ChangeState(NPC1state);
	m_NPC1StateMachine->Update(deltaTime);
}

void NPC1Script::FixedUpdate(float deltaTime)
{

}

void NPC1Script::Finalize()
{
	m_NPC1StateMachine->Finalize();
	delete m_NPC1StateMachine;
}

void NPC1Script::OnCollisionEnter(const Manifold& collision)
{

	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
		playerCollisionCheck = true;

}

void NPC1Script::OnCollisionStay(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		if (isTalking == true)
		{
			dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isNPCTalking = true;
			
			if (isPlayerTalking == true)
			{
				dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isPlayerTalkingState = true;
			}
			else
			{
				dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isPlayerTalkingState = false;

			}
		}
		else
		{
			dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isNPCTalking = false;
		}


	}

}

void NPC1Script::OnCollisionExit(const Manifold& collision)
{
	if(playerCollisionCheck == true)
		playerCollisionCheck = false;
	
}

void NPC1Script::TalkingState(std::any)
{

	if (conversation == 1)
	{
		NPC1state = "NPC1Talk";
		timeCount += deltaTime;
		if (Input::GetKey(KEY::SPACE) && timeCount > 0.2)
		{
			NPC1state = "NPC1Talk";
			conversation = 2;
			timeCount = 0;

			textOut = L" ";
			
		}
	}
	else if (conversation == 2)
	{
		NPC1state = "NPC1Idle";
		isPlayerTalking = true;
		timeCount += deltaTime;
		
		if (Input::GetKey(KEY::SPACE) && timeCount > 0.2)
		{
			conversation = 3;
			timeCount = 0;

			int num2 = (rand() % 3) + 3;
			textOut = m_NPC1TextManager->ScriptMap[m_ScriptMapKey][num2];
			//OutputDebugString(TEXT("\n\nPreTime: ")); OutputDebugString(textOut.c_str()); OutputDebugString(TEXT("\n"));
		}

	}
	else if (conversation == 3)
	{
		NPC1state = "NPC1Talk";
		isPlayerTalking = false;
		timeCount += deltaTime;

		if (Input::GetKey(KEY::SPACE) && timeCount > 0.2)
		{
			textOut = L" ";
			isTalking = false;
			timeCount = 0;
			conversation = 0;
			isReturn = true;
			xCheck = false;
			yCheck = false;
		}

	}

}

void NPC1Script::FindBodyState(std::any)
{

	if (timeCount > 7)
	{
		isFind = true;
		deadBodyCollisionCheck = false;
	}

}
