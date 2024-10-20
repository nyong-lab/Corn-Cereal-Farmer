#pragma once
#include <vector>
#include "MonoBehaviour.h"
#include "ZicoMath.h"

using std::vector;
using std::wstring;

class StateMachine;
class GameManagerScript;
class TextManagerScript;

/// <summary>
/// 작성일 : 2023.08.22
/// 작성자 : 고윤서
/// 
/// 순찰을 도는 police
/// </summary>

class Police2Script :
    public MonoBehaviour
{

public:
    Police2Script();
    ~Police2Script();

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
	Vector2 gotoSpot;

	vector<Vector2> patrolSpot1;
	vector<Vector2> patrolSpot2;


	float timeCount;
	int patrolNumber;
	string m_ScriptMapKey;			//각 npc의 키 값을 저장해둘 string
	wstring textOut;				//랜덤하게 텍스트를 보내줄 친구

	bool isCatch;
	bool isRevive;
	bool isDead;
	int patrolPath;
	int speed;						//경찰의 스피드	

	bool xCheck;
	bool yCheck;

	GameManagerScript* m_Policemanager;
	TextManagerScript* m_PoliceTextManager;

};

