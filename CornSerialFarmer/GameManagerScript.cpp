#include "GameManagerScript.h"

#include "ResourceManager.h"
#include "EventManager.h"

#include "Image.h"

#include "GameObject.h"
#include "Scene.h"

#include "ImageRenderer.h"
#include "TextRenderer.h"

#include "TimeBar.h"
#include "ItemSlot.h"
#include "PauseButton.h"
#include "GameOverWindow.h"

#include "QuestManagerScript.h"
#include "ObjectDataScript.h"
#include "ItemManagerScript.h"
#include "EffectManagerScript.h"
#include "FarmScript.h"
#include "WildBoarScript.h"
#include "Transform.h"

#include "GameplayStatics.h"
#include "FarmerScript.h"
#include "NPC1Script.h"
#include "NPC2Script.h"
#include "PoliceScript.h"
#include "Police2Script.h"
#include "KillWindow.h"
#include "QuestList.h"
#include "BlackScreenScript.h"
#include "BlackScreen.h"

#include "Animator.h"

// Sound
#include "SoundManager.h"
#include "Sound.h"

#include <random>

using namespace std;

GameManagerScript::GameManagerScript()
	: MonoBehaviour(typeid(this).name())
	, m_DayCount(1), m_IsDay(true), m_TimePassed(0.f), m_TimeBar(nullptr)
	, m_QuestManager(nullptr), m_ItemManager(nullptr), m_EffectManager(nullptr)
	, m_IsCreateQuest(true), m_IsCreateEmergencyQuest(false), m_EmergencyQuestTime(0)
	, m_IsCreateNightQuest(false), m_NightQuestTime(0)
	, m_PatrolLevelTemporary(false), m_PatrolLevel(1)
	, m_CatBowlAnimator(nullptr)
	, m_CurrentTimeZone(DAY_NIGHT::MORNING_EARLY), m_DayPassed(0.f), m_EffectTimePassed(0.f)
	, m_ColorTint(0.f), m_Temperature(0.f), m_Brightness(0.f)
	, m_ColorTintValue(0.f), m_TemperatureValue(0.f), m_BrightnessValue(0.f)
	, m_DayBGMVolume(0.f), m_NightBGMVolume(0.f)
	, m_IsGameOver(false), m_ShowGameOverWindow(false)
	, isNight(false), timeCount(0), isMorning(false)
	, m_NPC1Script(nullptr)
	, m_NPC2Script(nullptr)
	, m_NPC3Script(nullptr)
	, m_NPC4Script(nullptr)
	, m_NPC5Script(nullptr)
	, m_NPC6Script(nullptr)
	, m_Police1Script(nullptr)
	, m_Police2Script(nullptr)
	, m_Police3Script(nullptr)
	, m_Police4Script(nullptr)
	, m_BlackScreenScript(nullptr)
{
	DAY_TOTAL_TIME = DAYTIME_LENGTH + NIGHTTIME_LENGTH;

	// 이펙트 값 조절
	m_TemperatureValue = 0.8f / (DAYTIME_LENGTH / 2);
	m_ColorTintValue = 0.5f / (DAYTIME_LENGTH / 2);
	m_BrightnessValue = 0.06f / (DAYTIME_LENGTH / 2);

	// 사운드 볼륨
	m_DayBGMVolume = 0.4f;
	m_NightBGMVolume = 0.3f;
}

GameManagerScript::~GameManagerScript()
{

}

void GameManagerScript::Start()
{
	// BGM
	SoundManager::GetInstance()->StopSoundBGM();
	SoundManager::GetInstance()->PlaySoundBGM(
		ResourceManager::GetInstance()->LoadResource<Sound>(L"DayBGM", L"/Sound/BGM/DAY/Joy Ride.mp3")->GetSound());
	SoundManager::GetInstance()->SetBGMVolume(m_DayBGMVolume);

	//필요한 이벤트 메니저 생성

	// 경찰
	EventManager::GetInstance()->RegisterClient("PatrolLevelUp", MakeCallInfo(&GameManagerScript::PatrolLevelUp));
	EventManager::GetInstance()->RegisterClient("PatrolLevelDown", MakeCallInfo(&GameManagerScript::PatrolLevelDown));
	EventManager::GetInstance()->RegisterClient("PatrolLevelTemporary", MakeCallInfo(&GameManagerScript::PatrolLevelTemporary));

	// 고양이
	EventManager::GetInstance()->RegisterClient("CatBowlEmpty", MakeCallInfo(&GameManagerScript::CatBowlEmpty));
	EventManager::GetInstance()->RegisterClient("CatBowlFull", MakeCallInfo(&GameManagerScript::CatBowlFull));

	//알람설정
	EventManager::GetInstance()->RegisterClient("AlarmAlert", MakeCallInfo(&GameManagerScript::alarmAlert));

	//시체 위치 초기화
	m_DeadBodySpot = Vector2(-150, 1110);
	killNPCList.push_back(1);
	killNPCList.push_back(2);
	killNPCList.push_back(5);
	killNPCList.push_back(6);

	EventManager::GetInstance()->RegisterClient("CompleteKill", MakeCallInfo(&GameManagerScript::GetKillNpcIndex));

}
void GameManagerScript::Update(float deltaTime)
{
	// 게임오버 체크
	CheckGameOver();

	CheckDayProgress(deltaTime);
	TimeEffectManagement(deltaTime);

	if (m_QuestManager->m_FailWildBoar)
	{
		m_QuestManager->m_FailWildBoar = false;
		DestoryFarm();
	}
}

