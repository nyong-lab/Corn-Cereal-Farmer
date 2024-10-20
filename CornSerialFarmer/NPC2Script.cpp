#include "NPC2Script.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>
#include "../GraphicsEngine/GraphicsEngine.h"

#include "StateMachine.h"
#include "NPC2FSM.h"

#include "FarmerScript.h"
#include "GameManagerScript.h"
#include "TextManagerScript.h"

NPC2Script::NPC2Script()
	: MonoBehaviour(typeid(this).name())
	, m_NPC2StateMachine(nullptr)
	, detailState("MoveFront")
	, NPC2State("NPC2Trace")
	, count(0)
	, backCount(0)
	, randomBackNumber(0)
	, timeCount(0)
	, deltaTime(0)
	, conversation(0)
	, m_ScriptMapKey("")
	, textOut(L"")
	, directionCheck(1)
	, playerCollisionCheck(false)
	, deadBodyCollisionCheck(false)
	, isBuildingCollisionCheck(false)
	, isTalking(false)
	, isReturn(false)
	, isFind(false)
	, isPlayerTalking(false)
	, isPositionStart(false)
	, isRevive(false)
	, isDead(false)
	, m_NPC2Manager(nullptr)
	, xCheck(false)
	, yCheck(false)
	, bodyPos(Vector2{ -150, 1100 })
	, startPointCheck(0)
	, startPoint(0)
{

}

NPC2Script::~NPC2Script()
{

}

void NPC2Script::Start()
{

	sponPos = GetTransform()->GetLocalPosition();
	
	//bodyPos = (Vector2{ -780, 988 });
	bodyPos = (Vector2{ -150, 1100 });
	// 	Vector2 scale{ 1,1 };
	// 	GetTransform()->SetLocalScale(scale);

	m_NPC2StateMachine = new NPC2FSM(GetGameObject());

	//필요한 이벤트 메니저 생성
	EventManager::GetInstance()->RegisterClient("NPC2Talk", MakeCallInfo(&NPC2Script::TalkingState));
	EventManager::GetInstance()->RegisterClient("NPC2Check", MakeCallInfo(&NPC2Script::FindBodyState));

	startPoint1 = { Vector2(1100, -740), Vector2(1800, -550), Vector2(1800, -50) };
	startPoint2 = { Vector2(1300, 1400), Vector2(1950, 1400), Vector2(1950, 690) };

	if (startPointCheck == 1)
		gotoSpot = startPoint1[0];
		
	else
		gotoSpot = startPoint2[0];
		
	//startPoint = 0;
}

