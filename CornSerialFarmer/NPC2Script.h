#pragma once
#include <vector>
#include "MonoBehaviour.h"
#include "ZicoMath.h"

using std::vector;
using std::wstring;

/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// NPC2를 위한 스크립트
/// </summary>

class StateMachine;
class GameManagerScript;
class TextManagerScript;

class NPC2Script :
    public MonoBehaviour
{
public:
    NPC2Script();
    ~NPC2Script();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;

public:
	StateMachine* m_NPC2StateMachine;

	int directionCheck;				//방향 확인을 위한 변수
	//Vector2 NPC1Route;			//NPC의 루트를 확인하기 위한 변수
	string detailState;				//방향 상태를 위한 변수
	string NPC2State;				//NPC의 상태

	int count;						//순찰 거리를 위한 변수
	int backCount;					//후진을 위한 변수
	int randomBackNumber;			//후진 방향을 위한 변수
	float timeCount;				//시체 발견부터 그 이후까지 시간함수
	float deltaTime;				//델타타임
	bool playerCollisionCheck;		//플레이어와의 충돌 체크
	bool deadBodyCollisionCheck;	//시체와의 충돌 체크
	bool isBuildingCollisionCheck;	//건물과 충돌 체크
	bool isTalking;					//대화 체크
	bool isReturn;					//스폰지점으로 이동
	bool isFind;					//시체로 이동
	bool isPlayerTalking;			//플레이어와의 대화 체크
	bool isPositionStart;			//시작 위치로 이동했는가?
	bool isRevive;					//부활
	bool isDead;					//죽음?
	int conversation;				//대화순서
	string m_ScriptMapKey;			//각 npc의 키 값을 저장해둘 string
	wstring textOut;				//랜덤하게 텍스트를 보내줄 친구

	bool xCheck;
	bool yCheck;

	Vector2 bodyPos;				//시체위치
	Vector2 sponPos;				//스폰위치
		
	vector<Vector2> startPoint1;	//스폰 이후 이동 
	vector<Vector2> startPoint2;	//스폰 이후 이동2
	int startPoint;					//시작 이동 번호
	Vector2 gotoSpot;				//다음으로 가시오
	int startPointCheck;			//어떤 시작 이동 사용?

	GameManagerScript* m_NPC2Manager;
	TextManagerScript* m_NPC2TextManager;
public:
	void TalkingState(std::any);
	void FindBodyState(std::any);
};