void GameManagerScript::Finalize()
{

}

/// <summary>
/// 순찰 레벨 증가
/// 일시적인지 아닌지는 퀘스트매니저쪽에서 게임매니저에 보내준다.
/// 낮 퀘스트 실패 : 그 날만 순찰 레벨 증가
/// 밤 퀘스트 실패 : 영구적으로 순찰 레벨 증가
/// max 순찰 레벨은 6
/// </summary>
void GameManagerScript::PatrolLevelUp(std::any)
{
	if (GetGameObject()->GetScene()->GetName() == "MainScene")
	{
		if (m_PatrolLevel < 6)
		{
			m_PatrolLevel++;
		}

		else
		{
			assert(nullptr && "순찰 레벨 수치 오류");
		}
	}

}

/// <summary>
/// 순찰 레벨 감소
/// </summary>
void GameManagerScript::PatrolLevelDown(std::any)
{
	if (GetGameObject()->GetScene()->GetName() == "MainScene")
	{
		if (m_PatrolLevel > 1)
		{
			--m_PatrolLevel;
		}

		else
		{
			assert(nullptr && "순찰 레벨 수치 오류");
		}
	}
}

/// <summary>
/// 순찰 레벨 증가가 일시적이면 게임 매니저에 전달하고 
/// 게임 매니저에서는 시간의 흐름에 따라서 순찰 레벨을 다시 감소시켜준다.
/// </summary>
/// <param name=""></param>
void GameManagerScript::PatrolLevelTemporary(std::any)
{
	if (GetGameObject()->GetScene()->GetName() == "MainScene")
	{
		m_PatrolLevelTemporary = true;
	}
}

/// <summary>
/// 순찰 레벨에 따른 경찰 스피드 할당 함수
/// </summary>
void GameManagerScript::PolicePatrolLevelCheck()
{
	OutputDebugString(TEXT("Patrol Level")); OutputDebugString(to_wstring(m_PatrolLevel).c_str()); OutputDebugString(TEXT("\n"));

	// 순찰 레벨을 체크 후
	switch (m_PatrolLevel)
	{
		case 1:
			m_Police1Script->speed = 200;
			m_Police2Script->speed = 200;
			m_Police3Script->speed = 100;
			m_Police4Script->speed = 100;
			break;
		case 2:
			m_Police1Script->speed = 300;
			m_Police2Script->speed = 300;
			m_Police3Script->speed = 200;
			m_Police4Script->speed = 200;
			break;
		case 3:
			m_Police1Script->speed = 400;
			m_Police2Script->speed = 400;
			m_Police3Script->speed = 300;
			m_Police4Script->speed = 300;
			break;
		case 4:
			m_Police1Script->speed = 450;
			m_Police2Script->speed = 450;
			m_Police3Script->speed = 400;
			m_Police4Script->speed = 400;
			break;
		case 5:
			m_Police1Script->speed = 550;
			m_Police2Script->speed = 550;
			m_Police3Script->speed = 500;
			m_Police4Script->speed = 500;
			break;
		case 6:
			m_Police1Script->speed = 1000;
			m_Police2Script->speed = 1000;
			m_Police3Script->speed = 1000;
			m_Police4Script->speed = 1000;
			break;
	}
	// 순찰 레벨에 따른 speed를 할당시켜준다
}

/// <summary>
/// 알람이 필요한 경우, 필요한 알람을 불러준다.
/// </summary>
void GameManagerScript::alarmAlert(std::any)
{

}

/// <summary>
/// 고양이 밥 애니메이션 상태 변경 (밥 없음)
/// </summary>
void GameManagerScript::CatBowlEmpty(std::any)
{
	m_CatBowlAnimator->Play(L"catBowlEmpty", true);
}

/// <summary>
/// 고양이 밥 애니메이션 상태 변경 (밥 있음)
/// </summary>
void GameManagerScript::CatBowlFull(std::any)
{
	m_CatBowlAnimator->Play(L"catBowlFull", true);
}

void GameManagerScript::CheckCornQuest()
{
	int& cornQuestCount = m_QuestManager->m_CornQuestCount;
	if (m_QuestManager->m_IsCornQuestStepUp)
	{
		++(cornQuestCount);

		if (cornQuestCount > 5)
		{
			cornQuestCount = 1;
		}
	}

	if (cornQuestCount < 1 && cornQuestCount > 5)
	{
		assert(nullptr && "옥수수 단계 수치 오류");
	}
}

