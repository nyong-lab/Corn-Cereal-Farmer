/// [2023/8/14] 박연하
/// --------------------------
/// 전체적인 게임 흐름을 관리하는 게임 매니저
/// 게임 흐름을 보여주는 UI를 함께 관리한다
/// 
/// [2023/08/18] 고윤서 
/// -----------------------
/// 게임의 메인로직을 위해 수정

#pragma once

#include "MonoBehaviour.h"

#include <map>
#include <vector>
using std::vector;

class TimeBar;
class QuestManagerScript;
class ItemManagerScript;
class EffectManagerScript;
class GameObject;
class ImageRenderer;
class Animator;
class FarmScript;
class NPC1Script;
class NPC2Script;
class PoliceScript;
class Police2Script;
class BlackScreenScript;

enum class ITEM_TYPE;

enum class DAY_NIGHT
{
    MORNING_EARLY,
    MORNING_LATE,
    AFTERNOON_EARLY,
    AFTERNOON_LATE,
    EVENING_EARLY,
    EVENING_LATE,
    LATENIGHT_EARLY,
    LATENIGHT_LATE,
};

class GameManagerScript : public MonoBehaviour
{
public:
    GameManagerScript();
    ~GameManagerScript();

public:
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Finalize();

public:
    // 이벤트

    // 경찰
    void PatrolLevelUp(std::any); // 순찰 레벨 증가
    void PatrolLevelDown(std::any); // 순찰 레벨 감소
    void PatrolLevelTemporary(std::any); // 순찰 레벨 증가가 일시적인가
    void PolicePatrolLevelCheck();

    //알람 보내는 이벤트
    void alarmAlert(std::any);

    // 고양이
    void CatBowlEmpty(std::any);
    void CatBowlFull(std::any);
    
public:
    // 날짜 관리
    void CheckDayProgress(float deltaTime);
    
    // 이펙트
    void TimeEffectManagement(float deltaTime);

    /// 퀘스트
    // 긴급 퀘스트 체크
    void CheckEmergencyQuest();
    // 밤 퀘스트 체크
    void CheckNightQuest();
    // 플레이어 상호 작용
    void Interaction(GameObject* scanObject);

    /// 밭 (옥수수)
    // 옥수수 퀘스트 관리
    void CheckCornQuest();
    // 밭 상태 체크
    void CheckFarmState();
    // 밭 비료 이미지 초기화
    void InitializeFarmFertilizer();

    /// 멧돼지
    void InitializeWildBoar();
    void DestoryFarm();

    /// 엔딩분기
    void CheckEndingQuarter();

    /// 죽일까?
    void ShowKillWindow(int npc1 = 999, int npc2 = 999, int npc3 = 999, int npc4 = 999);
    void GetKillNpcIndex(std::any index);

    /// 게임오버
    void CheckGameOver();

    ///NPC 관리
    void NPCSponCheck();
    void MakeNPCKillList();
    void NPCKillCheck(int NPCIndex);
    
    void PoliceSponCheck();

public:
    /// 게임 진행 

    // 낮, 밤, 게임 플레이 날짜 길이 설정
    const float DAYTIME_LENGTH = 90.f;
    const float NIGHTTIME_LENGTH = 60.f;


    const int DAY_MAX = 5;
    
    // 현재 일차와 낮/밤을 구분하는 변수
    int m_DayCount;
    bool m_IsDay;
    // 시간의 흐름을 검사
    double m_TimePassed;
    // 시간 관련 UI
    TimeBar* m_TimeBar;

    ///NPC관련
    // 시체가 어디에 있는지
    Vector2 m_DeadBodySpot;
    //spon을 위한 script
    NPC1Script* m_NPC1Script;
    NPC2Script* m_NPC2Script;
    NPC1Script* m_NPC3Script;
    NPC1Script* m_NPC4Script;
    NPC1Script* m_NPC5Script;
    NPC2Script* m_NPC6Script;
    PoliceScript* m_Police1Script;
    PoliceScript* m_Police2Script;
    Police2Script* m_Police3Script;
    Police2Script* m_Police4Script;
    vector<int> killNPCList;

    /// 사운드
    float m_DayBGMVolume;
    float m_NightBGMVolume;

    /// 퀘스트
    // 퀘스트 생성 가능한지
    bool m_IsCreateQuest;
    // 긴급 퀘스트 생성 가능한지
    bool m_IsCreateEmergencyQuest;
    // 긴급 퀘스트 생성 시간
    int m_EmergencyQuestTime;
    // 밤 퀘스트 생성 가능한지 체크
    bool m_IsCreateNightQuest;
    // 밤 퀘스트 생성 시간
    int m_NightQuestTime;

    /// 경찰
    // 순찰 레벨이 일시적이였는가
    bool m_PatrolLevelTemporary;
    // 순찰 레벨 
    int m_PatrolLevel; 
   
    /// 고양이
    Animator* m_CatBowlAnimator;

    /// 밭
  /*  vector<FarmScript*> m_FarmScripts;*/
    std::map<int, FarmScript*> m_FarmScripts;

    /// 죽은애 인덱스
    bool m_IsKillAvailable = true;
    int m_DeadNPCIndex = -1;


    /// 이펙트

    // 이펙트 주기 조절
    const float EFFECT_CHANGE_LENGTH = 0.1f;
    float m_EffectTimePassed;

    // 이펙트를 위한 시간대 나누기
    float DAY_TOTAL_TIME;
    DAY_NIGHT m_CurrentTimeZone;
    float m_DayPassed;

    // 이펙트 수치
    float m_Temperature;
    float m_ColorTint;

    float m_TemperatureValue;
    float m_ColorTintValue;

    float m_Brightness;
    float m_BrightnessValue;

    //화면전환 시 Fade In out
    BlackScreenScript* m_BlackScreenScript;
    bool m_RunOnce = false;

    bool isNight;
    bool isMorning;
    float timeCount;

    /// 게임 오버
    bool m_IsGameOver;
    bool m_ShowGameOverWindow;

    /// 매니저
    ItemManagerScript* m_ItemManager;
    QuestManagerScript* m_QuestManager;
    EffectManagerScript* m_EffectManager;
};