void NPC2Script::Update(float deltaTime)
{
	Vector2 pos = GetTransform()->GetLocalPosition();
	bodyPos = m_NPC2Manager->m_DeadBodySpot;

	this->deltaTime = deltaTime;

	if (isFind == true)	//시체로 돌격
	{
		NPC2State = "NPC2Find";

		if (xCheck == true && yCheck == true)
		{
			//GameOver
			NPC2State = "NPC2Idle";
			timeCount = 0;
			m_NPC2Manager->m_IsGameOver = true;
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
				{
					directionCheck = 3;
					detailState = "MoveLeft";
				}

				if (pos.x < bodyPos.x)
				{
					directionCheck = 1;
					detailState = "MoveRight";
				}

			}

			if (yCheck != true)
			{
				if (pos.y < bodyPos.y)
				{
					directionCheck = 2;
					detailState = "MoveFront";
				}

				if (pos.y > bodyPos.y)
				{
					directionCheck = 4;
					detailState = "MoveBack";
				}

			}
		}
	}
	else if (isReturn == true)		//스폰지점으로 돌아가기
	{
		NPC2State = "NPC2Return";

		if (isBuildingCollisionCheck == true)
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

			if (backCount > 200)
			{
				isBuildingCollisionCheck = false;
				backCount = 0;

			}

		}
		else
		{
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
					xCheck = false;
					yCheck = false;
					NPC2State = "NPC2Trace";
				}

			}
			else
			{
				if (sponPos.x - 2 <= pos.x && sponPos.x + 2 > pos.x)
					xCheck = true;

				if (sponPos.y - 2 <= pos.y && sponPos.y + 2 > pos.y)
					yCheck = true;

				if (xCheck != true)
				{
					if (pos.x > sponPos.x)
					{
						directionCheck = 3;
						detailState = "MoveLeft";
					}

					if (pos.x < sponPos.x)
					{
						directionCheck = 1;
						detailState = "MoveRight";
					}

				}

				if (yCheck != true)
				{
					if (pos.y < sponPos.y)
					{
						directionCheck = 2;
						detailState = "MoveFront";
					}

					if (pos.y > sponPos.y)
					{
						directionCheck = 4;
						detailState = "MoveBack";
					}

				}
			}
		}
	}

	else if (isTalking == true)
	{
		EventManager::GetInstance()->SendEvent("NPC2Talk", nullptr);
	}

	else if (playerCollisionCheck == true)	//플레이어랑 부딪힘
	{
		if (conversation == 0)
		{
			NPC2State = "NPC2Idle";
			if (Input::GetKey(KEY::SPACE))
			{
				isTalking = true;
				timeCount = 0;
				conversation = 1;
				int num = rand() % 3;
				textOut = m_NPC2TextManager->ScriptMap[m_ScriptMapKey][num];
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
	
	else if (deadBodyCollisionCheck == true)		// 시체 발견
	{
		NPC2State = "NPC2Check";
		EventManager::GetInstance()->SendEvent("NPC2Check", nullptr);

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

	//추적
	else 	{
		NPC2State = "NPC2Trace";

		if (isBuildingCollisionCheck == true)
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

			if (backCount > 100)
			{
				isBuildingCollisionCheck = false;
				backCount = 0;

			}

		}

		else
		{
			if (bodyPos.x - 2 <= pos.x && bodyPos.x + 2 > pos.x)
				xCheck = true;

			if (bodyPos.y - 2 <= pos.y && bodyPos.y + 2 > pos.y)
				yCheck = true;

			if (xCheck != true)
			{
				if (pos.x > bodyPos.x)
				{
					directionCheck = 3;
					detailState = "MoveLeft";
				}

				if (pos.x < bodyPos.x)
				{
					directionCheck = 1;
					detailState = "MoveRight";
				}

			}

			if (yCheck != true)
			{
				if (pos.y < bodyPos.y)
				{
					directionCheck = 2;
					detailState = "MoveFront";
				}

				if (pos.y > bodyPos.y)
				{
					directionCheck = 4;
					detailState = "MoveBack";
				}

			}
		}
		
	}

	//시작 위치로 이동
	if (isPositionStart == false)
	{
		NPC2State = "NPC2Trace";

		if (xCheck == true && yCheck == true)
		{	
			
			if (startPoint == 3)
			{
				NPC2State = "NPC2Idle";
				detailState = "IdleRight";
				timeCount += deltaTime;

				//좌우로 봄
				if (timeCount >= 1 && timeCount < 2)
					detailState = "IdleLeft";
				if (timeCount >= 2)
					detailState = "IdleRight";

				if (timeCount >= 3)
				{
					xCheck = false;
					yCheck = false;
					timeCount = 0;
					isPositionStart = true;
					
				}
			}
			
			else
			{
				if (startPointCheck == 1)
					gotoSpot = startPoint1[startPoint];

				else
					gotoSpot = startPoint2[startPoint];

				xCheck = false;
				yCheck = false;
				startPoint++;
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
	}

	if (m_NPC2Manager->m_IsDay == false || isDead == true)
	{
		Vector2 pos = GetTransform()->GetLocalPosition();
		pos = Vector2{ -10000, -10000 };
		GetTransform()->SetLocalPosition(pos);
		isRevive = true;
	}  
	if (m_NPC2Manager->m_IsDay == true && isRevive == true && isDead == false && m_NPC2Manager->isMorning == false)
	{
		GetTransform()->SetLocalPosition(sponPos);
		isRevive = false;

		//필요한 초기화
		NPC2State = "NPC2Trace";
		detailState = "MoveFront";
		
		count = 0;
		timeCount = 0;
		playerCollisionCheck = false;
		deadBodyCollisionCheck = false;
		isTalking = false;
		isReturn = false;
		isFind = false;
		isPositionStart = false;
		isPlayerTalking = false;
		conversation = 0;
		xCheck = false;
		yCheck = false;

		if (startPointCheck == 1)
			gotoSpot = startPoint1[0];

		else
			gotoSpot = startPoint2[0];

		startPoint = 0;
	}
	
	m_NPC2StateMachine->ChangeDetailState(detailState);
	m_NPC2StateMachine->ChangeState(NPC2State);
	m_NPC2StateMachine->Update(deltaTime);
}

void NPC2Script::FixedUpdate(float deltaTime)
{

}

void NPC2Script::Finalize()
{
	m_NPC2StateMachine->Finalize();
	delete m_NPC2StateMachine;
}

void NPC2Script::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
		playerCollisionCheck = true;

	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING || collision.otherObject->GetObjectType() == OBJECT_TYPE::TREE)
		isBuildingCollisionCheck = true;

}

void NPC2Script::OnCollisionStay(const Manifold& collision)
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

void NPC2Script::OnCollisionExit(const Manifold& collision)
{
	playerCollisionCheck = false;

}

void NPC2Script::TalkingState(std::any)
{
	if (conversation == 1)
	{
		NPC2State = "NPC2Talk";
		timeCount += deltaTime;
		if (Input::GetKey(KEY::SPACE) && timeCount > 0.2)
		{
			NPC2State = "NPC2Talk";
			conversation = 2;
			timeCount = 0;

			textOut = L" ";
		}
	}
	else if (conversation == 2)
	{
		NPC2State = "NPC2Idle";
		isPlayerTalking = true;
		timeCount += deltaTime;

		if (Input::GetKey(KEY::SPACE) && timeCount > 0.2)
		{
			conversation = 3;
			timeCount = 0;

			int num2 = (rand() % 3) + 3;
			textOut = m_NPC2TextManager->ScriptMap[m_ScriptMapKey][num2];
			//OutputDebugString(TEXT("\n\nPreTime: ")); OutputDebugString(textOut.c_str()); OutputDebugString(TEXT("\n"));
		}

	}
	else if (conversation == 3)
	{
		NPC2State = "NPC2Talk";
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

void NPC2Script::FindBodyState(std::any)
{
	if (timeCount > 7)
	{
		isFind = true;
		deadBodyCollisionCheck = false;
	}
}