void GameManagerScript::CheckDayProgress(float deltaTime)
{
	if (m_DayCount > DAY_MAX)
	{
		CheckEndingQuarter();
	}

	// TimeBar 길이 가져오기
	Vector2 timeBarSize = m_TimeBar->GetTimeBarImage()->GetSize();
	const float TIMEBAR_LENGTH = timeBarSize.x;

	// TimeBar 길이 조절
	float timePassedRatio = static_cast<float>(m_TimePassed / (m_IsDay ? DAYTIME_LENGTH : NIGHTTIME_LENGTH));
	float timeBarLength = timePassedRatio * TIMEBAR_LENGTH;
	m_TimeBar->GetTimeBarImage()->SetSliceSize(Vector2(timeBarLength, timeBarSize.y));
	D2D1_RECT_F additionalOffset = {};
	additionalOffset.right = -(TIMEBAR_LENGTH - timeBarLength);
	m_TimeBar->GetTimeBarImage()->SetAdditionalOffset(additionalOffset);

	// 낮
	if (m_IsDay && isNight == false && isMorning == false)
	{
		// 시간이 흘러요
		m_TimePassed += deltaTime;

		if (m_QuestManager->m_ApplyFarm != true)
		{
			m_QuestManager->m_ApplyFarm = true;
			m_QuestManager->m_FailWildBoar = true;
		}

		// 퀘스트 생성
		if (m_IsCreateQuest)
		{
			m_QuestManager->m_WildBoar->GetObjectChild("wildBoarExclamationMark")->SetActivate(false);
			// 고양이 활성화
			if (m_QuestManager->m_SaveCat)
			{
				m_QuestManager->m_CatObject->SetActivate(true);
				/*	dynamic_cast<FarmerScript*>(m_QuestManager->m_Player->GetComponent<MonoBehaviour>())->speed = 500;
					dynamic_cast<FarmerScript*>(m_QuestManager->m_Player->GetComponent<MonoBehaviour>())->diagonalSpeed = 300;*/
			}

			// 비료 상태 초기화 
			InitializeFarmFertilizer();
			// 멧돼지 초기화
			InitializeWildBoar();
			// 매일 하루가 시작할 때 밭 상태를 체크해서 옥수수 성장을 고려한다.
			CheckFarmState();
			// 옥수수 퀘스트 단계를 체크한다.
			CheckCornQuest();
			// 긴급 퀘스트 생성여부 체크 및 발생 시간을 얻어낸다
			CheckEmergencyQuest();
			// 퀘스트 생성
			m_QuestManager->CreateQuest(m_DayCount, m_IsDay);
			// 낮밤이 바뀌기 전까진 재생성 불가능
			m_IsCreateQuest = false;
			// 아이템 모두 삭제
			//m_ItemManager->DeleteAllItem();
			m_QuestManager->DeleteAllItem();
		}

		// 긴급 퀘스트 생성 가능하다면
		if (m_IsCreateEmergencyQuest)
		{
			// 현재 시간이 긴급 퀘스트 생성 시간을 넘는다면 
			if (m_TimePassed > m_EmergencyQuestTime)
			{
				// 긴급 퀘스트 생성
				m_QuestManager->CreateEmergencyRandomQuest();
				m_IsCreateEmergencyQuest = false;
			}
		}

		// 		/// 킬 테스트
		// 		if (m_TimePassed > DAYTIME_LENGTH - 20.f)
		// 		{
		// 			ShowKillWindow(3, 5, 1);
		// 		}
				//저녁으로 넘어가기 위한 상태 변환
		if (m_TimePassed > DAYTIME_LENGTH)
		{
			//fade in out 을 위한 변수
			isNight = true;
			isMorning = false;
			m_RunOnce = false;

			// 퀘스트 생성 가능
			m_IsCreateQuest = true;

			m_TimePassed = 0.f;

			// 텍스트 및 이미지 변경
			wstring dateText = to_wstring(m_DayCount) + L"일차 밤";
			m_TimeBar->GetDateText()->SetText(dateText.c_str());
			m_TimeBar->GetTimeBarImage()->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarImageMoon", L"/UI/timebarMoon.png")->GetImage());
			m_TimeBar->GetTimeIconImage()->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarIconMoon", L"/UI/timeiconMoon.png")->GetImage());
			m_TimeBar->GetTimeIconImage()->SetPositionOffset(Vector2(12.f, 0.f));

			// BGM 재생
			SoundManager::GetInstance()->StopSoundBGM();
			SoundManager::GetInstance()->PlaySoundBGM(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"NightBGM", L"/Sound/BGM/NIGHT/Evil4 - Witch's Lair.mp3")->GetSound());
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"NightSFX", L"/Sound/SFX/DayNight/Night_Owl.mp3")->GetSound());
			SoundManager::GetInstance()->SetBGMVolume(m_NightBGMVolume);

			// 낮에 활성화된 퀘스트를 모두 완료했는지 체크
			m_QuestManager->CheckCompleteAllActiveQuests();

		}

	}
	//사이에 화면 전환
	else if (isMorning == true)
	{
		++(m_QuestManager->m_ActiveQuests.find(999)->second.questStep);

		if (m_QuestManager->m_ActiveQuests.find(999)->second.questStep == m_QuestManager->m_ActiveQuests.find(999)->second.maxQuestStep)
		{
			m_QuestManager->m_ActiveQuests.find(999)->second.isComplete = true;

			m_QuestManager->m_QuestUiList->m_CheckBoxImage[m_QuestManager->m_ActiveQuests.find(999)->second.uiOrder]->SetImage
			(
				ResourceManager::GetInstance()->LoadResource<Image>(L"Check", L"/UI/check.png")->GetImage()
			);
		}
		else
		{
			m_QuestManager->m_ActiveQuests.find(999)->second.objectId = m_QuestManager->m_QuestList[999 + 1].objectId;
		}

		EventManager::GetInstance()->SendEvent("ChangeNight", nullptr);
		timeCount += deltaTime;

		/// 밤 -> 낮 전환 스크린

		// 검정 화면 페이드인
		if (timeCount > 0.f && timeCount <= 1.f)
		{
			if (!m_RunOnce)
			{
				m_BlackScreenScript->m_BlackScreen->FadeIn(1.5f);
				m_RunOnce = true;
			}
		}

		if (timeCount > 1.7f)
		{
			int npcNo1 = killNPCList[0];
			int npcNo2 = killNPCList[1];
			int npcNo3 = killNPCList[2];
			int npcNo4 = killNPCList[3];

			ShowKillWindow(npcNo1, npcNo2, npcNo3, npcNo4);
		}

		if (timeCount > 2.f)
		{
			// 낮에 알려야 할 것
			wstring textData = L"";

			// 텍스트 추가
			if (m_DeadNPCIndex != -1) textData += L"마을 사람 하나가 실종되었다!";
			if (textData != L"") textData += L"\n";
			if (!m_QuestManager->m_ApplyFarm) textData += L"멧돼지놈들이 밭을 망쳐버렸다...";

			// 검정 화면 활성화
			m_BlackScreenScript->PlayText(true, textData);
		}

		if (timeCount > 5.f)
		{
			// 검정 화면 비활성화
			m_BlackScreenScript->DisabledBlackScreen();

			isMorning = false;
			timeCount = 0;
			NPCSponCheck();
			m_RunOnce = false;
		}


	}

	else if (isNight == true)
	{
		timeCount += deltaTime;

		/// 낮 -> 밤 전환 스크린

		//검은 화면 생성
		if (timeCount > 0.f && timeCount <= 1.f)
		{
			if (!m_RunOnce)
			{
				m_BlackScreenScript->m_BlackScreen->FadeIn(1.5f);
				m_RunOnce = true;
			}
		}

		if (timeCount > 2.f)
		{
			// 밤에 알려야 할 것
			wstring textData = L"";

			// 텍스트 추가
			if (!m_QuestManager->m_CompleteAllActiveQuests)
				textData += L"할 일 미완료. 경찰 순찰 강화";
			if (textData != L"") textData += L"\n";
			if (!m_QuestManager->m_SaveCat)
				textData += L"고양이가 죽어서 우울해…";

			// 검정 화면 활성화
			m_BlackScreenScript->PlayText(false, textData);
		}

		if (timeCount > 5.f)
		{
			// 검정 화면 비활성화
			m_BlackScreenScript->DisabledBlackScreen();

			isNight = false;
			m_IsDay = !m_IsDay;
			timeCount = 0;

			//순찰레벨에 따라 경찰의 속도 변경
			PolicePatrolLevelCheck();
			//일차별 경찰 생성
			PoliceSponCheck();
		}
	}
	// 밤
	else
	{
		EventManager::GetInstance()->SendEvent("ChangeNight", nullptr);
		// 시간이 흘러요
		m_TimePassed += deltaTime;

		// 퀘스트 생성
		if (m_IsCreateQuest)
		{
			m_QuestManager->m_PondObject->GetObjectChild("PondCat")->SetActivate(false);
			//m_QuestManager->m_PondObject->GetObjectChild("pondExclamationMark")->SetActivate(false);

			// 고양이 구하기 여부에 따라서 활성화 비활성화 
			if (m_QuestManager->m_SaveCat == false)
			{
				m_QuestManager->m_SaveCat = true;
				/*dynamic_cast<FarmerScript*>(m_QuestManager->m_Player->GetComponent<MonoBehaviour>())->speed = 400;
				dynamic_cast<FarmerScript*>(m_QuestManager->m_Player->GetComponent<MonoBehaviour>())->diagonalSpeed = 200;*/
			}


			// 밤 퀘스트 발생 시간
			CheckNightQuest();
			// 퀘스트 생성
			m_QuestManager->CreateQuest(m_DayCount, m_IsDay);
			// 낮밤이 바뀌기 전까진 재생성 불가능
			m_IsCreateQuest = false;
			// 아이템 모두 삭제
			// m_ItemManager->DeleteAllItem();
			m_QuestManager->DeleteAllItem();
		}

		// 밤 퀘스트 생성 가능하다면
		if (m_IsCreateNightQuest)
		{
			// 현재 시간이 밤 퀘스트 생성 시간을 넘는다면 
			if (m_TimePassed > m_NightQuestTime)
			{
				// 밤 퀘스트 생성
				m_QuestManager->CreateNightRandomQuest();
				m_IsCreateNightQuest = false;
			}
		}
		//if (m_TimePassed + 3 > NIGHTTIME_LENGTH)
		//{
		//	//여기서 페이드 인 시작?
		//	m_BlackScreen->SetActivate(true);
		//	m_BlackScreen->GetComponent<ImageRenderer>()->FadeIn(2);
		//}

		if (m_TimePassed > NIGHTTIME_LENGTH)
		{
			//fade in out 을 위한 변수
			isNight = false;
			isMorning = true;
			m_RunOnce = false;

			// 퀘스트 생성 가능
			m_IsCreateQuest = true;

			m_IsDay = !m_IsDay;
			m_TimePassed = 0.f;
			m_DayCount++;

			if (m_DayCount > DAY_MAX) return;

			m_IsKillAvailable = true;

			// 텍스트 및 이미지 변경
			wstring dateText = to_wstring(m_DayCount) + L"일차 낮";
			m_TimeBar->GetDateText()->SetText(dateText.c_str());
			m_TimeBar->GetTimeBarImage()->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarImageSun", L"/UI/timebarSun.png")->GetImage());
			m_TimeBar->GetTimeIconImage()->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarIconSun", L"/UI/timeiconSun.png")->GetImage());
			m_TimeBar->GetTimeIconImage()->SetPositionOffset(Vector2(2.f, 0.f));

			// BGM 재생
			SoundManager::GetInstance()->StopSoundBGM();
			SoundManager::GetInstance()->PlaySoundBGM(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"DayBGM", L"/Sound/BGM/DAY/Joy Ride.mp3")->GetSound());
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"DaySFX", L"/Sound/SFX/DayNight/Day_Chicken.mp3")->GetSound());
			SoundManager::GetInstance()->SetBGMVolume(m_DayBGMVolume);

			// 순찰 레벨 증가가 일시적이라면 낮에 다시 감소시켜준다.
			if (m_PatrolLevelTemporary)
			{
				EventManager::GetInstance()->SendEvent("PatrolLevelDown", nullptr);
				m_PatrolLevelTemporary = false;
			}
		}


	}
}

