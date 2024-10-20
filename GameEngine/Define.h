#pragma once

class GameObject;
class Collider;


/// ========= 오브젝트 =========

/// <summary>
/// 오브젝트의 타입의 번호가 작을수록 모든 이벤트에서 우선순위를 가진다.
/// 다른의미로 큰 번호일 수록 가장 상단에 렌더링한다.
/// </summary>
enum class OBJECT_TYPE
{
	DEFAULT,	// 매니저 오브젝트
	BACKGROUND, // 배경

	FARM,		// 밭
	ADDITINAL,  // 비료, 금지, 선택, 물에 빠진 고양이 이미지,애니메이션



	ANIMAL,		// 동물	
	NPC,		// NPC
	BUILDING,	// 건물
	WILDBOAR,   // 멧돼지
	TREE,		// 나무
	PLAYER,		// 플레이어
	PLAYER_AIM, // 플레이어 에임


	TEXTBUBBLE,	// 말풍선
	INTERACTION_ARROW, // 상호작용 화살표
	POLICEVIEW,	// Police 시야
	NPCVIEW,	// NPC 시야


	EFFECT,		// 이펙트
	// 아래의 오브젝트 타입부터는 마우스 이벤트가 발생함
	UI = 30,

	CAMERA = 31,
	END = 32,
};

/// ========= 충돌 관련 =========
struct Collision
{
	Collider* myCollider;

	GameObject* otherObject;
	Collider* otherCollider;
};


/// ========== FSM 관련 =========
enum class STATE_TYPE
{
	IDLE,
	WALK,
	DEAD,
};