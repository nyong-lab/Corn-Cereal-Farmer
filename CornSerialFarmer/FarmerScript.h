#pragma once
#include "MonoBehaviour.h"

using std::wstring;

/// <summary>
/// 작성일 : 2023.08.09
/// 작성자 : 고윤서
/// 
/// FSM 돌아가는거 확인을 위한 테스트 스크립트
/// </summary>

class StateMachine;
class Camera;
class GameManagerScript;
class TextManagerScript;

class FarmerScript :
    public MonoBehaviour
{
public:
    FarmerScript();
    ~FarmerScript();

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
	// 이벤트
	void MiniGame(std::any); // 미니게임
	void FarmerWatering(std::any); // 물 주기 모션
	void FarmerInteraction(std::any); // 상호작용 모션
	void FarmerHarvest(std::any);	// 수확 모션
	
public:
	StateMachine* m_FarmerStateMachine;

	int speed;						//각 상태에 대한 스피드
	int diagonalSpeed;				//대각선 이동을 위한 스피드
	int directionCheck;				//방향 확인을 위한 변수
	float timeCount;				//시간을 확인하는 변수
	string detailState;				//멈춰있는 상태를 위한 변수
	string Farmerstate;				//상태를 위한 변수
	bool collisionCheck;			//충돌체크
	 
	bool deadBodyCollisionCheck;	//시체와의 충돌 체크
	bool farmCollisionCheck;		//밭과의 충돌 체크
	bool buildingCollisionCheck;	//집과의 충돌 체크		
	bool isNPCTalking;				//대화 상태
	bool isPlayerTalkingState;		//플레이어가 대답하는 상황
	bool isWatering;				//물 주는 상태
	bool isInterection;				//상호작용 상태
	bool isHarvest;					//수확하는 상태
	bool haveDeadBody;				//시체 들고 있는 상태
	bool hideDeadBody;				//시체 숨기기 상태
	bool isGameOver;				//게임 오버 상태
	bool isMorning;
	bool isNight;					//시간에 따른 초기화를 위한 상태
	
	
	string m_ScriptMapKey;			//각 npc의 키 값을 저장해둘 string
	wstring textOut;				//랜덤하게 텍스트를 보내줄 친구
	Vector2 sponPos;

	GameManagerScript* manager;
	TextManagerScript* textManager;
};