/// <summary>
/// 긴급 퀘스트 생성 여부를 체크한다.
/// </summary>
void GameManagerScript::CheckEmergencyQuest()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(30, 60);

	int randomNumber = dis(gen);

	// 30 ~ 60 숫자중에 39 이상이라면 긴급 퀘스트 생성  (70퍼 확률)
	if (randomNumber > 39)
	{
		m_IsCreateEmergencyQuest = true;
	}

	////테스트
	/*std::uniform_int_distribution<int> dis(1, 2);
	int randomNumber = dis(gen);
	m_IsCreateEmergencyQuest = true;*/

	//긴급 퀘스트 발생 시간
	m_EmergencyQuestTime = randomNumber;
}

/// <summary>
/// 밤 퀘스트 생성 여부를 체크한다.
/// </summary>
void GameManagerScript::CheckNightQuest()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(10, 20);

	//// 테스트
	//std::uniform_int_distribution<int> dis(1, 2);

	m_IsCreateNightQuest = true;
	// 밤 퀘스트 발생 시간
	m_NightQuestTime = dis(gen);
}

void GameManagerScript::CheckFarmState()
{
	for (auto& farmId : m_FarmScripts)
	{
		if (farmId.second->completeQuestCount == 2)
		{
			string farmState = farmId.second->detailState;

			if (farmState == "NoSeed")
			{
				farmId.second->detailState = "Seed";
			}
			else if (farmState == "Seed")
			{
				if (farmId.second->fakeSeed)
				{
					farmId.second->fakeSeed = false;
				}
				else
				{
					farmId.second->detailState = "First";
				}
			}
			else if (farmState == "First")
			{
				farmId.second->detailState = "Second";
			}
			else if (farmState == "Second")
			{
				farmId.second->detailState = "Third";
			}
		}
		else if (farmId.second->completeQuestCount == 1)
		{
			if (farmId.second->fakeSeed)
			{
				farmId.second->detailState = "NoSeed";
				farmId.second->fakeSeed = false;
			}
		}


		if (farmId.second->farmState == "FarmWater")
		{
			farmId.second->farmState = "FarmNoWater";
		}

		farmId.second->completeQuestCount = 0;
		farmId.second->isInteraction = false;
	}
}

