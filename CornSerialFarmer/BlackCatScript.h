#pragma once
#include "MonoBehaviour.h"
#include "ZicoMath.h"

/// <summary>
/// 작성일 : 2023.08.15
/// 작성자 : 고윤서
/// 
/// BlackCat을 위한 스크립트
/// </summary>

class StateMachine;

class BlackCatScript :
    public MonoBehaviour
{

public:
    BlackCatScript();
    ~BlackCatScript();

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
	StateMachine* m_BlackCatStateMachine;

	int directionCheck;				//방향 확인을 위한 변수
	string detailState;				//방향 상태를 위한 변수
	string blackCatState;			//고양이의 상태
	bool isSave;					//고양이를 구했을 경우
	bool action;					//고양이 구하고 난 이후 액션 

	int count;						//랜덤 이동을 위한 카운트
	int randomDirection;			//랜덤 이동을 위한 방향 랜덤뭐시기
	float timeCount;					//시간 세는 카운트

	
};

