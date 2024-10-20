#pragma once
#include "MonoBehaviour.h"
#include "ZicoMath.h"

using std::wstring;

class StateMachine;
class GameManagerScript;
class TextManagerScript;

/// <summary>
/// 작성일 : 2023.08.16
/// 작성자 : 고윤서
/// 
/// Police를 위한 script
/// </summary>

class PoliceScript :
    public MonoBehaviour
{
public:
    PoliceScript();
    ~PoliceScript();

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
	StateMachine* m_PoliceStateMachine;

public:
	string detailState;
	string police1State;
	Vector2 sponPos;

	Vector2 patrolSpot1;
	Vector2 patrolSpot2;
	Vector2 patrolSpot3;
	Vector2 patrolSpot4;
	Vector2 patrolSpot;

	float timeCount;
	int randomPatrolNumber;
	string m_ScriptMapKey;			//각 npc의 키 값을 저장해둘 string
	wstring textOut;				//랜덤하게 텍스트를 보내줄 친구

	bool isCatch;
	bool isRevive;
	bool isBuildingCollision;		//건물과 부딪힘?
	bool isDead;					//죽음?
	int backCount;					//후진카운트
	int randomBackNumber;			//후진 방향

	int speed;						//경찰의 스피드


	bool xCheck;
	bool yCheck;

	GameManagerScript* m_Policemanager;
	TextManagerScript* m_PoliceTextManager;
};