void GameManagerScript::InitializeFarmFertilizer()
{
	for (auto& farmId : m_FarmScripts)
	{
		int index = farmId.second->farmNumber;
		for (auto& farmChild : farmId.second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildFertilizer" + to_string(index) || farmChild->GetName() == "SecondFarmChildFertilizer" + to_string(index))
			{
				if (farmChild->GetActivate())
				{
					farmChild->SetActivate(false);
				}
			}
		}
	}
}

void GameManagerScript::InitializeWildBoar()
{
	for (auto& object : m_QuestManager->m_QuestObjects)
	{
		if (object->GetObjectType() == OBJECT_TYPE::WILDBOAR)
		{
			if (object->GetObjectParent() != nullptr)
			{
				object->GetObjectParent()->GetTransform()->SetLocalPosition(Vector2{ -3000.f, -150.f } + Vector2{ 960.f, 540.f });
				object->GetObjectParent()->SetActivate(false);
				return;
			}
			else
			{
				object->GetTransform()->SetLocalPosition(Vector2{ -2000.f, -150.f } + Vector2{ 960.f, 540.f });
				object->SetActivate(false);
				return;
			}
		}
	}
}

/// <summary>
/// 함수화 해야하는데 머리가 안돌아간다. 언젠가 멀쩡해지면 다시 보자
/// </summary>
void GameManagerScript::DestoryFarm()
{
	if ((m_FarmScripts.find(2))->second->isDestroyFarm == false)
	{
		(m_FarmScripts.find(1))->second->isDestroyFarm = true;
		(m_FarmScripts.find(1))->second->detailState = "NoSeed";

		int index = (m_FarmScripts.find(1))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(1))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(2))->second->isDestroyFarm = true;
		(m_FarmScripts.find(2))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(2))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(2))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(3))->second->isDestroyFarm = true;
		(m_FarmScripts.find(3))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(3))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(3))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}
	}
	else if ((m_FarmScripts.find(5))->second->isDestroyFarm == false)
	{
		(m_FarmScripts.find(4))->second->isDestroyFarm = true;
		(m_FarmScripts.find(4))->second->detailState = "NoSeed";

		int index = (m_FarmScripts.find(4))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(4))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(5))->second->isDestroyFarm = true;
		(m_FarmScripts.find(5))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(5))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(5))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(6))->second->isDestroyFarm = true;
		(m_FarmScripts.find(6))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(6))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(6))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

	}
	else if ((m_FarmScripts.find(8))->second->isDestroyFarm == false)
	{
		(m_FarmScripts.find(7))->second->isDestroyFarm = true;
		(m_FarmScripts.find(7))->second->detailState = "NoSeed";

		int index = (m_FarmScripts.find(7))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(7))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(8))->second->isDestroyFarm = true;
		(m_FarmScripts.find(8))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(8))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(8))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(9))->second->isDestroyFarm = true;
		(m_FarmScripts.find(9))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(9))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(9))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "FirstFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

	}
	else if ((m_FarmScripts.find(11))->second->isDestroyFarm == false)
	{
		(m_FarmScripts.find(10))->second->isDestroyFarm = true;
		(m_FarmScripts.find(10))->second->detailState = "NoSeed";

		int index = (m_FarmScripts.find(10))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(10))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(11))->second->isDestroyFarm = true;
		(m_FarmScripts.find(11))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(11))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(11))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(12))->second->isDestroyFarm = true;
		(m_FarmScripts.find(12))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(12))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(12))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

	}
	else if ((m_FarmScripts.find(14))->second->isDestroyFarm == false)
	{
		(m_FarmScripts.find(13))->second->isDestroyFarm = true;
		(m_FarmScripts.find(13))->second->detailState = "NoSeed";

		int index = (m_FarmScripts.find(13))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(13))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(14))->second->isDestroyFarm = true;
		(m_FarmScripts.find(14))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(14))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(14))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(15))->second->isDestroyFarm = true;
		(m_FarmScripts.find(15))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(15))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(15))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

	}
	else if ((m_FarmScripts.find(17))->second->isDestroyFarm == false)
	{
		(m_FarmScripts.find(16))->second->isDestroyFarm = true;
		(m_FarmScripts.find(16))->second->detailState = "NoSeed";

		int index = (m_FarmScripts.find(16))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(16))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(17))->second->isDestroyFarm = true;
		(m_FarmScripts.find(17))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(17))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(17))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}

		(m_FarmScripts.find(18))->second->isDestroyFarm = true;
		(m_FarmScripts.find(18))->second->detailState = "NoSeed";

		index = (m_FarmScripts.find(18))->second->farmNumber;
		for (auto& farmChild : (m_FarmScripts.find(18))->second->GetGameObject()->GetObjectChildren())
		{
			if (farmChild->GetName() == "SecondFarmChildPanel" + to_string(index))
			{
				farmChild->SetActivate(true);
			}
		}
	}
}

