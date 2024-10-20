#pragma once
#include <vector>
#include "MonoBehaviour.h"
#include "ZicoMath.h"

using std::wstring;
using std::vector;

/// <summary>
/// 작성일 : 2023.08.11
/// 작성자 : 고윤서
/// 
/// NPC1을 위한 스크립트
/// </summary>

class StateMachine;
class GameManagerScript;
class TextManagerScript;

class NPC1Script
	:public MonoBehaviour
{
public:
	NPC1Script();
	~NPC1Script();

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
	StateMachine* m_NPC1StateMachine;

	int directionCheck;				//방향 확인을 위한 변수
	//Vector2 NPC1Route;			//NPC의 루트를 확인하기 위한 변수
	int conversation;				//대화순서
	int patrolEnd;					//여기까지 돌아요
	string detailState;				//방향 상태를 위한 변수
	string NPC1state;				//NPC의 상태

	int count;						//순찰 거리를 위한 변수
	float timeCount;				//시간변수
	float deltaTime;				//델타타임
	bool playerCollisionCheck;		//플레이어와의 충돌 체크
	bool deadBodyCollisionCheck;	//시체와의 충돌 체크
	bool isTalking;					//대화 체크
	bool isReturn;					//스폰지점으로 이동
	bool isFind;					//시체로 이동
	bool isPlayerTalking;			//플레이어와의 대화 체크
	bool isRevive;					//부활
	bool isDead;					//죽음
	string m_ScriptMapKey;			//각 npc의 키 값을 저장해둘 string
	wstring textOut;				//랜덤하게 텍스트를 보내줄 친구
	
	vector<Vector2> patrolSpot1;
	vector<Vector2> patrolSpot2;	//순찰 위치
	vector<Vector2> patrolSpot3;	//순찰 위치
	vector<Vector2> patrolSpot4;	//순찰 위치
	vector<Vector2> patrolSpot5;	//순찰 위치

	int patrolNumber;				//몇 번째 위치로 이동?
	int patrolPath;					//어떤 루트 이용?

	bool xCheck;
	bool yCheck;

	Vector2 bodyPos;				//시체 위치
	Vector2 sponPos;				//스폰장소
	Vector2 gotoSpot;				//다음에 갈 곳

	GameManagerScript* m_NPC1Manager;
	TextManagerScript* m_NPC1TextManager;

public:
	void TalkingState(std::any);
	void FindBodyState(std::any);		//시체 발견 이벤트
};