/// <summary>
/// 엔딩 분기 체크
/// </summary>
void GameManagerScript::CheckEndingQuarter()
{
	for (auto& item : m_ItemManager->m_ItemList)
	{
		if (item != nullptr)
		{
			if (item->m_ItemKeyName == L"corn")
			{
				if (item->m_ItemCount >= 9)
				{
					/// 진 엔딩 (옥수수 9개 이상 모음)
					GameplayStatics::LoadScene("TrueEnding");
					return;
				}
			}
		}
	}

	GameplayStatics::LoadScene("ArrestedEnding");
	return;
}

void GameManagerScript::ShowKillWindow(int npc1, int npc2, int npc3, int npc4 /*= 999*/)
{
	if (m_IsKillAvailable)
	{
		KillWindow* killWindow = new KillWindow(m_DayCount, npc1, npc2, npc3, npc4);
		GameplayStatics::CreateObject(killWindow);
		GameplayStatics::PauseGame();
		m_IsKillAvailable = false;
	}
}

void GameManagerScript::GetKillNpcIndex(std::any index)
{
	m_DeadNPCIndex = std::any_cast<int>(index);
	GameplayStatics::ResumeGame();
}

void GameManagerScript::CheckGameOver()
{
	if (!m_IsGameOver) return;

	if (!m_ShowGameOverWindow)
	{
		GameOverWindow* gameoverWindow = new GameOverWindow();
		GameplayStatics::CreateObject(gameoverWindow);
		m_ShowGameOverWindow = true;

		GameplayStatics::PauseGame();
	}
}

void GameManagerScript::NPCSponCheck()
{
	if (m_DayCount == 2) //1일차 밤
	{
		killNPCList.clear();

		if (m_DeadNPCIndex != -1)
		{
			NPCKillCheck(m_DeadNPCIndex);
			killNPCList.push_back(999);
			EventManager::GetInstance()->SendEvent("PatrolLevelUp", nullptr);
		}

		MakeNPCKillList();

	}

	else if (m_DayCount == 3) //2일차 밤
	{
		//1일차에 사람을 죽였을 경우,
		if (killNPCList[0] == 999)
			m_NPC3Script->isDead = false;

		killNPCList.clear();

		if (m_DeadNPCIndex != -1)
		{
			NPCKillCheck(m_DeadNPCIndex);
			killNPCList.push_back(999);
			EventManager::GetInstance()->SendEvent("PatrolLevelUp", nullptr);
		}

		MakeNPCKillList();

	}

	else if (m_DayCount == 4) //3일차 밤
	{
		//2일차에 사람을 죽였을 경우,
		if (killNPCList[0] == 999)
			m_NPC4Script->isDead = false;

		killNPCList.clear();

		if (m_DeadNPCIndex != -1)
		{
			NPCKillCheck(m_DeadNPCIndex);
			killNPCList.push_back(999);
			EventManager::GetInstance()->SendEvent("PatrolLevelUp", nullptr);
		}

		MakeNPCKillList();
	}

	else if (m_DayCount == 5) //4일차 밤
	{

		//3일차에 사람을 죽였을 경우,
		if (killNPCList[0] == 999)
			m_NPC1Script->isDead = false;

		killNPCList.clear();

		if (m_DeadNPCIndex != -1)
		{
			NPCKillCheck(m_DeadNPCIndex);
			killNPCList.push_back(999);
			EventManager::GetInstance()->SendEvent("PatrolLevelUp", nullptr);
		}
		MakeNPCKillList();
	}

	else if (m_DayCount == 5)
	{

		if (m_DeadNPCIndex != -1)
		{
			NPCKillCheck(m_DeadNPCIndex);
			killNPCList.clear();
			MakeNPCKillList();
			killNPCList.push_back(999);
			EventManager::GetInstance()->SendEvent("PatrolLevelUp", nullptr);
		}
	}
}

void GameManagerScript::MakeNPCKillList()
{
	if (m_NPC1Script->isDead == false)
		killNPCList.push_back(1);

	if (m_NPC2Script->isDead == false)
		killNPCList.push_back(2);

	if (m_NPC3Script->isDead == false)
		killNPCList.push_back(3);

	if (m_NPC4Script->isDead == false)
		killNPCList.push_back(4);

	if (m_NPC5Script->isDead == false)
		killNPCList.push_back(5);

	if (m_NPC6Script->isDead == false)
		killNPCList.push_back(6);

}

void GameManagerScript::NPCKillCheck(int NPCIndex)
{
	if (NPCIndex == 1)
		m_NPC1Script->isDead = true;
	else if (NPCIndex == 2)
		m_NPC2Script->isDead = true;
	else if (NPCIndex == 3)
		m_NPC3Script->isDead = true;
	else if (NPCIndex == 4)
		m_NPC4Script->isDead = true;
	else if (NPCIndex == 5)
		m_NPC5Script->isDead = true;
	else if (NPCIndex == 6)
		m_NPC6Script->isDead = true;
}

void GameManagerScript::PoliceSponCheck()
{

	switch (m_DayCount)
	{
		case 1:
			m_Police1Script->isDead = true;
			m_Police2Script->isDead = true;
			m_Police3Script->isDead = false;
			m_Police4Script->isDead = true;
			break;

		case 2:
			m_Police1Script->isDead = false;
			m_Police2Script->isDead = true;
			m_Police3Script->isDead = false;
			m_Police4Script->isDead = true;
			break;

		case 3:
			m_Police1Script->isDead = false;
			m_Police2Script->isDead = true;
			m_Police3Script->isDead = false;
			m_Police4Script->isDead = true;
			break;

		case 4:
			m_Police1Script->isDead = false;
			m_Police2Script->isDead = true;
			m_Police3Script->isDead = false;
			m_Police4Script->isDead = false;
			break;

		case 5:
			m_Police1Script->isDead = false;
			m_Police2Script->isDead = false;
			m_Police3Script->isDead = false;
			m_Police4Script->isDead = false;
			break;
	}
}

/// <summary>
/// 플레이어가 퀘스트관련 오브젝트와 상호작용 하기위해
/// 오브젝트 아이디 값을 활용하여 퀘스트를 체크한다.
/// 
/// --> 퀘스트 매니저에서 밭 상태를 알아야 하기때문에 id 값이 아닌 오브젝트 자체를 보내기로 했다..
/// 굉장히 자주 상태를, 디테일하게 봐야하기 때문에 이벤트처리나 및 여러단계를 거치는것보다는 괜찮을지도? 잘 모르겠다
/// 
/// </summary>
/// <param name="scanObject"></param>
void GameManagerScript::Interaction(GameObject* scanObject)
{
	int scanObejectId = dynamic_cast<ObjectDataScript*>(scanObject->GetComponent<MonoBehaviour>())->id;
	m_QuestManager->CheckQuest(scanObejectId, scanObject);
}


/// <summary>
/// 이펙트
/// </summary>
/// <param name="deltaTime"></param>
void GameManagerScript::TimeEffectManagement(float deltaTime)
{
	if ((isNight == false && isMorning == false))
	{
		m_DayPassed += deltaTime;
		m_EffectTimePassed += deltaTime;
	}

	if (m_DayPassed > DAY_TOTAL_TIME) m_DayPassed = 0.f;

	// 시간대 설정
	if (m_DayPassed >= 0.f) m_CurrentTimeZone = DAY_NIGHT::MORNING_EARLY;																	// 0.f
	if (m_DayPassed >= DAYTIME_LENGTH / 4) m_CurrentTimeZone = DAY_NIGHT::MORNING_LATE;														// 22.5f
	if (m_DayPassed >= DAYTIME_LENGTH / 2) m_CurrentTimeZone = DAY_NIGHT::AFTERNOON_EARLY;													// 45.f
	if (m_DayPassed >= DAYTIME_LENGTH / 2 + DAYTIME_LENGTH / 4) m_CurrentTimeZone = DAY_NIGHT::AFTERNOON_LATE;								// 67.5f

	if (m_DayPassed >= DAYTIME_LENGTH) m_CurrentTimeZone = DAY_NIGHT::EVENING_EARLY;														// 90.f
	if (m_DayPassed >= DAYTIME_LENGTH + NIGHTTIME_LENGTH / 4) m_CurrentTimeZone = DAY_NIGHT::EVENING_LATE;									// 112.5f
	if (m_DayPassed >= DAYTIME_LENGTH + NIGHTTIME_LENGTH / 2) m_CurrentTimeZone = DAY_NIGHT::LATENIGHT_EARLY;								// 135.f
	if (m_DayPassed >= DAYTIME_LENGTH + NIGHTTIME_LENGTH / 2 + NIGHTTIME_LENGTH / 4) m_CurrentTimeZone = DAY_NIGHT::LATENIGHT_LATE;		// 157.5f

	if (m_DayPassed >= DAYTIME_LENGTH + NIGHTTIME_LENGTH) m_CurrentTimeZone = DAY_NIGHT::MORNING_EARLY;										// 180.f

	// 정해둔 주기따라 실행
	if (m_EffectTimePassed > EFFECT_CHANGE_LENGTH)
	{
		// 이펙트 적용
		switch (m_CurrentTimeZone)
		{
			case DAY_NIGHT::MORNING_EARLY:
			{
				if (m_Brightness > 0.f) m_Brightness -= m_BrightnessValue * m_EffectTimePassed;
				if (m_Temperature < 0.f) m_Temperature += m_TemperatureValue * m_EffectTimePassed;
				if (m_ColorTint < 0.f) m_ColorTint += m_ColorTintValue * m_EffectTimePassed;
			}
			break;
			case DAY_NIGHT::MORNING_LATE:
			{
				// 온도 올리기
				if (m_Temperature < 0.8f) m_Temperature += m_TemperatureValue * m_EffectTimePassed;
			}
			break;
			case DAY_NIGHT::AFTERNOON_EARLY:
			{
				// 온도, 색조 올리기
				if (m_Temperature < 0.8f) m_Temperature += m_TemperatureValue * m_EffectTimePassed * 2;
				if (m_ColorTint < 0.5f) m_ColorTint += m_ColorTintValue * m_EffectTimePassed;
			}
			break;
			case DAY_NIGHT::AFTERNOON_LATE:
			{
				// 어두워지기 시작
				if (m_Brightness < 0.06f) m_Brightness += m_BrightnessValue * m_EffectTimePassed;

				// 색조 올리기
				if (m_ColorTint < 0.5f) m_ColorTint += m_ColorTintValue * m_EffectTimePassed;
				if (m_Temperature > -0.8f) m_Temperature -= m_TemperatureValue * m_EffectTimePassed * 2;
			}
			break;
			case DAY_NIGHT::EVENING_EARLY:
			{
				if (m_Brightness < 0.06f) m_Brightness += m_BrightnessValue * m_EffectTimePassed;

				// 온도 내리기
				if (m_Temperature > -0.8f) m_Temperature -= m_TemperatureValue * m_EffectTimePassed * 2;
			}
			break;
			case DAY_NIGHT::EVENING_LATE:
			{
				// 온도 내리기
				if (m_Temperature > -0.8f) m_Temperature -= m_TemperatureValue * m_EffectTimePassed;
			}
			break;
			case DAY_NIGHT::LATENIGHT_EARLY:
			{
				if (m_Temperature < 0.8f) m_Temperature += m_TemperatureValue * m_EffectTimePassed;
				if (m_ColorTint > 0.f) m_ColorTint -= m_ColorTintValue * m_EffectTimePassed;
			}
			break;
			case DAY_NIGHT::LATENIGHT_LATE:
			{
				// 밝아지기 시작
				if (m_Brightness > 0.f) m_Brightness -= m_BrightnessValue * m_EffectTimePassed;

				// 온도 올리기, 색조 내리기
				if (m_Temperature < 0.8f) m_Temperature += m_TemperatureValue * m_EffectTimePassed * 2;
				if (m_ColorTint > 0.f) m_ColorTint -= m_ColorTintValue * m_EffectTimePassed;
			}
			break;
			default:
				break;
		}

		m_EffectTimePassed = 0.f;
		m_EffectManager->ApplyTimeFlowEffect(m_Temperature, m_ColorTint, m_Brightness);

		// 		OutputDebugString(TEXT("Brightness: "));
		// 		OutputDebugString(to_wstring(m_Brightness).c_str());
		// 		OutputDebugString(TEXT("\n"));
	}

}