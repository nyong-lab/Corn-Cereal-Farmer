#include "MainScene.h"

// Basic
#include "GameObject.h"
#include "Transform.h"

// Camera
#include "Camera.h"
#include "CameraScript.h"

// Collider
#include "CircleCollider.h"
#include "BoxCollider.h"

// Graphics
#include "../GraphicsEngine/GraphicsEngine.h"
#include "ImageRenderer.h"
#include "PrimitiveRenderer.h"
#include "Image.h"
#include "Animator.h"
#include "TextRenderer.h"
#include "Font.h"

// Manager
#include "EventManager.h"
#include "ResourceManager.h"

// Prefab
#include "PauseButton.h"
#include "TimeBar.h"
#include "ItemSlot.h"
#include "QuestList.h"
#include "ExplainWindow.h"
#include "BlackScreen.h"

// Script
#include "GameManagerScript.h"
#include "ItemManagerScript.h"
#include "QuestManagerScript.h"
#include "TextManagerScript.h"
#include "EffectManagerScript.h"
#include "FarmerScript.h"
#include "NPC1Script.h"
#include "NPC1ViewScript.h"
#include "NPC2Script.h"
#include "NPC2ViewScript.h"
#include "BlackCatScript.h"
#include "PoliceScript.h"
#include "Police2Script.h"
#include "Police2ViewScript.h"
#include "PoliceViewScript.h"
#include "ObjectDataScript.h"
#include "FarmScript.h"
#include "WildBoarScript.h"

#include "ChangdoScript.h"
#include "FarmerAim.h"
#include "Panel.h"

#include "Rigidbody.h"
#include "PolygonCollider.h"

#include "BubblePopScript.h"
// 오브젝트 ID 
// 
// 창고A : 1000
// 창고B : 2000
//	창고C : 3000
// 창고D : 4000
// 집 : 5000
// 밭 : 6000
// 연못 : 7000
// 나무 : 8000
// 고양이 밥통 : 9000
// 맷돼지 : 10000
// 

void MainScene::Enter()
{

#pragma region 충돌타입체크
	/// 충돌 타입 체크 ----------------------------------------------------------
	//플레이어
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);


	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BUILDING);


	//EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FARM);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::POLICEVIEW);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WILDBOAR);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ADDITINAL);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TREE);

	//플레이어 에임
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER_AIM, OBJECT_TYPE::FARM);

	//동물
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::ANIMAL, OBJECT_TYPE::BUILDING);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::WILDBOAR, OBJECT_TYPE::FARM);

	//NPC
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::NPC, OBJECT_TYPE::BUILDING);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::NPC, OBJECT_TYPE::TREE);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::NPCVIEW, OBJECT_TYPE::BUILDING);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::POLICEVIEW, OBJECT_TYPE::BUILDING);

#pragma endregion

	/// Camera ---------------------------------------------------------------
	GameObject* cameraObject = new GameObject("CameraObject", OBJECT_TYPE::CAMERA);
	Camera* camera = new Camera;
	CameraScript* cameraScript = new CameraScript;
	cameraObject->AddComponent(camera);
	cameraObject->AddComponent(cameraScript);
	AddGameObject(cameraObject);

	/// Background -----------------------------------------------------------
	GameObject* background = new GameObject("Background", OBJECT_TYPE::BACKGROUND);
	background->GetTransform()->SetLocalPosition(m_StartPoint);
	background->GetTransform()->SetSize({ 4800.f, 2704.f });
	ImageRenderer* backgroundRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"BackGround", L"/Image/floor/lever.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 4800.f, 2704.f }
	);
	background->AddComponent(backgroundRender);
	AddGameObject(background);


	/// Resources ------------------------------------------------------------

#pragma region 건물
	/// 창고 A (상호작용 가능 / ObjectId 1000)
	///
	GameObject* warehouseA = new GameObject("WareHouseA", OBJECT_TYPE::BUILDING);
	warehouseA->GetTransform()->SetLocalPosition(Vector2(-1300, -530) + m_StartPoint);
	warehouseA->GetTransform()->SetSize({ 510.f, 420.f });
	ImageRenderer* warehouseARender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseA", L"/Image/House/Warehouse_A.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 510.f, 420.f }
	);
	Collider* warehouseACollider = new BoxCollider({ 420.f, 240.f });
	warehouseACollider->SetOffset({ 0.f,70.f });

	ObjectDataScript* warehouseADataScript = new ObjectDataScript(1000);
	warehouseADataScript->isDeadBodyHave = false;

	warehouseA->AddComponent(warehouseADataScript);
	warehouseA->AddComponent(warehouseACollider);
	warehouseA->AddComponent(warehouseARender);

	AddGameObject(warehouseA);

	// 창고 A 말풍선
	GameObject* warehouseATextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* warehouseATextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleHouse", L"/Image/UI/die_mark_1.png")->GetImage());
	warehouseATextBubble->AddComponent(warehouseATextBubbleAnimator);
	warehouseATextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	warehouseATextBubbleAnimator->Play(L"DieMark", true);

	warehouseA->AddObjectChild(warehouseATextBubble);
	warehouseA->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 창고 A 상호작용 화살표 
	GameObject* warehouseAInteractionArrow = new GameObject("warehouseAInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	warehouseAInteractionArrow->GetTransform()->SetLocalPosition({ 40.f, -130.f });
	warehouseAInteractionArrow->SetActivate(false);

	Animator* warehouseAInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseAInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	warehouseAInteractionArrow->AddComponent(warehouseAInteractionArrowAnimator);
	warehouseAInteractionArrowAnimator->CreateAnimation(L"warehouseAInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	warehouseAInteractionArrowAnimator->Play(L"warehouseAInteractionArrowAnimation", true);

	ObjectDataScript* warehouseAInteractionArrowDataScript = new ObjectDataScript(0);
	warehouseAInteractionArrow->AddComponent(warehouseAInteractionArrowDataScript);

	warehouseA->AddObjectChild(warehouseAInteractionArrow);

	// -----------------------------------------------------------------------

	/// 창고 B (상호작용 가능 / ObjectId 2000)
	///
	GameObject* warehouseB = new GameObject("WarehouseB", OBJECT_TYPE::BUILDING);
	warehouseB->GetTransform()->SetLocalPosition(Vector2(-1110, 570) + m_StartPoint);
	warehouseB->GetTransform()->SetSize({ 912.f, 438.f });
	ImageRenderer* warehouseBRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseB", L"/Image/House/Warehouse_B.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 912.f, 438.f }
	);
	Collider* warehouseBCollider = new BoxCollider({ 870.f, 260.f });
	warehouseBCollider->SetOffset({ 0.f,80.f });
	ObjectDataScript* warehouseBDataScript = new ObjectDataScript(2000);
	warehouseBDataScript->isDeadBodyHave = true;

	warehouseB->AddComponent(warehouseBDataScript);
	warehouseB->AddComponent(warehouseBCollider);
	warehouseB->AddComponent(warehouseBRender);

	AddGameObject(warehouseB);

	//창고 B 말풍선
	GameObject* warehouseBTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* warehouseBTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleWareHouseB", L"/Image/UI/die_mark_1.png")->GetImage());
	warehouseBTextBubble->AddComponent(warehouseBTextBubbleAnimator);
	warehouseBTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(250, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	warehouseBTextBubbleAnimator->Play(L"DieMark", true);

	warehouseB->AddObjectChild(warehouseBTextBubble);
	warehouseB->GetObjectChild("houseTextBubble")->SetActivate(true);

	// 창고 B 상호작용 화살표 
	GameObject* warehouseBInteractionArrow = new GameObject("warehouseBInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	warehouseBInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -150.f });
	warehouseBInteractionArrow->SetActivate(false);

	Animator* warehouseBInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseBInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	warehouseBInteractionArrow->AddComponent(warehouseBInteractionArrowAnimator);
	warehouseBInteractionArrowAnimator->CreateAnimation(L"warehouseBInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	warehouseBInteractionArrowAnimator->Play(L"warehouseBInteractionArrowAnimation", true);

	//ObjectDataScript* warehouseBInteractionArrowDataScript = new ObjectDataScript(0);
	//warehouseBInteractionArrow->AddComponent(warehouseBInteractionArrowDataScript);

	warehouseB->AddObjectChild(warehouseBInteractionArrow);

	// -----------------------------------------------------------------------

	/// 창고 C (상호작용 가능 / ObjectId 3000)
	///
	GameObject* warehouseC = new GameObject("WarehouseC", OBJECT_TYPE::BUILDING);
	warehouseC->GetTransform()->SetLocalPosition(Vector2(660, 540) + m_StartPoint);
	warehouseC->GetTransform()->SetSize({ 510.f, 420.f });
	ImageRenderer* warehouseCRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseC", L"/Image/House/Warehouse_C.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 510.f, 420.f }
	);
	Collider* warehouseCCollider = new BoxCollider({ 420.f, 240.f });
	warehouseCCollider->SetOffset({ 0.f,70.f });

	ObjectDataScript* warehouseCDataScript = new ObjectDataScript(3000);
	warehouseCDataScript->isDeadBodyHave = false;

	warehouseC->AddComponent(warehouseCDataScript);
	warehouseC->AddComponent(warehouseCCollider);
	warehouseC->AddComponent(warehouseCRender);

	AddGameObject(warehouseC);

	//창고 C 말풍선
	GameObject* warehouseCTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* warehouseCTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleWareHouseB", L"/Image/UI/die_mark_1.png")->GetImage());
	warehouseCTextBubble->AddComponent(warehouseCTextBubbleAnimator);
	warehouseCTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	warehouseCTextBubbleAnimator->Play(L"DieMark", true);

	warehouseC->AddObjectChild(warehouseCTextBubble);
	warehouseC->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 창고 C 상호작용 화살표 
	GameObject* warehouseCInteractionArrow = new GameObject("warehouseCInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	warehouseCInteractionArrow->GetTransform()->SetLocalPosition({ 40.f, -130.f });
	warehouseCInteractionArrow->SetActivate(false);

	Animator* warehouseCInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseCInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	warehouseCInteractionArrow->AddComponent(warehouseCInteractionArrowAnimator);
	warehouseCInteractionArrowAnimator->CreateAnimation(L"warehouseCInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	warehouseCInteractionArrowAnimator->Play(L"warehouseCInteractionArrowAnimation", true);

	ObjectDataScript* warehouseCInteractionArrowDataScript = new ObjectDataScript(0);
	warehouseCInteractionArrow->AddComponent(warehouseCInteractionArrowDataScript);

	warehouseC->AddObjectChild(warehouseCInteractionArrow);

	// -----------------------------------------------------------------------

	/// 창고 D (상호작용 가능 / ObjectId 4000)
	///
	GameObject* warehouseD = new GameObject("WarehouseD", OBJECT_TYPE::BUILDING);
	warehouseD->GetTransform()->SetLocalPosition(Vector2(2080, 0) + m_StartPoint);
	warehouseD->GetTransform()->SetSize({ 600.f, 700.f });

	ImageRenderer* warehouseDRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseD", L"/Image/House/Warehouse_D.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 600.f, 700.f }
	);

	Collider* warehouseDCollider = new BoxCollider({ 580.f, 400.f });
	warehouseDCollider->SetOffset({ 0.f,120.f });

	ObjectDataScript* warehouseDDataScript = new ObjectDataScript(4000);
	warehouseDDataScript->isDeadBodyHave = false;

	warehouseD->AddComponent(warehouseDDataScript);
	warehouseD->AddComponent(warehouseDCollider);
	warehouseD->AddComponent(warehouseDRender);

	AddGameObject(warehouseD);

	//창고 D말풍선
	GameObject* warehouseDTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* warehouseDTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleWareHouseB", L"/Image/UI/die_mark_1.png")->GetImage());
	warehouseDTextBubble->AddComponent(warehouseDTextBubbleAnimator);
	warehouseDTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	warehouseDTextBubbleAnimator->Play(L"DieMark", true);

	warehouseD->AddObjectChild(warehouseDTextBubble);
	warehouseD->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 창고 D 상호작용 화살표 
	GameObject* warehouseDInteractionArrow = new GameObject("warehouseDInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	warehouseDInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -130.f });
	warehouseDInteractionArrow->SetActivate(false);

	Animator* warehouseDInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseDInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	warehouseDInteractionArrow->AddComponent(warehouseDInteractionArrowAnimator);
	warehouseDInteractionArrowAnimator->CreateAnimation(L"warehouseDInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	warehouseDInteractionArrowAnimator->Play(L"warehouseDInteractionArrowAnimation", true);

	ObjectDataScript* warehouseDInteractionArrowDataScript = new ObjectDataScript(0);
	warehouseDInteractionArrow->AddComponent(warehouseDInteractionArrowDataScript);

	warehouseD->AddObjectChild(warehouseDInteractionArrow);

	// -----------------------------------------------------------------------

	/// 집 (상호작용 가능 / ObjectId 5000)
	///
	GameObject* house = new GameObject("House", OBJECT_TYPE::BUILDING);
	house->GetTransform()->SetLocalPosition(Vector2(-600, -590) + m_StartPoint);
	house->GetTransform()->SetSize({ 636.f, 516.f });

	ImageRenderer* houseRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"House", L"/Image/House/House.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 636.f, 516.f }
	);

	Collider* houseCollider = new BoxCollider({ 630.f, 300.f });
	houseCollider->SetOffset({ 0.f,75.f });

	ObjectDataScript* houseDataScript = new ObjectDataScript(5000);
	houseDataScript->isDeadBodyHave = false;

	house->AddComponent(houseDataScript);
	house->AddComponent(houseCollider);
	house->AddComponent(houseRender);

	AddGameObject(house);

	//집 말풍선
	GameObject* houseTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* houseTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleWareHouseB", L"/Image/UI/die_mark_1.png")->GetImage());
	houseTextBubble->AddComponent(houseTextBubbleAnimator);
	houseTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	houseTextBubbleAnimator->Play(L"DieMark", true);

	house->AddObjectChild(houseTextBubble);
	house->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 집 상호작용 화살표 
	GameObject* houseInteractionArrow = new GameObject("houseInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	houseInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -130.f });
	houseInteractionArrow->SetActivate(false);

	Animator* houseInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"houseInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	houseInteractionArrow->AddComponent(houseInteractionArrowAnimator);
	houseInteractionArrowAnimator->CreateAnimation(L"houseInteractionArrowAnimaton", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	houseInteractionArrowAnimator->Play(L"houseInteractionArrowAnimaton", true);

	house->AddObjectChild(houseInteractionArrow);

	// -----------------------------------------------------------------------

	/// 연못 (상호작용 가능 / ObjectId 7000)
	///
	GameObject* pond = new GameObject("Pond", OBJECT_TYPE::BUILDING);
	pond->GetTransform()->SetLocalPosition(Vector2(-150, 440) + m_StartPoint);
	pond->GetTransform()->SetSize({ 492.f, 492.f });

	Animator* pondAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Pond", L"/Image/House/Pond_Sheet.png")->GetImage());
	pondAnimator->CreateAnimation(L"pond", Vector2(0, 0), Vector2(492, 492), Vector2(0, 0), Vector2(492, 0), 0.2f, 4);
	pondAnimator->Play(L"pond", true);

	PolygonCollider* pondCollider = new PolygonCollider();
	pondCollider->AddVertice({ 143.f, 214.f });
	pondCollider->AddVertice({ 189.f, 71.f });
	pondCollider->AddVertice({ 79.f, -170.f });
	pondCollider->AddVertice({ -66.f, -226.f });
	pondCollider->AddVertice({ -199.f, -140.f });
	pondCollider->AddVertice({ -188.f, 28.f });
	pondCollider->AddVertice({ -68.f, 218.f });

	ObjectDataScript* pondDataScript = new ObjectDataScript(7000);
	pondDataScript->isDeadBodyHave = false;

	pond->AddComponent(pondDataScript);
	pond->AddComponent(pondCollider);
	pond->AddComponent(pondAnimator);

	AddGameObject(pond);

	// 임시 연못 말풍선
	GameObject* pondTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* pondTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleHouse", L"/Image/UI/die_mark_1.png")->GetImage());
	pondTextBubble->AddComponent(pondTextBubbleAnimator);
	pondTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	pondTextBubbleAnimator->Play(L"DieMark", true);

	pond->AddObjectChild(pondTextBubble);
	pond->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 물에 빠진 고양이
	GameObject* pondCat = new GameObject("PondCat", OBJECT_TYPE::ADDITINAL);
	pondCat->GetTransform()->SetLocalPosition({ 17.f, -40.f });
	pondCat->SetActivate(false);

	Animator* pondCatAnimatior = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"PondCatImage", L"/Image/Animation/cat/cat_water.png")->GetImage());
	pondCat->AddComponent(pondCatAnimatior);
	pondCatAnimatior->CreateAnimation(L"PondCatAnimaion", Vector2(0, -0), Vector2(84, 151), Vector2(0, 0), Vector2(84, 0), 0.2f, 4);
	pondCatAnimatior->Play(L"PondCatAnimaion", true);

	pond->AddObjectChild(pondCat);

	// 연못 긴급 퀘스트 느낌표 
	/*GameObject* pondExclamationMark = new GameObject("pondExclamationMark", OBJECT_TYPE::ADDITINAL);
	pondExclamationMark->GetTransform()->SetLocalPosition({ 0.f, -250.f });
	pondExclamationMark->SetActivate(false);

	Animator* pondExclamationMarkAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"PondExclamationMark", L"/Image/UI/EX_mark.png")->GetImage());
	pondExclamationMark->AddComponent(pondExclamationMarkAnimator);
	pondExclamationMarkAnimator->CreateAnimation(L"PondExclamationMarkAnimaion", Vector2(0, -0), Vector2(152, 136), Vector2(0, 0), Vector2(152, 0), 0.2f, 4);
	pondExclamationMarkAnimator->Play(L"PondExclamationMarkAnimaion", true);

	pond->AddObjectChild(pondExclamationMark);*/

	// 연못 상호작용 화살표 
	GameObject* pondInteractionArrow = new GameObject("pondInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	pondInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -170.f });
	pondInteractionArrow->SetActivate(false);

	Animator* pondInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"pondInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	pondInteractionArrow->AddComponent(pondInteractionArrowAnimator);
	pondInteractionArrowAnimator->CreateAnimation(L"pondInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	pondInteractionArrowAnimator->Play(L"pondInteractionArrowAnimation", true);

	pond->AddObjectChild(pondInteractionArrow);

	// -----------------------------------------------------------------------

	/// 트럭 (상호작용 가능 / ObjectId 0) (윤서 전용)
	///
	GameObject* truck = new GameObject("Truck", OBJECT_TYPE::BUILDING);
	truck->GetTransform()->SetLocalPosition(Vector2(-1230, 220) + m_StartPoint);
	truck->GetTransform()->SetSize({ 570.f, 300.f });

	Animator* truckAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"truck", L"/Image/House/Truck_sheet.png")->GetImage());
	truckAnimator->CreateAnimation(L"truck", Vector2(0, 0), Vector2(570.f, 300.f), Vector2(0, 0), Vector2(570.f, 0), 0.2f, 5);
	truckAnimator->Play(L"truck", true);

	Collider* truckCollider = new BoxCollider({ 545.f, 165.f });
	truckCollider->SetOffset({ 0.f, 45.f });

	ObjectDataScript* truckDataScript = new ObjectDataScript(0);
	truckDataScript->isDeadBodyHave = false;

	truck->AddComponent(truckDataScript);
	truck->AddComponent(truckCollider);
	truck->AddComponent(truckAnimator);
	AddGameObject(truck);

	// 임시 트럭 말풍선
	GameObject* truckTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* truckTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleWarehHouse", L"/Image/UI/die_mark_1.png")->GetImage());
	truckTextBubble->AddComponent(truckTextBubbleAnimator);
	truckTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	truckTextBubbleAnimator->Play(L"DieMark", true);

	truck->AddObjectChild(truckTextBubble);
	truck->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 트럭 상호작용 화살표  (윤서 전용)
	GameObject* truckInteractionArrow = new GameObject("truckInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	truckInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -170.f });
	truckInteractionArrow->SetActivate(false);

	Animator* truckInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"truckInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	truckInteractionArrow->AddComponent(truckInteractionArrowAnimator);
	truckInteractionArrowAnimator->CreateAnimation(L"truckInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	truckInteractionArrowAnimator->Play(L"truckInteractionArrowAnimation", true);

	truck->AddObjectChild(truckInteractionArrow);

	// -----------------------------------------------------------------------
#pragma endregion

#pragma region 고양이관련
	/// 고양이 집
	///
	GameObject* catHouse = new GameObject("CatHouse", OBJECT_TYPE::BUILDING);
	catHouse->GetTransform()->SetLocalPosition(Vector2(-1030, -1000) + m_StartPoint);
	catHouse->GetTransform()->SetSize({ 300.f, 325.f });

	ImageRenderer* catHouseRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CatHouse", L"/Image/House/cat_house.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 300.f, 325.f }
	);

	Collider* catHouseCollider = new BoxCollider({ 165.f, 160.f });
	catHouseCollider->SetOffset({ 0.f,25.f });

	ObjectDataScript* catHouseDataScript = new ObjectDataScript(0);

	catHouse->AddComponent(catHouseCollider);
	catHouse->AddComponent(catHouseRender);
	catHouse->AddComponent(catHouseDataScript);

	AddGameObject(catHouse);

	///고양이 밥 (상호작용 가능 / ObjectId 9000)
	///
	GameObject* catBowl = new GameObject("CatBowl", OBJECT_TYPE::BUILDING);
	catBowl->GetTransform()->SetLocalPosition(Vector2(-840, -870) + m_StartPoint);
	catBowl->GetTransform()->SetSize({ 76.f, 72.f });

	Animator* catBowlAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"CatBowl", L"/Image/House/pet_bowl.png")->GetImage());
	catBowlAnimator->CreateAnimation(L"catBowlEmpty", Vector2(0, 0), Vector2(76, 72), Vector2(0, 0), Vector2(0, 0), 0.1f, 1);
	catBowlAnimator->CreateAnimation(L"catBowlFull", Vector2(0, 0), Vector2(76, 72), Vector2(76, 0), Vector2(0, 0), 0.1f, 1);
	catBowlAnimator->Play(L"catBowlEmpty", true);

	Collider* catBowlCollider = new BoxCollider({ 70.f, 45.f });
	catBowlCollider->SetOffset({ 0.f,10.f });

	ObjectDataScript* catBowlDataScript = new ObjectDataScript(9000);

	catBowl->AddComponent(catBowlDataScript);
	catBowl->AddComponent(catBowlCollider);
	catBowl->AddComponent(catBowlAnimator);

	AddGameObject(catBowl);

	// 임시 고양이식당 말풍선
	GameObject* catBowlTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* catBowlTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleCatBowl", L"/Image/UI/die_mark_1.png")->GetImage());
	catBowlTextBubble->AddComponent(catBowlTextBubbleAnimator);
	catBowlTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	
	catBowl->AddObjectChild(catBowlTextBubble);
	catBowl->GetObjectChild("houseTextBubble")->SetActivate(false);

	// 고양이 밥 상호작용 화살표 
	GameObject* catBowlInteractionArrow = new GameObject("catBowlInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	catBowlInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -170.f });
	catBowlInteractionArrow->SetActivate(false);

	Animator* catBowlInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"catBowlInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	catBowlInteractionArrow->AddComponent(catBowlInteractionArrowAnimator);
	catBowlInteractionArrowAnimator->CreateAnimation(L"catBowlInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	catBowlInteractionArrowAnimator->Play(L"catBowlInteractionArrowAnimation", true);

	catBowl->AddObjectChild(catBowlInteractionArrow);

	// -----------------------------------------------------------------------

	/// 검은 고양이
	GameObject* blackCat = new GameObject("blackCat", OBJECT_TYPE::ANIMAL);

	Collider* blackCatCollider = new BoxCollider(Vector2{ 60.f, 40.f });
	blackCatCollider->SetOffset(Vector2{ 0.f, 45.f });
	blackCat->AddComponent(blackCatCollider);

	Animator* blackCatAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"blackCat", L"/Image/Animation/cat/cat.png")->GetImage());
	blackCat->AddComponent(blackCatAnimator);
	blackCatAnimator->CreateAnimation(L"blackCatIdleFront", Vector2(0, 0), Vector2(136, 120), Vector2(0, 0), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatIdleLeft", Vector2(0, 0), Vector2(136, 120), Vector2(0, 120), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatIdleRight", Vector2(0, 0), Vector2(136, 120), Vector2(0, 240), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatIdleBack", Vector2(0, 0), Vector2(136, 120), Vector2(0, 360), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatMoveFront", Vector2(0, 0), Vector2(136, 120), Vector2(0, 480), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatMoveLeft", Vector2(0, 0), Vector2(136, 120), Vector2(0, 600), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatMoveRight", Vector2(0, 0), Vector2(136, 120), Vector2(0, 720), Vector2(136, 0), 0.2f, 4);
	blackCatAnimator->CreateAnimation(L"blackCatMoveBack", Vector2(0, 0), Vector2(136, 120), Vector2(0, 840), Vector2(136, 0), 0.2f, 4);
	//blackCatAnimator->Play(L"blackCatWalkLeft", true);
	BlackCatScript* blackCatScript = new BlackCatScript;
	blackCat->AddComponent(blackCatScript);

	AddGameObject(blackCat);

	GameObject* blackCatChild = new GameObject("blackCatChild", OBJECT_TYPE::ADDITINAL);

	Collider* blackCatChildCollider = new BoxCollider(Vector2{ 60.f, 40.f });
	blackCatChildCollider->SetOffset(Vector2{ 0.f, 45.f });
	blackCatChild->AddComponent(blackCatChildCollider);

	Animator* blackCatChildAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"blackCatChild", L"/Image/Animation/effect/heart effect.png")->GetImage());
	blackCatChildAnimator->CreateAnimation(L"heartEffect", Vector2(0, 0), Vector2(132, 172), Vector2(0, 0), Vector2(132, 0), 0.2f, 4);
	blackCatChildAnimator->Play(L"heartEffect", true);

	blackCatChild->AddComponent(blackCatChildAnimator);

	blackCat->AddObjectChild(blackCatChild);

	blackCatChild->SetActivate(false);

	// -----------------------------------------------------------------------
#pragma endregion

#pragma region 멧돼지

	/// 멧돼지 
	GameObject* wildBoar = new GameObject("wildBoar", OBJECT_TYPE::WILDBOAR);
	wildBoar->GetTransform()->SetSize(Vector2(176, 128));
	wildBoar->GetTransform()->SetLocalPosition(Vector2{ -2000.f,-144.f } + m_StartPoint);

	Collider* wildBoarCollider = new BoxCollider(Vector2{ 130.f, 125.f });
	wildBoar->AddComponent(wildBoarCollider);

	Animator* wildBoarAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WildBoar", L"/Image/Animation/wild_boar/wild_boar.png")->GetImage());
	wildBoar->AddComponent(wildBoarAnimator);
	wildBoarAnimator->CreateAnimation(L"WildBoarRightRun", Vector2(0.f, 0.f), Vector2(176.f, 128.f), Vector2(0.f, 128.f), Vector2(176.f, 0.f), 0.2f, 4);
	wildBoarAnimator->CreateAnimation(L"WildBoarLeftRun", Vector2(0.f, 0.f), Vector2(176.f, 128.f), Vector2(0.f, 0.f), Vector2(176.f, 0.f), 0.2f, 4);
	wildBoarAnimator->CreateAnimation(L"WildBoarIdle", Vector2(0.f, 0.f), Vector2(176.f, 128.f), Vector2(0.f, 128.f), Vector2(0.f, 0.f), 0.2f, 4);

	WildBoarScript* wildBoarScript = new WildBoarScript;
	wildBoar->AddComponent(wildBoarScript);

	AddGameObject(wildBoar);

	GameObject* wildBoarChild = new GameObject("wildBoarChild", OBJECT_TYPE::WILDBOAR);
	wildBoarChild->GetTransform()->SetSize(Vector2(176.f, 128.f));
	wildBoarChild->GetTransform()->SetLocalPosition({ 0.f,0.f });

	Collider* wildBoarChildCollider = new BoxCollider(Vector2{ 130.f, 125.f });
	wildBoarChildCollider->SetOffset(Vector2{ 0.f, 0.f });
	wildBoarChild->AddComponent(wildBoarChildCollider);

	ObjectDataScript* wildBoarChildDataScript = new ObjectDataScript(10000);
	wildBoarChild->AddComponent(wildBoarChildDataScript);

	wildBoar->AddObjectChild(wildBoarChild);

	// 멧돼지 밤 퀘스트 느낌표 
	GameObject* wildBoarExclamationMark = new GameObject("wildBoarExclamationMark", OBJECT_TYPE::ADDITINAL);
	wildBoarExclamationMark->GetTransform()->SetLocalPosition({ 0.f, -120.f });
	wildBoarExclamationMark->SetActivate(false);

	Animator* wildBoarExclamationMarkAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WildBoarExclamationMark", L"/Image/UI/EX_mark.png")->GetImage());
	wildBoarExclamationMark->AddComponent(wildBoarExclamationMarkAnimator);
	wildBoarExclamationMarkAnimator->CreateAnimation(L"WildBoarExclamationMarkAnimaion", Vector2(0, -0), Vector2(152, 136), Vector2(0, 0), Vector2(152, 0), 0.2f, 4);
	wildBoarExclamationMarkAnimator->Play(L"WildBoarExclamationMarkAnimaion", true);

	wildBoar->AddObjectChild(wildBoarExclamationMark);

#pragma endregion
	
#pragma region 상호작용나무
	/// 나무 (상호작용 가능 / ObjectId 8000)
	GameObject* tree = new GameObject("Tree", OBJECT_TYPE::BUILDING);
	tree->GetTransform()->SetLocalPosition(Vector2(490, -900.f) + m_StartPoint);
	tree->GetTransform()->SetSize({ 400.f, 382.f });

	ImageRenderer* treeRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree", L"/Image/floor/tree_wood.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 400.f, 382.f }
	);

	// Collider
	PolygonCollider* treeColliedr = new PolygonCollider;

	treeColliedr->AddVertice({ -46, 8 });
	treeColliedr->AddVertice({ -130, 186 });
	treeColliedr->AddVertice({ 64, 175 });
	treeColliedr->AddVertice({ 143, 116 });
	treeColliedr->AddVertice({ 137, 79 });
	treeColliedr->AddVertice({ 3, 25 });

	ObjectDataScript* treeDataScript = new ObjectDataScript(8000);

	tree->AddComponent(treeDataScript);
	tree->AddComponent(treeColliedr);
	tree->AddComponent(treeRender);


	GameObject* treeTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* treeTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleTree", L"/Image/UI/die_mark_1.png")->GetImage());
	treeTextBubble->AddComponent(treeTextBubbleAnimator);
	treeTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	//treeTextBubbleAnimator->Play(L"DieMark", true);

	tree->AddObjectChild(treeTextBubble);
	tree->GetObjectChild("houseTextBubble")->SetActivate(false);

	AddGameObject(tree);

	// 나무 상호작용 화살표 
	GameObject* treeInteractionArrow = new GameObject("treeInteractionArrow", OBJECT_TYPE::INTERACTION_ARROW);
	treeInteractionArrow->GetTransform()->SetLocalPosition({ 0.f, -170.f });
	treeInteractionArrow->SetActivate(false);

	Animator* treeInteractionArrowAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"treeInteractionArrow", L"/Image/UI/arrow_mark.png")->GetImage());
	treeInteractionArrow->AddComponent(treeInteractionArrowAnimator);
	treeInteractionArrowAnimator->CreateAnimation(L"treeInteractionArrowAnimation", Vector2(0, -0), Vector2(105.f, 145), Vector2(0, 0), Vector2(105.f, 0), 0.2f, 4);
	treeInteractionArrowAnimator->Play(L"treeInteractionArrowAnimation", true);

	tree->AddObjectChild(treeInteractionArrow);
#pragma endregion

#pragma region 나무
	/// TREES -------------------------------------------------------

	GameObject* tree1 = new GameObject("Tree1", OBJECT_TYPE::TREE);
	tree1->GetTransform()->SetLocalPosition(Vector2(410, -1300.f) + m_StartPoint);
	tree1->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree1Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree1", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree1Colliedr = new BoxCollider({ 60.f, 70.f });
	tree1Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree1->AddComponent(tree1Render);
	tree1->AddComponent(tree1Colliedr);

	AddGameObject(tree1);
	/// --------------------------------------------------------------

	GameObject* tree2 = new GameObject("Tree2", OBJECT_TYPE::TREE);
	tree2->GetTransform()->SetLocalPosition(Vector2(-150, -1100.f) + m_StartPoint);
	tree2->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree2Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree2", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree2Colliedr = new BoxCollider({ 60.f, 70.f });
	tree2Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree2->AddComponent(tree2Render);
	tree2->AddComponent(tree2Colliedr);

	AddGameObject(tree2);

	/// --------------------------------------------------------------

	GameObject* tree3 = new GameObject("Tree3", OBJECT_TYPE::TREE);
	tree3->GetTransform()->SetLocalPosition(Vector2(1215, -1080.f) + m_StartPoint);
	tree3->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree3Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree3", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree3Colliedr = new BoxCollider({ 60.f, 70.f });
	tree3Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree3->AddComponent(tree3Render);
	tree3->AddComponent(tree3Colliedr);

	AddGameObject(tree3);

	/// --------------------------------------------------------------

	GameObject* tree4 = new GameObject("Tree4", OBJECT_TYPE::TREE);
	tree4->GetTransform()->SetLocalPosition(Vector2(1020, -770.f) + m_StartPoint);
	tree4->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree4Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree4", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree4Colliedr = new BoxCollider({ 60.f, 70.f });
	tree4Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree4->AddComponent(tree4Render);
	tree4->AddComponent(tree4Colliedr);

	AddGameObject(tree4);

	/// --------------------------------------------------------------

	GameObject* tree5 = new GameObject("Tree5", OBJECT_TYPE::TREE);
	tree5->GetTransform()->SetLocalPosition(Vector2(1853, -722.f) + m_StartPoint);
	tree5->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree5Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree5", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree5Colliedr = new BoxCollider({ 60.f, 70.f });
	tree5Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree5->AddComponent(tree5Render);
	tree5->AddComponent(tree5Colliedr);

	AddGameObject(tree5);

	/// --------------------------------------------------------------

	GameObject* tree6 = new GameObject("Tree6", OBJECT_TYPE::TREE);
	tree6->GetTransform()->SetLocalPosition(Vector2(1640, 150.f) + m_StartPoint);
	tree6->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree6Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree6", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree6Colliedr = new BoxCollider({ 60.f, 70.f });
	tree6Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree6->AddComponent(tree6Render);
	tree6->AddComponent(tree6Colliedr);

	AddGameObject(tree6);

	/// --------------------------------------------------------------

	GameObject* tree7 = new GameObject("Tree7", OBJECT_TYPE::TREE);
	tree7->GetTransform()->SetLocalPosition(Vector2(1210, 695.f) + m_StartPoint);
	tree7->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree7Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree7", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree7Colliedr = new BoxCollider({ 60.f, 70.f });
	tree7Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree7->AddComponent(tree7Render);
	tree7->AddComponent(tree7Colliedr);

	AddGameObject(tree7);

	/// --------------------------------------------------------------

	GameObject* tree8 = new GameObject("Tree8", OBJECT_TYPE::TREE);
	tree8->GetTransform()->SetLocalPosition(Vector2(1300, 785.f) + m_StartPoint);
	tree8->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree8Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree8", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree8Colliedr = new BoxCollider({ 60.f, 70.f });
	tree8Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree8->AddComponent(tree8Render);
	tree8->AddComponent(tree8Colliedr);

	AddGameObject(tree8);

	/// --------------------------------------------------------------

	GameObject* tree9 = new GameObject("Tree9", OBJECT_TYPE::TREE);
	tree9->GetTransform()->SetLocalPosition(Vector2(705, 988.f) + m_StartPoint);
	tree9->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree9Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree9", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree9Colliedr = new BoxCollider({ 60.f, 70.f });
	tree9Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree9->AddComponent(tree9Render);
	tree9->AddComponent(tree9Colliedr);

	AddGameObject(tree9);

	/// --------------------------------------------------------------

	GameObject* tree10 = new GameObject("Tree10", OBJECT_TYPE::TREE);
	tree10->GetTransform()->SetLocalPosition(Vector2(665, 1208.f) + m_StartPoint);
	tree10->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree10Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree10", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree10Colliedr = new BoxCollider({ 60.f, 70.f });
	tree10Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree10->AddComponent(tree10Render);
	tree10->AddComponent(tree10Colliedr);

	AddGameObject(tree10);

	/// --------------------------------------------------------------

	GameObject* tree11 = new GameObject("Tree11", OBJECT_TYPE::TREE);
	tree11->GetTransform()->SetLocalPosition(Vector2(335, 685.f) + m_StartPoint);
	tree11->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree11Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree11", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree11Colliedr = new BoxCollider({ 60.f, 70.f });
	tree11Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree11->AddComponent(tree11Render);
	tree11->AddComponent(tree11Colliedr);

	AddGameObject(tree11);

	/// --------------------------------------------------------------

	GameObject* tree12 = new GameObject("Tree12", OBJECT_TYPE::TREE);
	tree12->GetTransform()->SetLocalPosition(Vector2(280, 360.f) + m_StartPoint);
	tree12->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree12Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree12", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree12Colliedr = new BoxCollider({ 60.f, 70.f });
	tree12Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree12->AddComponent(tree12Render);
	tree12->AddComponent(tree12Colliedr);

	AddGameObject(tree12);

	/// --------------------------------------------------------------

	GameObject* tree13 = new GameObject("Tree13", OBJECT_TYPE::TREE);
	tree13->GetTransform()->SetLocalPosition(Vector2(-515, 1130.f) + m_StartPoint);
	tree13->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree13Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree13", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree13Colliedr = new BoxCollider({ 60.f, 70.f });
	tree13Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree13->AddComponent(tree13Render);
	tree13->AddComponent(tree13Colliedr);

	AddGameObject(tree13);

	/// --------------------------------------------------------------

	GameObject* tree14 = new GameObject("Tree14", OBJECT_TYPE::TREE);
	tree14->GetTransform()->SetLocalPosition(Vector2(-675, 1010.f) + m_StartPoint);
	tree14->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree14Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree14", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree14Colliedr = new BoxCollider({ 60.f, 70.f });
	tree14Colliedr->SetOffset(Vector2(0.f,85.f));

	tree14->AddComponent(tree14Render);
	tree14->AddComponent(tree14Colliedr);

	AddGameObject(tree14);

	/// --------------------------------------------------------------

	GameObject* tree15 = new GameObject("Tree15", OBJECT_TYPE::TREE);
	tree15->GetTransform()->SetLocalPosition(Vector2(-1670, 440.f) + m_StartPoint);
	tree15->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree15Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree15", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree15Colliedr = new BoxCollider({ 60.f, 70.f });
	tree15Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree15->AddComponent(tree15Render);
	tree15->AddComponent(tree15Colliedr);

	AddGameObject(tree15);

	/// --------------------------------------------------------------

	GameObject* tree16 = new GameObject("Tree16", OBJECT_TYPE::TREE);
	tree16->GetTransform()->SetLocalPosition(Vector2(-1770, 535.f) + m_StartPoint);
	tree16->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree16Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree16", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree16Colliedr = new BoxCollider({ 60.f, 70.f });
	tree16Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree16->AddComponent(tree16Render);
	tree16->AddComponent(tree16Colliedr);

	AddGameObject(tree16);

	/// --------------------------------------------------------------

	GameObject* tree17 = new GameObject("Tree17", OBJECT_TYPE::TREE);
	tree17->GetTransform()->SetLocalPosition(Vector2(-1955, -400.f) + m_StartPoint);
	tree17->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree17Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree17", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree17Colliedr = new BoxCollider({ 60.f, 70.f });
	tree17Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree17->AddComponent(tree17Render);
	tree17->AddComponent(tree17Colliedr);

	AddGameObject(tree17);

	/// --------------------------------------------------------------

	GameObject* tree18 = new GameObject("Tree18", OBJECT_TYPE::TREE);
	tree18->GetTransform()->SetLocalPosition(Vector2(-1830, -315.f) + m_StartPoint);
	tree18->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree18Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree18", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree18Colliedr = new BoxCollider({ 60.f, 70.f });
	tree18Colliedr->SetOffset(Vector2(0.f,85.f));

	tree18->AddComponent(tree18Render);
	tree18->AddComponent(tree18Colliedr);

	AddGameObject(tree18);

	/// --------------------------------------------------------------

	GameObject* tree19 = new GameObject("Tree19", OBJECT_TYPE::TREE);
	tree19->GetTransform()->SetLocalPosition(Vector2(-1620, -795.f) + m_StartPoint);
	tree19->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree19Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree19", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree19Colliedr = new BoxCollider({ 60.f, 70.f });
	tree19Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree19->AddComponent(tree19Render);
	tree19->AddComponent(tree19Colliedr);

	AddGameObject(tree19);

	/// --------------------------------------------------------------

	GameObject* tree20 = new GameObject("Tree20", OBJECT_TYPE::TREE);
	tree20->GetTransform()->SetLocalPosition(Vector2(-1710, -700.f) + m_StartPoint);
	tree20->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree20Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree20", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree20Colliedr = new BoxCollider({ 60.f, 70.f });
	tree20Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree20->AddComponent(tree20Render);
	tree20->AddComponent(tree20Colliedr);

	AddGameObject(tree20);

	/// --------------------------------------------------------------

	GameObject* tree21 = new GameObject("Tree21", OBJECT_TYPE::TREE);
	tree21->GetTransform()->SetLocalPosition(Vector2(-1227, -1233.f) + m_StartPoint);
	tree21->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree21Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree21", L"/Image/floor/tree_2.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree21Colliedr = new BoxCollider({ 60.f, 70.f });
	tree21Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree21->AddComponent(tree21Render);
	tree21->AddComponent(tree21Colliedr);

	AddGameObject(tree21);

	/// --------------------------------------------------------------

	GameObject* tree22 = new GameObject("Tree22", OBJECT_TYPE::TREE);
	tree22->GetTransform()->SetLocalPosition(Vector2(-1340, -1143.f) + m_StartPoint);
	tree22->GetTransform()->SetSize({ 184.f, 252.f });

	ImageRenderer* tree22Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree22", L"/Image/floor/tree_1.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 184.f, 252.f }
	);

	Collider* tree22Colliedr = new BoxCollider({ 60.f, 70.f });
	tree22Colliedr->SetOffset(Vector2(0.f, 85.f));

	tree22->AddComponent(tree22Render);
	tree22->AddComponent(tree22Colliedr);

	AddGameObject(tree22);

	/// -------------------------------------------------------------- 

	GameObject* tree23 = new GameObject("Tree23", OBJECT_TYPE::TREE);
	tree23->GetTransform()->SetLocalPosition(Vector2(70, -970.f) + m_StartPoint);
	tree23->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree23Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree23", L"/Image/floor/tree_5.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree23Colliedr = new BoxCollider({ 162.f, 50.f });
	tree23Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree23->AddComponent(tree23Render);
	tree23->AddComponent(tree23Colliedr);

	AddGameObject(tree23);

	/// -------------------------------------------------------------- 

	GameObject* tree24 = new GameObject("Tree24", OBJECT_TYPE::TREE);
	tree24->GetTransform()->SetLocalPosition(Vector2(200, -970.f) + m_StartPoint);
	tree24->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree24Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree24", L"/Image/floor/tree_4.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree24Colliedr = new BoxCollider({ 162.f, 50.f });
	tree24Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree24->AddComponent(tree24Render);
	tree24->AddComponent(tree24Colliedr);

	AddGameObject(tree24);

	/// -------------------------------------------------------------- 

	GameObject* tree25 = new GameObject("Tree25", OBJECT_TYPE::TREE);
	tree25->GetTransform()->SetLocalPosition(Vector2(1200, -790.f) + m_StartPoint);
	tree25->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree25Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree25", L"/Image/floor/tree_6.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree25Colliedr = new BoxCollider({ 162.f, 50.f });
	tree25Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree25->AddComponent(tree25Render);
	tree25->AddComponent(tree25Colliedr);

	AddGameObject(tree25);

	/// -------------------------------------------------------------- 

	GameObject* tree26 = new GameObject("Tree26", OBJECT_TYPE::TREE);
	tree26->GetTransform()->SetLocalPosition(Vector2(1910, -458.f) + m_StartPoint);
	tree26->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree26Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree26", L"/Image/floor/tree_3.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree26Colliedr = new BoxCollider({ 162.f, 50.f });
	tree26Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree26->AddComponent(tree26Render);
	tree26->AddComponent(tree26Colliedr);

	AddGameObject(tree26);

	/// -------------------------------------------------------------- 

	GameObject* tree27 = new GameObject("Tree27", OBJECT_TYPE::TREE);
	tree27->GetTransform()->SetLocalPosition(Vector2(1845, -370.f) + m_StartPoint);
	tree27->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree27Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree27", L"/Image/floor/tree_6.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree27Colliedr = new BoxCollider({ 162.f, 50.f });
	tree27Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree27->AddComponent(tree27Render);
	tree27->AddComponent(tree27Colliedr);

	AddGameObject(tree27);

	/// -------------------------------------------------------------- 

	GameObject* tree28 = new GameObject("Tree28", OBJECT_TYPE::TREE);
	tree28->GetTransform()->SetLocalPosition(Vector2(130.f, 905.f) + m_StartPoint);
	tree28->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree28Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree28", L"/Image/floor/tree_3.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree28Colliedr = new BoxCollider({ 162.f, 50.f });
	tree28Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree28->AddComponent(tree28Render);
	tree28->AddComponent(tree28Colliedr);

	AddGameObject(tree28);

	/// -------------------------------------------------------------- 

	GameObject* tree29 = new GameObject("Tree29", OBJECT_TYPE::TREE);
	tree29->GetTransform()->SetLocalPosition(Vector2(135.f, 1158.f) + m_StartPoint);
	tree29->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree29Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree29", L"/Image/floor/tree_6.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree29Colliedr = new BoxCollider({ 162.f, 50.f });
	tree29Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree29->AddComponent(tree29Render);
	tree29->AddComponent(tree29Colliedr);

	AddGameObject(tree29);

	/// -------------------------------------------------------------- 

	GameObject* tree30 = new GameObject("Tree30", OBJECT_TYPE::TREE);
	tree30->GetTransform()->SetLocalPosition(Vector2(135.f, 1268.f) + m_StartPoint);
	tree30->GetTransform()->SetSize({ 172.f, 160.f });

	ImageRenderer* tree30Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree30", L"/Image/floor/tree_3.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 172.f, 160.f }
	);

	Collider* tree30Colliedr = new BoxCollider({ 162.f, 50.f });
	tree30Colliedr->SetOffset(Vector2(0.f, 50.f));

	tree30->AddComponent(tree30Render);
	tree30->AddComponent(tree30Colliedr);

	AddGameObject(tree30);

	/// -------------------------------------------------------------- 

	GameObject* tree31 = new GameObject("Tree31", OBJECT_TYPE::TREE);
	tree31->GetTransform()->SetLocalPosition(Vector2(-1690.f, 735.f) + m_StartPoint);
	tree31->GetTransform()->SetSize({ 144.f, 136.f });

	ImageRenderer* tree31Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree31", L"/Image/floor/stump.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 144.f, 136.f }
	);

	tree31->AddComponent(tree31Render);

	AddGameObject(tree31);

	/// -------------------------------------------------------------- 

	GameObject* tree32 = new GameObject("Tree32", OBJECT_TYPE::TREE);
	tree32->GetTransform()->SetLocalPosition(Vector2(-1710.f, -500.f) + m_StartPoint);
	tree32->GetTransform()->SetSize({ 144.f, 136.f });

	ImageRenderer* tree32Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree32", L"/Image/floor/stump.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 144.f, 136.f }
	);

	tree32->AddComponent(tree32Render);

	AddGameObject(tree32);

	/// -------------------------------------------------------------- 

	GameObject* tree33 = new GameObject("Tree33", OBJECT_TYPE::TREE);
	tree33->GetTransform()->SetLocalPosition(Vector2(-1955.f, -820.f) + m_StartPoint);
	tree33->GetTransform()->SetSize({ 144.f, 136.f });

	ImageRenderer* tree33Render = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree33", L"/Image/floor/stump.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 144.f, 136.f }
	);

	tree33->AddComponent(tree33Render);

	AddGameObject(tree33);
#pragma endregion

#pragma region UI
	/// UI -------------------------------------------------------------------

	/// Pause Button
	GameObject* pauseButton = new PauseButton();
	AddGameObject(pauseButton);

	/// Time Bar
	GameObject* timeBar = new TimeBar();
	AddGameObject(timeBar);

	/// Item Slot
	GameObject* itemSlot = new ItemSlot();
	AddGameObject(itemSlot);

	/// Quest List
	GameObject* questList = new QuestList();
	AddGameObject(questList);

	/// Game Manager ---------------------------------------------------------
	GameObject* gameManager = new GameObject("GameManager", OBJECT_TYPE::DEFAULT);
	gameManager->SetScene(this);
	GameManagerScript* gameManagerScript = new GameManagerScript();
	gameManager->AddComponent(gameManagerScript);

	gameManagerScript->m_TimeBar = (TimeBar*)timeBar;

	AddGameObject(gameManager);

	/// Item Manager
	GameObject* itemManager = new GameObject("ItemManager", OBJECT_TYPE::DEFAULT);
	gameManager->SetScene(this);
	ItemManagerScript* itemManagerScript = new ItemManagerScript();
	gameManager->AddComponent(itemManagerScript);

	itemManagerScript->m_ItemSlot = (ItemSlot*)itemSlot;
	AddGameObject(itemManager);

	/// Quest Manager	
	GameObject* questManager = new GameObject("QuestManager", OBJECT_TYPE::DEFAULT);
	questManager->SetScene(this);
	QuestManagerScript* questManagerScript = new QuestManagerScript();
	questManager->AddComponent(questManagerScript);

	questManagerScript->m_QuestUiList = (QuestList*)questList;
	questManagerScript->m_ItemManager = itemManagerScript;
	AddGameObject(questManager);

	questManagerScript->m_CatObject = blackCat;
	questManagerScript->m_PondObject = pond;
	questManagerScript->m_WildBoar = wildBoar;
	questManagerScript->m_Camera = cameraScript;

	/// Script Manager
	GameObject* textManager = new GameObject("textManager", OBJECT_TYPE::DEFAULT);
	textManager->SetScene(this);
	TextManagerScript* textManagerScript = new TextManagerScript();
	textManager->AddComponent(textManagerScript);

	AddGameObject(textManager);

	/// Effect Manager
	GameObject* effectManager = new GameObject("EffectManager", OBJECT_TYPE::DEFAULT);
	effectManager->SetScene(this);
	EffectManagerScript* effectManagerScript = new EffectManagerScript();
	effectManager->AddComponent(effectManagerScript);
	AddGameObject(effectManager);

	// 게임 매니저에 매니저 스크립트들 추가
	gameManagerScript->m_ItemManager = itemManagerScript;
	gameManagerScript->m_QuestManager = questManagerScript;
	gameManagerScript->m_EffectManager = effectManagerScript;

	// 퀘스트 관련 오브젝트들을 넣어줌 
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(warehouseA); // 창고 A  1000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(warehouseB); // 창고 B  2000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(warehouseC); // 창고 C  3000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(warehouseD); // 창고 D  4000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(house);      // 집 5000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(pond);       // 연못 7000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(tree);       // 나무 8000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(catBowl);    // 고양이 밥통 9000
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(wildBoarChild);    // 멧돼지 10000

	// 윤서
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(truck);	// 트럭 0

	// 고양이 애니메이터
	gameManagerScript->m_CatBowlAnimator = catBowlAnimator;

	// -----------------------------------------------------------------------
#pragma endregion

#pragma region 밭
	/// 밭1 (상호작용 가능 / ObjectId 6000) ----=====================================================================
	float farmPosX = 500.f;
	float farmPosY = 290.f;

	GameObject* firstFarm[10] = {};
	GameObject* firstFarmChild[10] = {};
	GameObject* firstFarmChildSelect[10] = {};
	GameObject* firstFarmChildFertilizer[10] = {};
	GameObject* firstFarmChildPanel[10] = {};

	for (int i = 1; i < 10; i++)
	{
		string farmName = "FirstFarm" + to_string(i);
		firstFarm[i] = new GameObject(farmName, OBJECT_TYPE::FARM);
		firstFarm[i]->GetTransform()->SetLocalPosition(Vector2(farmPosX, -farmPosY) + m_StartPoint);
		firstFarm[i]->GetTransform()->SetSize({ 125.f, 125.f });

		//Collider* firstFarmCollider = new BoxCollider(Vector2{ 125, 125 });
		FarmScript* firstFarmScript = new FarmScript;

		//firstFarm[i]->AddComponent(firstFarmCollider);
		firstFarm[i]->AddComponent(firstFarmScript);
		// 137  230
		Animator* firstFarmAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"corn", L"/Image/corn/corn_sheet.png")->GetImage());

		// 기본 
		firstFarmAnimator->CreateAnimation(L"farmNoSeed", Vector2(0, 0), Vector2(137, 230), Vector2(4, 12), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmSeed", Vector2(0, 0), Vector2(137, 230), Vector2(139, 12), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmFirst", Vector2(0, 0), Vector2(137, 230), Vector2(274, 12), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmSecond", Vector2(0, -3), Vector2(137, 230), Vector2(409, 10), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmThird", Vector2(0, -25), Vector2(137, 198), Vector2(544, 4), Vector2(0, 0), 0.1f, 1);
		// 기본 물 줌
		firstFarmAnimator->CreateAnimation(L"farmNoSeedWater", Vector2(0, 0), Vector2(137, 230), Vector2(4, 200), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmSeedWater", Vector2(0, 0), Vector2(137, 230), Vector2(139, 203), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmFirstWater", Vector2(0, 0), Vector2(137, 230), Vector2(274, 203), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmSecondWater", Vector2(0, -3), Vector2(137, 230), Vector2(409, 200), Vector2(0, 0), 0.1f, 1);
		firstFarmAnimator->CreateAnimation(L"farmThirdWater", Vector2(0, -25), Vector2(137, 198), Vector2(544, 192), Vector2(0, 0), 0.1f, 1);

		firstFarmAnimator->Play(L"farmThirdWater", true);

		firstFarm[i]->AddComponent(firstFarmAnimator);

		AddGameObject(firstFarm[i]);

		// 스크립트 중복 불가로 자식객체에 ObjectDataScript 넣어준다.
		string firstFarmChildName = "FirstFarmChild" + to_string(i);
		firstFarmChild[i] = new GameObject(firstFarmChildName, OBJECT_TYPE::FARM);

		Collider* firstFarmChildCollider = new BoxCollider(Vector2{ 125, 125 });
		ObjectDataScript* firstFarmChildDataScript = new ObjectDataScript(6000);

		firstFarmChild[i]->AddComponent(firstFarmChildCollider);
		firstFarmChild[i]->AddComponent(firstFarmChildDataScript);

		firstFarm[i]->AddObjectChild(firstFarmChild[i]);

		farmPosX -= 145;
		if (i % 3 == 0)
		{
			farmPosX = 500.f;
			farmPosY -= 145.f;
		}

		int nameIndex = 0;
		switch (i)
		{
		case 1:
			nameIndex = 9;
			firstFarmScript->farmNumber = 9;
			gameManagerScript->m_FarmScripts.insert(make_pair(9, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 2:
			nameIndex = 6;
			firstFarmScript->farmNumber = 6;
			gameManagerScript->m_FarmScripts.insert(make_pair(6, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 3:
			nameIndex = 3;
			firstFarmScript->farmNumber = 3;
			gameManagerScript->m_FarmScripts.insert(make_pair(3, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 4:
			nameIndex = 8;
			firstFarmScript->farmNumber = 8;
			gameManagerScript->m_FarmScripts.insert(make_pair(8, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 5:
			nameIndex = 5;
			firstFarmScript->farmNumber = 5;
			gameManagerScript->m_FarmScripts.insert(make_pair(5, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 6:
			nameIndex = 2;
			firstFarmScript->farmNumber = 2;
			gameManagerScript->m_FarmScripts.insert(make_pair(2, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 7:
			nameIndex = 7;
			firstFarmScript->farmNumber = 7;
			gameManagerScript->m_FarmScripts.insert(make_pair(7, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 8:
			nameIndex = 4;
			firstFarmScript->farmNumber = 4;
			gameManagerScript->m_FarmScripts.insert(make_pair(4, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 9:
			nameIndex = 1;
			firstFarmScript->farmNumber = 1;
			gameManagerScript->m_FarmScripts.insert(make_pair(1, dynamic_cast<FarmScript*>(firstFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		}

		// 선택 이미지 ㅡㅡ
		string firstFarmChildSelectName = "FirstFarmChildSelect" + to_string(nameIndex);
		firstFarmChildSelect[i] = new GameObject(firstFarmChildSelectName, OBJECT_TYPE::ADDITINAL);

		ImageRenderer* firstFarmChildSelectRender = new ImageRenderer
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"firstFarmChildSelectRender", L"/Image/corn/Field_A.png")->GetImage(),
			{ 0.f, 0.f }, { 0.f, 0.f }, { 145.f, 145.f }
		);

		firstFarmChildSelect[i]->AddComponent(firstFarmChildSelectRender);
		firstFarm[i]->AddObjectChild(firstFarmChildSelect[i]);

		firstFarmChildSelect[i]->GetTransform()->SetLocalPosition({ 0.f,0.f });
		firstFarmChildSelect[i]->GetTransform()->SetSize({ 145.f, 145.f });

		firstFarmChildSelect[i]->SetActivate(false);

		// 비료 이미지 ㅡㅡ
		string firstFarmChildFertilizerName = "FirstFarmChildFertilizer" + to_string(nameIndex);
		firstFarmChildFertilizer[i] = new GameObject(firstFarmChildFertilizerName, OBJECT_TYPE::ADDITINAL);

		ImageRenderer* firstFarmChildFertilizerRender = new ImageRenderer
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"firstFarmChildFertilizerRender", L"/Image/corn/field_Fertilizer.png")->GetImage(),
			{ 0.f, 0.f }, { 0.f, 0.f }, { 60.f, 45.f }
		);

		firstFarmChildFertilizer[i]->AddComponent(firstFarmChildFertilizerRender);
		firstFarm[i]->AddObjectChild(firstFarmChildFertilizer[i]);

		firstFarmChildFertilizer[i]->GetTransform()->SetLocalPosition({ 0.f,0.f });
		firstFarmChildFertilizer[i]->GetTransform()->SetSize({ 60.f, 45.f });

		firstFarmChildFertilizer[i]->SetActivate(false);
		firstFarmChildFertilizer[i]->GetTransform()->SetLocalPosition({ 0.f, 35.f });

		// 금지 판넬 이미지 ㅡㅡ
		string firstFarmChildPanelName = "FirstFarmChildPanel" + to_string(nameIndex);
		firstFarmChildPanel[i] = new GameObject(firstFarmChildPanelName, OBJECT_TYPE::ADDITINAL);

		ImageRenderer* firstFarmChildPanelRender = new ImageRenderer
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"firstFarmChildPanelRender", L"/Image/corn/panel.png")->GetImage(),
			{ 0.f, 0.f }, { 0.f, 0.f }, { 96.f, 116.f }
		);

		firstFarmChildPanel[i]->AddComponent(firstFarmChildPanelRender);
		firstFarm[i]->AddObjectChild(firstFarmChildPanel[i]);

		firstFarmChildPanel[i]->GetTransform()->SetLocalPosition({ 0.f,0.f });
		firstFarmChildPanel[i]->GetTransform()->SetSize({ 96.f, 116.f });

		firstFarmChildPanel[i]->SetActivate(false);
	}

	// -----------------------------------------------------------------------

	///  밭 2 (상호작용 가능 / ObjectId 6000)  ----=====================================================================
	farmPosX = 1125.f;
	farmPosY = 290.f;

	GameObject* secondFarm[10] = {};
	GameObject* secondFarmChild[10] = {};
	GameObject* secondFarmChildSelect[10] = {};
	GameObject* secondFarmChildFertilizer[10] = {};
	GameObject* secondFarmChildPanel[10] = {};

	for (int i = 1; i < 10; i++)
	{
		string farmName = "SecondFarm" + to_string(i);
		secondFarm[i] = new GameObject(farmName, OBJECT_TYPE::FARM);
		secondFarm[i]->GetTransform()->SetLocalPosition(Vector2(farmPosX, -farmPosY) + m_StartPoint);
		secondFarm[i]->GetTransform()->SetSize({ 125.f, 125.f });

		//Collider* secondFarmColider = new BoxCollider(Vector2{ 125, 125 });
		FarmScript* secondFarmScript = new FarmScript;

		//secondFarm[i]->AddComponent(secondFarmColider);
		secondFarm[i]->AddComponent(secondFarmScript);

		Animator* secondFarmAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"corn", L"/Image/corn/corn_sheet.png")->GetImage());
		secondFarmAnimator->CreateAnimation(L"farmNoSeed", Vector2(0, 0), Vector2(137, 230), Vector2(4, 12), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmSeed", Vector2(0, 0), Vector2(137, 230), Vector2(139, 12), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmFirst", Vector2(0, 0), Vector2(137, 230), Vector2(274, 12), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmSecond", Vector2(0, -3), Vector2(137, 230), Vector2(409, 10), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmThird", Vector2(0, -25), Vector2(137, 198), Vector2(544, 4), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmNoSeedWater", Vector2(0, 0), Vector2(137, 230), Vector2(4, 200), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmSeedWater", Vector2(0, 0), Vector2(137, 230), Vector2(139, 203), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmFirstWater", Vector2(0, 0), Vector2(137, 230), Vector2(274, 203), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmSecondWater", Vector2(0, -3), Vector2(137, 230), Vector2(409, 200), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->CreateAnimation(L"farmThirdWater", Vector2(0, -25), Vector2(137, 198), Vector2(544, 192), Vector2(0, 0), 0.1f, 1);
		secondFarmAnimator->Play(L"farmThirdWater", true);

		secondFarm[i]->AddComponent(secondFarmAnimator);

		AddGameObject(secondFarm[i]);


		// 스크립트 중복 불가로 자식객체에 ObjectDataScript 넣어준다.
		string secondfarmChildName = "SecondFarmChild" + to_string(i);
		secondFarmChild[i] = new GameObject(secondfarmChildName, OBJECT_TYPE::FARM);

		Collider* secondFarmChildCollider = new BoxCollider(Vector2{ 125, 125 });
		ObjectDataScript* secondFarmChildDataScript = new ObjectDataScript(6000);

		secondFarmChild[i]->AddComponent(secondFarmChildCollider);
		secondFarmChild[i]->AddComponent(secondFarmChildDataScript);

		secondFarm[i]->AddObjectChild(secondFarmChild[i]);

		farmPosX -= 145;
		if (i % 3 == 0)
		{
			farmPosX = 1125.f;
			farmPosY -= 145.f;
		}

		int nameIndex = 0;
		switch (i)
		{
		case 1:
			nameIndex = 18;
			secondFarmScript->farmNumber = 18;
			gameManagerScript->m_FarmScripts.insert(make_pair(18, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 2:
			nameIndex = 15;
			secondFarmScript->farmNumber = 15;
			gameManagerScript->m_FarmScripts.insert(make_pair(15, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 3:
			nameIndex = 12;
			secondFarmScript->farmNumber = 12;
			gameManagerScript->m_FarmScripts.insert(make_pair(12, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 4:
			nameIndex = 17;
			secondFarmScript->farmNumber = 17;
			gameManagerScript->m_FarmScripts.insert(make_pair(17, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 5:
			nameIndex = 14;
			secondFarmScript->farmNumber = 14;
			gameManagerScript->m_FarmScripts.insert(make_pair(14, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 6:
			nameIndex = 11;
			secondFarmScript->farmNumber = 11;
			gameManagerScript->m_FarmScripts.insert(make_pair(11, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 7:
			nameIndex = 16;
			secondFarmScript->farmNumber = 16;
			gameManagerScript->m_FarmScripts.insert(make_pair(16, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 8:
			nameIndex = 13;
			secondFarmScript->farmNumber = 13;
			gameManagerScript->m_FarmScripts.insert(make_pair(13, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		case 9:
			nameIndex = 10;
			secondFarmScript->farmNumber = 10;
			gameManagerScript->m_FarmScripts.insert(make_pair(10, dynamic_cast<FarmScript*>(secondFarm[i]->GetComponent<MonoBehaviour>())));
			break;
		}
		// 선택 이미지 ㅡㅡ
		string secondFarmChildSelectName = "SecondFarmChildSelect" + to_string(nameIndex);
		secondFarmChildSelect[i] = new GameObject(secondFarmChildSelectName, OBJECT_TYPE::ADDITINAL);
		ImageRenderer* secondFarmChildSelectRender = new ImageRenderer
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"secondFarmChildSelectRender", L"/Image/corn/Field_A.png")->GetImage(),
			{ 0.f, 0.f }, { 0.f, 0.f }, { 145.f, 145.f }
		);
		secondFarmChildSelect[i]->AddComponent(secondFarmChildSelectRender);
		secondFarm[i]->AddObjectChild(secondFarmChildSelect[i]);

		secondFarmChildSelect[i]->GetTransform()->SetLocalPosition({ 0.f,0.f });
		secondFarmChildSelect[i]->GetTransform()->SetSize({ 145.f, 145.f });

		secondFarmChildSelect[i]->SetActivate(false);

		// 비료 이미지 ㅡㅡ
		string secondFarmChildFertilizerName = "SecondFarmChildFertilizer" + to_string(nameIndex);
		secondFarmChildFertilizer[i] = new GameObject(secondFarmChildFertilizerName, OBJECT_TYPE::ADDITINAL);
		ImageRenderer* secondFarmChildFertilizerRender = new ImageRenderer
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"secondFarmChildFertilizerRender", L"/Image/corn/field_Fertilizer.png")->GetImage(),
			{ 0.f, 0.f }, { 0.f, 0.f }, { 60.f, 45.f }
		);
		secondFarmChildFertilizer[i]->AddComponent(secondFarmChildFertilizerRender);
		secondFarm[i]->AddObjectChild(secondFarmChildFertilizer[i]);

		secondFarmChildFertilizer[i]->GetTransform()->SetLocalPosition({ 0.f,0.f });
		secondFarmChildFertilizer[i]->GetTransform()->SetSize({ 60.f, 45.f });

		secondFarmChildFertilizer[i]->SetActivate(false);
		secondFarmChildFertilizer[i]->GetTransform()->SetLocalPosition({ 0.f, 35.f });

		// 금지 판넬 이미지 ㅡㅡ
		string secondFarmChildPanelName = "SecondFarmChildPanel" + to_string(nameIndex);
		secondFarmChildPanel[i] = new GameObject(secondFarmChildPanelName, OBJECT_TYPE::ADDITINAL);

		ImageRenderer* secondFarmChildPanelRender = new ImageRenderer
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"secondFarmChildPanelRender", L"/Image/corn/panel.png")->GetImage(),
			{ 0.f, 0.f }, { 0.f, 0.f }, { 96.f, 116.f }
		);

		secondFarmChildPanel[i]->AddComponent(secondFarmChildPanelRender);
		secondFarm[i]->AddObjectChild(secondFarmChildPanel[i]);

		secondFarmChildPanel[i]->GetTransform()->SetLocalPosition({ 0.f,0.f });
		secondFarmChildPanel[i]->GetTransform()->SetSize({ 96.f, 116.f });

		secondFarmChildPanel[i]->SetActivate(false);
	}

	// 밭 6000 (ObjectData)
	// 총 밭 3 * 3 * 2 = 18  
	for (int i = 1; i < 10; ++i)
	{
		gameManagerScript->m_QuestManager->m_QuestObjects.push_back(firstFarmChild[i]);
		gameManagerScript->m_QuestManager->m_QuestObjects.push_back(secondFarmChild[i]);
	}

#pragma endregion

#pragma region 플레이어
	/// 플레이어 --------------------------------------------------------------
	GameObject* farmer = new GameObject("farmer", OBJECT_TYPE::PLAYER);

	Collider* farmerCollider = new BoxCollider(Vector2{ 60,35 });
	farmerCollider->SetOffset(Vector2{ 0.f,63.f });
	farmer->AddComponent(farmerCollider);

	Rigidbody* playerBody = new Rigidbody;
	farmer->AddComponent(playerBody);

	Animator* farmerAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"FarmerImage", L"/Image/Animation/farmer/farmer.png")->GetImage());
	farmer->AddComponent(farmerAnimator);
	farmerAnimator->CreateAnimation(L"farmerIdleFront", Vector2(0, 0), Vector2(140, 159), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	farmerAnimator->CreateAnimation(L"farmerIdleLeft", Vector2(0, 0), Vector2(140, 159), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	farmerAnimator->CreateAnimation(L"farmerIdleRight", Vector2(0, 0), Vector2(140, 159), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	farmerAnimator->CreateAnimation(L"farmerIdleBack", Vector2(0, 0), Vector2(140, 159), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	farmerAnimator->CreateAnimation(L"farmerWalkFront", Vector2(0, 0), Vector2(140, 159), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	farmerAnimator->CreateAnimation(L"farmerWalkLeft", Vector2(0, 0), Vector2(140, 159), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	farmerAnimator->CreateAnimation(L"farmerWalkRight", Vector2(0, 0), Vector2(140, 159), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	farmerAnimator->CreateAnimation(L"farmerWalkBack", Vector2(0, 0), Vector2(140, 159), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	farmerAnimator->CreateAnimation(L"farmerHarvest", Vector2(0, 0), Vector2(140, 159), Vector2(0, 1280), Vector2(140, 0), 0.1f, 8);
	farmerAnimator->CreateAnimation(L"farmerWatering", Vector2(0, 0), Vector2(140, 159), Vector2(0, 1440), Vector2(140, 0), 0.1f, 7);
	farmerAnimator->CreateAnimation(L"farmerInteraction", Vector2(0, 0), Vector2(140, 159), Vector2(0, 1600), Vector2(140, 0), 0.1f, 7);
	farmerAnimator->CreateAnimation(L"farmerMoveBodyLeft", Vector2(0, 0), Vector2(244, 159), Vector2(0, 1760), Vector2(244, 0), 0.1f, 5);
	farmerAnimator->CreateAnimation(L"farmerMoveBodyRight", Vector2(0, 0), Vector2(244, 159), Vector2(0, 1920), Vector2(244, 0), 0.1f, 5);
	//farmerAnimator->Play(L"farmerWalkFront", true);

	FarmerScript* farmerScript = new FarmerScript;
	farmer->AddComponent(farmerScript);

	AddGameObject(farmer);

	cameraScript->m_Target = farmer;

	// 플레이어 말풍선
	GameObject* farmerTextBubble = new GameObject("farmerTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* farmerTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble", L"/UI/speechBubble.png")->GetImage());
	farmerTextBubble->AddComponent(farmerTextBubbleAnimator);
	farmerTextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	farmerTextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	farmerTextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	TextRenderer* farmerTextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	farmerTextRenderer->SetTextAlignMiddle();

	farmerTextBubble->AddComponent(farmerTextRenderer);

	farmer->AddObjectChild(farmerTextBubble);
	farmer->GetObjectChild("farmerTextBubble")->SetActivate(false);

	// 플레이어 에임
	GameObject* farmerAim = new GameObject("farmerAim", OBJECT_TYPE::PLAYER_AIM);

	Collider* farmerAimCollider = new BoxCollider(Vector2{ 20.f,20.f });
	farmerAim->AddComponent(farmerAimCollider);
	farmerAimCollider->GetTransform()->SetLocalPosition({ 0.f, 20.f });
	FarmerAim* farmerAimScript = new FarmerAim;
	farmerAim->AddComponent(farmerAimScript);

	farmer->AddObjectChild(farmerAim);

	// 플레이어 옥수수 씨앗 뿌리기 , 옥수수 수확 이펙트
	GameObject* farmerEffect = new GameObject("farmerEffect", OBJECT_TYPE::TEXTBUBBLE);

	Animator* farmerEffectAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"farmerEffect", L"/Image/Animation/dirt_effect.png")->GetImage());
	farmerEffect->AddComponent(farmerEffectAnimator);
	farmerEffectAnimator->CreateAnimation(L"farmerEffectAnimation", Vector2(0, 0), Vector2(210, 116), Vector2(0, 0), Vector2(210, 0), 0.2f, 4);
	//farmerEffectAnimator->Play(L"farmerEffectAnimation", true);
	//farmerEffect->SetActivate(true);

	farmer->AddObjectChild(farmerEffect);

	// 플레이어에 게임 매니저 넣어줌....
	farmerScript->manager = gameManagerScript;
	farmerScript->textManager = textManagerScript;
	farmerScript->m_ScriptMapKey = "Player";

	questManagerScript->m_Player = farmer;

	farmerAimScript->m_GameManagerScript = gameManagerScript;

	// 오브젝트 설명 UI
	ExplainWindow* explainWindow = new ExplainWindow();
	AddGameObject(explainWindow);

#pragma endregion

#pragma region NPC
	/// NPC1 : 빡빡이 할아버지 ------------------------------------------------------------------
	GameObject* NPC1 = new GameObject("npc1", OBJECT_TYPE::NPC);
	NPC1->GetTransform()->SetLocalPosition({ 1100, -940 });
	NPC1->GetTransform()->SetSize({ 140.f, 160.f });


	Collider* NPC1Collider = new BoxCollider(Vector2{ 60, 60 });
	NPC1->AddComponent(NPC1Collider);
	NPC1Collider->SetOffset(Vector2{ 0.f, 50.f });

	Animator* NPC1Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC1Image", L"/Image/Animation/npc/npc_1.png")->GetImage());
	NPC1->AddComponent(NPC1Animator);
	NPC1Animator->CreateAnimation(L"NPCIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"NPCMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC1Animator->Play(L"npcIdleFront", true);

	NPC1Script* npc1Script = new NPC1Script;
	NPC1->AddComponent(npc1Script);

	// NPC1에게 게임 매니저 넣어줌....
	npc1Script->m_NPC1Manager = gameManagerScript;
	npc1Script->m_NPC1TextManager = textManagerScript;
	npc1Script->m_ScriptMapKey = "NPC1";
	npc1Script->patrolPath = 1;
	npc1Script->isDead = false;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_NPC1Script = npc1Script;

	AddGameObject(NPC1);

	////NPC1 시야
	GameObject* NPC1View = new GameObject("NPCView", OBJECT_TYPE::NPCVIEW);

	Collider* NPC1ViewCollider = new BoxCollider(Vector2{ 140, 160 });
	NPC1ViewCollider->SetOffset(Vector2{ 120.f, 20.f });
	NPC1ViewCollider->SetTrigger(true);
	
	NPC1View->AddComponent(NPC1ViewCollider);

	NPC1ViewScript* npc1ViewScript = new NPC1ViewScript;
	NPC1View->AddComponent(npc1ViewScript);

	NPC1->AddObjectChild(NPC1View);

	////NPC1 말풍선
	GameObject* NPC1TextBubble = new GameObject("NPCTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC1TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble", L"/UI/speechBubble.png")->GetImage());

	NPC1TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC1TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC1TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
	NPC1TextBubbleAnimator->CreateAnimation(L"TextBubble2", Vector2(0, -120), Vector2(144, 108), Vector2(0, 352), Vector2(0, 0), 0.2f, 1);
	NPC1TextBubbleAnimator->CreateAnimation(L"TextBubble3", Vector2(0, -120), Vector2(176, 108), Vector2(0, 456), Vector2(0, 0), 0.2f, 1);


	TextRenderer* NPC1TextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	NPC1TextRenderer->SetTextAlignMiddle();

	NPC1TextBubble->AddComponent(NPC1TextBubbleAnimator);
	NPC1TextBubble->AddComponent(NPC1TextRenderer);

	NPC1->AddObjectChild(NPC1TextBubble);
	NPC1->GetObjectChild("NPCTextBubble")->SetActivate(false);


	/// NPC2 양갈래 노란머리 소녀 ------------------------------------------------------
	GameObject* NPC2 = new GameObject("npc2", OBJECT_TYPE::NPC);
	NPC2->GetTransform()->SetLocalPosition({ 1100, -940 });
	NPC2->GetTransform()->SetSize({ 140.f, 160.f });

	Collider* NPC2Collider = new BoxCollider(Vector2{ 60,60 });
	NPC2Collider->SetOffset(Vector2{ 0.f, 50.f });
	NPC2->AddComponent(NPC2Collider);

	Animator* NPC2Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC2Image", L"/Image/Animation/npc/npc_2.png")->GetImage());
	NPC2->AddComponent(NPC2Animator);
	NPC2Animator->CreateAnimation(L"NPCIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPCMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC2Animator->Play(L"NPC2IdleFront", true);

	NPC2Script* npc2Script = new NPC2Script;
	NPC2->AddComponent(npc2Script);

	// NPC2에게 게임 매니저 넣어줌....
	npc2Script->m_NPC2Manager = gameManagerScript;
	npc2Script->m_NPC2TextManager = textManagerScript;
	npc2Script->m_ScriptMapKey = "NPC2";
	npc2Script->startPointCheck = 1;
	npc2Script->isDead = false;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_NPC2Script = npc2Script;

	AddGameObject(NPC2);

	////NPC2 시야
	GameObject* NPC2View = new GameObject("NPCView", OBJECT_TYPE::NPCVIEW);
	//Collider* NPC1ViewCollider = new CircleCollider(100.f);
	Collider* NPC2ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC2ViewCollider->SetTrigger(true);
	NPC2View->AddComponent(NPC2ViewCollider);

	NPC2ViewScript* npc2ViewScript = new NPC2ViewScript;
	NPC2View->AddComponent(npc2ViewScript);

	NPC2->AddObjectChild(NPC2View);
	NPC2ViewCollider->SetOffset(Vector2{ 120.f, 20.f });

	////NPC2 말풍선
	GameObject* NPC2TextBubble = new GameObject("NPCTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC2TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble2", L"/UI/speechBubble.png")->GetImage());
	NPC2TextBubble->AddComponent(NPC2TextBubbleAnimator);
	NPC2TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC2TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC2TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
	NPC2TextBubbleAnimator->CreateAnimation(L"TextBubble3", Vector2(0, -120), Vector2(176, 108), Vector2(0, 456), Vector2(0, 0), 0.2f, 1);
	NPC2TextBubbleAnimator->CreateAnimation(L"TextBubble2", Vector2(0, -120), Vector2(144, 108), Vector2(0, 352), Vector2(0, 0), 0.2f, 1);

	TextRenderer* NPC2TextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	NPC2TextRenderer->SetTextAlignMiddle();

	NPC2TextBubble->AddComponent(NPC2TextRenderer);

	NPC2->AddObjectChild(NPC2TextBubble);
	NPC2->GetObjectChild("NPCTextBubble")->SetActivate(false);

	///NPC3 양갈래 파란머리 소녀 ----------------------------------------------------------
	GameObject* NPC3 = new GameObject("npc3", OBJECT_TYPE::NPC);

	NPC3->GetTransform()->SetLocalPosition({ 1100, -940 });
	NPC3->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC3Collider = new BoxCollider(Vector2{ 60, 60 });
	NPC3Collider->SetOffset(Vector2{ 0.f, 50.f });

	Animator* NPC3Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC3Image", L"/Image/Animation/npc/npc_3.png")->GetImage());
	NPC3Animator->CreateAnimation(L"NPCIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"NPCMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC3Animator->Play(L"npc3IdleFront", true);

	NPC1Script* npc3Script = new NPC1Script;

	// NPC3에게 게임 매니저 넣어줌....
	npc3Script->m_NPC1Manager = gameManagerScript;
	npc3Script->m_NPC1TextManager = textManagerScript;
	npc3Script->m_ScriptMapKey = "NPC3";
	npc3Script->patrolPath = 3;
	npc3Script->isDead = true;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_NPC3Script = npc3Script;

	NPC3->AddComponent(NPC3Animator);
	NPC3->AddComponent(npc3Script);
	NPC3->AddComponent(NPC3Collider);
	AddGameObject(NPC3);

	////NPC3 시야
	GameObject* NPC3View = new GameObject("NPCView", OBJECT_TYPE::NPCVIEW);
	Collider* NPC3ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC3ViewCollider->SetTrigger(true);
	NPC3View->AddComponent(NPC3ViewCollider);

	NPC1ViewScript* npc3ViewScript = new NPC1ViewScript;
	NPC3View->AddComponent(npc3ViewScript);

	NPC3->AddObjectChild(NPC3View);
	NPC3ViewCollider->SetOffset(Vector2{ 120.f, 20.f });

	//NPC3 말풍선
	GameObject* NPC3TextBubble = new GameObject("NPCTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC3TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble3", L"/UI/speechBubble.png")->GetImage());
	NPC3TextBubble->AddComponent(NPC3TextBubbleAnimator);
	NPC3TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC3TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC3TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
	NPC3TextBubbleAnimator->CreateAnimation(L"TextBubble2", Vector2(0, -120), Vector2(144, 108), Vector2(0, 352), Vector2(0, 0), 0.2f, 1);
	NPC3TextBubbleAnimator->CreateAnimation(L"TextBubble3", Vector2(0, -120), Vector2(176, 108), Vector2(0, 456), Vector2(0, 0), 0.2f, 1);

	TextRenderer* NPC3TextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	NPC3TextRenderer->SetTextAlignMiddle();

	NPC3TextBubble->AddComponent(NPC3TextRenderer);

	NPC3->AddObjectChild(NPC3TextBubble);
	NPC3->GetObjectChild("NPCTextBubble")->SetActivate(false);

	///NPC4 공룡소년 ----------------------------------------------------------
	GameObject* NPC4 = new GameObject("npc4", OBJECT_TYPE::NPC);

	NPC4->GetTransform()->SetLocalPosition({ 1300, 1600 });
	NPC4->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC4Collider = new BoxCollider(Vector2{ 60, 60 });
	NPC4Collider->SetOffset(Vector2{ 0.f, 50.f });

	Animator* NPC4Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC4Image", L"/Image/Animation/npc/npc_4.png")->GetImage());
	NPC4Animator->CreateAnimation(L"NPCIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"NPCMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC4Animator->Play(L"npc4IdleFront", true);

	NPC1Script* npc4Script = new NPC1Script;

	// NPC4에게 게임 매니저 넣어줌....
	npc4Script->m_NPC1Manager = gameManagerScript;
	npc4Script->m_NPC1TextManager = textManagerScript;
	npc4Script->m_ScriptMapKey = "NPC4";
	npc4Script->patrolPath = 4;
	npc4Script->isDead = true;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_NPC4Script = npc4Script;

	NPC4->AddComponent(NPC4Animator);
	NPC4->AddComponent(npc4Script);
	NPC4->AddComponent(NPC4Collider);
	AddGameObject(NPC4);

	////NPC4 시야
	GameObject* NPC4View = new GameObject("NPCView", OBJECT_TYPE::NPCVIEW);
	Collider* NPC4ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC4ViewCollider->SetTrigger(true);
	NPC4View->AddComponent(NPC4ViewCollider);

	NPC1ViewScript* npc4ViewScript = new NPC1ViewScript;
	NPC4View->AddComponent(npc4ViewScript);

	NPC4->AddObjectChild(NPC4View);
	NPC4ViewCollider->SetOffset(Vector2{ 120.f, 20.f });

	//NPC4 말풍선
	GameObject* NPC4TextBubble = new GameObject("NPCTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC4TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble4", L"/UI/speechBubble.png")->GetImage());
	NPC4TextBubble->AddComponent(NPC4TextBubbleAnimator);
	NPC4TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC4TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC4TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
	NPC4TextBubbleAnimator->CreateAnimation(L"TextBubble2", Vector2(0, -120), Vector2(144, 108), Vector2(0, 352), Vector2(0, 0), 0.2f, 1);
	NPC4TextBubbleAnimator->CreateAnimation(L"TextBubble3", Vector2(0, -120), Vector2(176, 108), Vector2(0, 456), Vector2(0, 0), 0.2f, 1);

	TextRenderer* NPC4TextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	NPC4TextRenderer->SetTextAlignMiddle();

	NPC4TextBubble->AddComponent(NPC4TextRenderer);

	NPC4->AddObjectChild(NPC4TextBubble);
	NPC4->GetObjectChild("NPCTextBubble")->SetActivate(false);

	///NPC5 사이비 ----------------------------------------------------------
	GameObject* NPC5 = new GameObject("npc5", OBJECT_TYPE::NPC);

	NPC5->GetTransform()->SetLocalPosition({ 1300, 1600 });
	NPC5->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC5Collider = new BoxCollider(Vector2{ 60, 60 });
	NPC5Collider->SetOffset(Vector2{ 0.f, 50.f });

	Animator* NPC5Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC5Image", L"/Image/Animation/npc/npc_5.png")->GetImage());
	NPC5Animator->CreateAnimation(L"NPCIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"NPCMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC4Animator->Play(L"npc4IdleFront", true);

	NPC1Script* npc5Script = new NPC1Script;

	// NPC5에게 게임 매니저 넣어줌....
	npc5Script->m_NPC1Manager = gameManagerScript;
	npc5Script->m_NPC1TextManager = textManagerScript;
	npc5Script->m_ScriptMapKey = "NPC5";
	npc5Script->patrolPath = 2;
	npc5Script->isDead = false;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_NPC5Script = npc5Script;

	NPC5->AddComponent(NPC5Animator);
	NPC5->AddComponent(npc5Script);
	NPC5->AddComponent(NPC5Collider);
	AddGameObject(NPC5);

	////NPC5 시야
	GameObject* NPC5View = new GameObject("NPCView", OBJECT_TYPE::NPCVIEW);
	Collider* NPC5ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC5ViewCollider->SetTrigger(true);
	NPC5View->AddComponent(NPC5ViewCollider);

	NPC1ViewScript* npc5ViewScript = new NPC1ViewScript;
	NPC5View->AddComponent(npc5ViewScript);

	NPC5->AddObjectChild(NPC5View);
	NPC5ViewCollider->SetOffset(Vector2{ 120.f, 20.f });

	//NPC5 말풍선
	GameObject* NPC5TextBubble = new GameObject("NPCTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC5TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble5", L"/UI/speechBubble.png")->GetImage());
	NPC5TextBubble->AddComponent(NPC5TextBubbleAnimator);
	NPC5TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC5TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC5TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
	NPC5TextBubbleAnimator->CreateAnimation(L"TextBubble2", Vector2(0, -120), Vector2(144, 108), Vector2(0, 352), Vector2(0, 0), 0.2f, 1);
	NPC5TextBubbleAnimator->CreateAnimation(L"TextBubble3", Vector2(0, -120), Vector2(176, 108), Vector2(0, 456), Vector2(0, 0), 0.2f, 1);

	TextRenderer* NPC5TextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	NPC5TextRenderer->SetTextAlignMiddle();

	NPC5TextBubble->AddComponent(NPC5TextRenderer);

	NPC5->AddObjectChild(NPC5TextBubble);
	NPC5->GetObjectChild("NPCTextBubble")->SetActivate(false);

	///NPC6 빨간머리앤 ----------------------------------------------------------
	GameObject* NPC6 = new GameObject("npc6", OBJECT_TYPE::NPC);

	NPC6->GetTransform()->SetLocalPosition({ 1300, 1600 });
	NPC6->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC6Collider = new BoxCollider(Vector2{ 60, 60 });
	NPC6Collider->SetOffset(Vector2{ 0.f, 50.f });

	Animator* NPC6Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC6Image", L"/Image/Animation/npc/npc_6.png")->GetImage());
	NPC6Animator->CreateAnimation(L"NPCIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"NPCMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC4Animator->Play(L"npc4IdleFront", true);

	NPC2Script* npc6Script = new NPC2Script;

	// NPC6에게 게임 매니저 넣어줌....
	npc6Script->m_NPC2Manager = gameManagerScript;
	npc6Script->m_NPC2TextManager = textManagerScript;
	npc6Script->m_ScriptMapKey = "NPC6";
	npc6Script->startPointCheck = 2;
	npc6Script->isDead = false;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_NPC6Script = npc6Script;

	NPC6->AddComponent(NPC6Animator);
	NPC6->AddComponent(npc6Script);
	NPC6->AddComponent(NPC6Collider);
	AddGameObject(NPC6);

	////NPC6 시야
	GameObject* NPC6View = new GameObject("NPCView", OBJECT_TYPE::NPCVIEW);
	Collider* NPC6ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC6ViewCollider->SetTrigger(true);
	NPC6View->AddComponent(NPC6ViewCollider);

	NPC2ViewScript* npc6ViewScript = new NPC2ViewScript;
	NPC6View->AddComponent(npc6ViewScript);

	NPC6->AddObjectChild(NPC6View);
	NPC6ViewCollider->SetOffset(Vector2{ 120.f, 20.f });

	//NPC6 말풍선
	GameObject* NPC6TextBubble = new GameObject("NPCTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC6TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble6", L"/UI/speechBubble.png")->GetImage());
	NPC6TextBubble->AddComponent(NPC6TextBubbleAnimator);
	NPC6TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC6TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC6TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
	NPC6TextBubbleAnimator->CreateAnimation(L"TextBubble2", Vector2(0, -120), Vector2(144, 108), Vector2(0, 352), Vector2(0, 0), 0.2f, 1);
	NPC6TextBubbleAnimator->CreateAnimation(L"TextBubble3", Vector2(0, -120), Vector2(176, 108), Vector2(0, 456), Vector2(0, 0), 0.2f, 1);

	TextRenderer* NPC6TextRenderer = new TextRenderer(
		Vector2(0.f, -150.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	NPC6TextRenderer->SetTextAlignMiddle();

	NPC6TextBubble->AddComponent(NPC6TextRenderer);

	NPC6->AddObjectChild(NPC6TextBubble);
	NPC6->GetObjectChild("NPCTextBubble")->SetActivate(false);

#pragma endregion

#pragma region 경찰
	///Police1 -----------------------------------------------------------------------
	GameObject* police1 = new GameObject("police1", OBJECT_TYPE::NPC);


	police1->GetTransform()->SetLocalPosition(Vector2(1100, -740));
	police1->GetTransform()->SetSize({ 140.f, 160.f });

	Collider* police1Collider = new BoxCollider(Vector2{ 60, 60 });
	police1Collider->SetOffset(Vector2{ 0.f, 50.f });
	police1->AddComponent(police1Collider);

	Animator* police1Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Police1", L"/Image/Animation/police/police_1.png")->GetImage());
	police1->AddComponent(police1Animator);
	police1Animator->CreateAnimation(L"PoliceIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.2f, 4);
	police1Animator->CreateAnimation(L"PoliceFind", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.2f, 4);

	PoliceScript* police1Script = new PoliceScript;
	police1->AddComponent(police1Script);

	// 경찰에게 게임 매니저 넣어줌....
	police1Script->m_Policemanager = gameManagerScript;
	police1Script->m_PoliceTextManager = textManagerScript;
	police1Script->m_ScriptMapKey = "Police";
	police1Script->isDead = true;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_Police1Script = police1Script;

	AddGameObject(police1);

	////Police1 시야
	GameObject* police1View = new GameObject("police1View", OBJECT_TYPE::POLICEVIEW);
	police1View->GetTransform()->SetSize(Vector2(140.f, 480.f));

	Collider* police1ViewCollider = new BoxCollider(Vector2{ 110.f, 460.f });
	police1ViewCollider->SetOffset(Vector2{ 0.f, 200.f });
	police1ViewCollider->SetTrigger(true);
	police1View->AddComponent(police1ViewCollider);

	ImageRenderer* policeViewRender = new ImageRenderer(ResourceManager::GetInstance()->LoadResource<Image>(L"View", L"/Image/UI/eye_box.png")->GetImage(),
		{ 0.f, 200.f }, { 0.f, 0.f }, { 140.f, 480.f });
	police1View->AddComponent(policeViewRender);

	PoliceViewScript* police1ViewScript = new PoliceViewScript;
	police1View->AddComponent(police1ViewScript);

	police1->AddObjectChild(police1View);

	//Police1 말풍선
	GameObject* police1TextBubble = new GameObject("police1TextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* police1TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubblePolice", L"/UI/speechBubble.png")->GetImage());
	police1TextBubble->AddComponent(police1TextBubbleAnimator);
	police1TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	police1TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	police1TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	TextRenderer* PoliceTextRenderer = new TextRenderer(
		Vector2(0.f, -90.f),
		L" ",
		ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48", L"/Font/DNFBitBitTTF.ttf", L"던파 비트비트체 TTF", 10.f)->Getfont()
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	PoliceTextRenderer->SetTextAlignMiddle();
	police1TextBubble->AddComponent(PoliceTextRenderer);

	police1->AddObjectChild(police1TextBubble);
	police1->GetObjectChild("police1TextBubble")->SetActivate(false);

	///Police2 -----------------------------------------------------------------------
	GameObject* police2 = new GameObject("police2", OBJECT_TYPE::NPC);


	police2->GetTransform()->SetLocalPosition(Vector2(1600, 1600));
	police2->GetTransform()->SetSize({ 140.f, 160.f });

	Collider* police2Collider = new BoxCollider(Vector2{ 60, 60 });
	police2Collider->SetOffset(Vector2{ 0.f, 50.f });
	police2->AddComponent(police2Collider);

	Animator* police2Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Police2", L"/Image/Animation/police/police_2.png")->GetImage());
	police2->AddComponent(police2Animator);
	police2Animator->CreateAnimation(L"PoliceIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.2f, 4);
	police2Animator->CreateAnimation(L"PoliceFind", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.2f, 4);

	PoliceScript* police2Script = new PoliceScript;
	police2->AddComponent(police2Script);

	// 경찰에게 게임 매니저 넣어줌....
	police2Script->m_Policemanager = gameManagerScript;
	police2Script->m_PoliceTextManager = textManagerScript;
	police2Script->m_ScriptMapKey = "Police";
	police2Script->isDead = true;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_Police2Script = police2Script;

	AddGameObject(police2);

	////Police2 시야
	GameObject* police2View = new GameObject("police1View", OBJECT_TYPE::POLICEVIEW);
	police2View->GetTransform()->SetSize(Vector2(140.f, 480.f));

	Collider* police2ViewCollider = new BoxCollider(Vector2{ 110.f, 460.f });
	police2ViewCollider->SetOffset(Vector2{ 0.f, 200.f });
	police2ViewCollider->SetTrigger(true);
	police2View->AddComponent(police2ViewCollider);

	ImageRenderer* police2ViewRender = new ImageRenderer(ResourceManager::GetInstance()->LoadResource<Image>(L"View", L"/Image/UI/eye_box.png")->GetImage(),
		{ 0.f, 200.f }, { 0.f, 0.f }, { 140.f, 480.f });
	police2View->AddComponent(police2ViewRender);

	PoliceViewScript* police2ViewScript = new PoliceViewScript;
	police2View->AddComponent(police2ViewScript);

	police2->AddObjectChild(police2View);

	//Police2 말풍선
	GameObject* police2TextBubble = new GameObject("police1TextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* police2TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubblePolice", L"/UI/speechBubble.png")->GetImage());
	police2TextBubble->AddComponent(police2TextBubbleAnimator);
	police2TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	police2TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	police2TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	police2->AddObjectChild(police2TextBubble);
	police2->GetObjectChild("police1TextBubble")->SetActivate(false);


	///Police3 ----------------------------------------------------------------------- 순찰
	GameObject* police3 = new GameObject("police3", OBJECT_TYPE::NPC);

	police3->GetTransform()->SetSize({ 140.f, 160.f });

	Collider* police3Collider = new BoxCollider(Vector2{ 60, 60 });
	police3Collider->SetOffset(Vector2{ 0.f, 50.f });
	police3->AddComponent(police3Collider);

	Animator* police3Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Police", L"/Image/Animation/police/police_1.png")->GetImage());
	police3->AddComponent(police3Animator);
	police3Animator->CreateAnimation(L"PoliceIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.2f, 4);
	police3Animator->CreateAnimation(L"PoliceFind", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.2f, 4);


	Police2Script* police3Script = new Police2Script;
	police3->AddComponent(police3Script);

	// 경찰에게 게임 매니저 넣어줌....
	police3Script->m_Policemanager = gameManagerScript;
	police3Script->m_PoliceTextManager = textManagerScript;
	police3Script->m_ScriptMapKey = "Police";
	police3Script->patrolPath = 1;
	police3Script->isDead = false;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_Police3Script = police3Script;

	AddGameObject(police3);

	////Police3 시야
	GameObject* police3View = new GameObject("police1View", OBJECT_TYPE::POLICEVIEW);
	police3View->GetTransform()->SetSize(Vector2(140.f, 480.f));

	Collider* police3ViewCollider = new BoxCollider(Vector2{ 110.f, 460.f });
	police3ViewCollider->SetOffset(Vector2{ 0.f, 200.f });
	police3ViewCollider->SetTrigger(true);
	police3View->AddComponent(police3ViewCollider);


	ImageRenderer* police3ViewRender = new ImageRenderer(ResourceManager::GetInstance()->LoadResource<Image>(L"View3", L"/Image/UI/eye_box.png")->GetImage(),
		{ 0.f, 200.f }, { 0.f, 0.f }, { 140.f, 480.f });
	police3View->AddComponent(police3ViewRender);

	Police2ViewScript* police3ViewScript = new Police2ViewScript;
	police3View->AddComponent(police3ViewScript);

	police3->AddObjectChild(police3View);

	//Police3 말풍선
	GameObject* police3TextBubble = new GameObject("police1TextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* police3TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubblePolice", L"/UI/speechBubble.png")->GetImage());
	police3TextBubble->AddComponent(police3TextBubbleAnimator);
	police3TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	police3TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	police3TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	police3->AddObjectChild(police3TextBubble);
	police3->GetObjectChild("police1TextBubble")->SetActivate(false);

	///Police4 ----------------------------------------------------------------------- 순찰
	GameObject* police4 = new GameObject("police4", OBJECT_TYPE::NPC);

	police4->GetTransform()->SetSize({ 140.f, 160.f });

	Collider* police4Collider = new BoxCollider(Vector2{ 60, 60 });
	police4Collider->SetOffset(Vector2{ 0.f, 50.f });
	police4->AddComponent(police4Collider);

	Animator* police4Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Police4", L"/Image/Animation/police/police_2.png")->GetImage());
	police4->AddComponent(police4Animator);
	police4Animator->CreateAnimation(L"PoliceIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.2f, 4);
	police4Animator->CreateAnimation(L"PoliceFind", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.2f, 4);

	Police2Script* police4Script = new Police2Script;
	police4->AddComponent(police4Script);

	// 경찰에게 게임 매니저 넣어줌....
	police4Script->m_Policemanager = gameManagerScript;
	police4Script->m_PoliceTextManager = textManagerScript;
	police4Script->m_ScriptMapKey = "Police";
	police4Script->patrolPath = 2;
	police4Script->isDead = true;

	//게임 메니저에 스크립트 넣어쥼..
	gameManagerScript->m_Police4Script = police4Script;

	AddGameObject(police4);

	//Police4 시야
	GameObject* police4View = new GameObject("police1View", OBJECT_TYPE::POLICEVIEW);
	police4View->GetTransform()->SetSize(Vector2(140.f, 480.f));

	Collider* police4ViewCollider = new BoxCollider(Vector2{ 110.f, 460.f });
	police4ViewCollider->SetOffset(Vector2{ 0.f, 200.f });
	police4ViewCollider->SetTrigger(true);
	police4View->AddComponent(police4ViewCollider);

	ImageRenderer* police4ViewRender = new ImageRenderer(ResourceManager::GetInstance()->LoadResource<Image>(L"View4", L"/Image/UI/eye_box.png")->GetImage(),
		{ 0.f, 200.f }, { 0.f, 0.f }, { 140.f, 480.f });
	police4View->AddComponent(police4ViewRender);

	Police2ViewScript* police4ViewScript = new Police2ViewScript;
	police4View->AddComponent(police4ViewScript);

	police4->AddObjectChild(police4View);

	//Police4 말풍선
	GameObject* police4TextBubble = new GameObject("police1TextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* police4TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubblePolice4", L"/UI/speechBubble.png")->GetImage());
	police4TextBubble->AddComponent(police4TextBubbleAnimator);
	police4TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	police4TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	police4TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	police4->AddObjectChild(police4TextBubble);
	police4->GetObjectChild("police1TextBubble")->SetActivate(false);

#pragma endregion

#pragma region 바운더리왼쪽
	/// BOUNDARY 6시부터 시계방향으로 나무오브젝트타입처리
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;
		boundaryCollider->AddVertice({ 900, 2355 });
		boundaryCollider->AddVertice({ 1500, 2400 });
		boundaryCollider->AddVertice({ 1610, 2470 });
		boundaryCollider->AddVertice({ 1777, 2704 });
		boundaryCollider->AddVertice({ 900, 2704 });
		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;
		boundaryCollider->AddVertice({ 495, 2230 });
		boundaryCollider->AddVertice({ 690, 2235 });
		boundaryCollider->AddVertice({ 900, 2355 });
		boundaryCollider->AddVertice({ 900, 2704 });
		boundaryCollider->AddVertice({ 495, 2704 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;
		boundaryCollider->AddVertice({ 0, 2704 });
		boundaryCollider->AddVertice({ 0, 1810 });
		boundaryCollider->AddVertice({ 175, 1810 });
		boundaryCollider->AddVertice({ 495, 2230 });
		boundaryCollider->AddVertice({ 495, 2704 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 0, 1810 });
		boundaryCollider->AddVertice({ 175, 1810 });
		boundaryCollider->AddVertice({ 242, 1730 });
		boundaryCollider->AddVertice({ 0, 1730 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 0, 1367 });
		boundaryCollider->AddVertice({ 284, 1367 });
		boundaryCollider->AddVertice({ 444, 1453 });
		boundaryCollider->AddVertice({ 525, 1633 });
		boundaryCollider->AddVertice({ 465, 1720 });
		boundaryCollider->AddVertice({ 242, 1730 });
		boundaryCollider->AddVertice({ 0, 1730 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 0, 1367 });
		boundaryCollider->AddVertice({ 284, 1367 });
		boundaryCollider->AddVertice({ 391, 1125 });
		boundaryCollider->AddVertice({ 324, 954 });
		boundaryCollider->AddVertice({ 0, 954 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 0, 432 });
		boundaryCollider->AddVertice({ 294, 432 });
		boundaryCollider->AddVertice({ 394, 741 });
		boundaryCollider->AddVertice({ 324, 954 });
		boundaryCollider->AddVertice({ 0, 954 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 0, 432 });
		boundaryCollider->AddVertice({ 294, 432 });
		boundaryCollider->AddVertice({ 444, 344 });
		boundaryCollider->AddVertice({ 444, 0 });
		boundaryCollider->AddVertice({ 0, 0 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 1300, 0 });
		boundaryCollider->AddVertice({ 893, 375 });
		boundaryCollider->AddVertice({ 444, 344 });
		boundaryCollider->AddVertice({ 444, 0 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
#pragma endregion

#pragma region 바운더리12시
	/// BOUNDARY 6시부터 시계방향으로 나무오브젝트타입처리
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;
		boundaryCollider->AddVertice({ 1445, 0 });
		boundaryCollider->AddVertice({ 1540, 190 });
		boundaryCollider->AddVertice({ 1710, 211 });
		boundaryCollider->AddVertice({ 1710, 0 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 1710, 0 });
		boundaryCollider->AddVertice({ 1710, 211 });
		boundaryCollider->AddVertice({ 1786, 277 });
		boundaryCollider->AddVertice({ 2124, 281 });
		boundaryCollider->AddVertice({ 2214, 150 });
		boundaryCollider->AddVertice({ 2224, 59 });
		boundaryCollider->AddVertice({ 2181, 0 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
#pragma endregion
	
#pragma region 바운더리1시

	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 4800, 1000 });
		boundaryCollider->AddVertice({ 4716, 1000 });
		boundaryCollider->AddVertice({ 4648, 932 });
		boundaryCollider->AddVertice({ 4627, 868 });
		boundaryCollider->AddVertice({ 4800, 868 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;


		boundaryCollider->AddVertice({ 4800, 868 });
		boundaryCollider->AddVertice({ 4627, 868 });
		boundaryCollider->AddVertice({ 4475, 863 });
		boundaryCollider->AddVertice({ 4395, 803 });
		boundaryCollider->AddVertice({ 4395, 701 });
		boundaryCollider->AddVertice({ 4515, 505 });
		boundaryCollider->AddVertice({ 4800, 505 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;



		boundaryCollider->AddVertice({ 4800, 505 });
		boundaryCollider->AddVertice({ 4515, 505 });
		boundaryCollider->AddVertice({ 4414, 292 });
		boundaryCollider->AddVertice({ 4414, 0 });
		boundaryCollider->AddVertice({ 4800, 0 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;




		boundaryCollider->AddVertice({ 4414, 0 });
		boundaryCollider->AddVertice({ 4414, 292 });
		boundaryCollider->AddVertice({ 4359, 350 });
		boundaryCollider->AddVertice({ 4155, 355 });
		boundaryCollider->AddVertice({ 4155, 0 });



		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;


		boundaryCollider->AddVertice({ 4155, 0 });
		boundaryCollider->AddVertice({ 4155, 355 });
		boundaryCollider->AddVertice({ 4100, 395 });
		boundaryCollider->AddVertice({ 4100, 395 });
		boundaryCollider->AddVertice({ 3907, 395 });
		boundaryCollider->AddVertice({ 3838, 353 });
		boundaryCollider->AddVertice({ 3866, 106 });
		boundaryCollider->AddVertice({ 3943, 0 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;



		boundaryCollider->AddVertice({ 3943, 0 });
		boundaryCollider->AddVertice({ 3866, 106 });
		boundaryCollider->AddVertice({ 3787, 100 });
		boundaryCollider->AddVertice({ 3722, 0 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
#pragma endregion

#pragma region 바운더리5시

	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;

		boundaryCollider->AddVertice({ 4800, 1855 });
		boundaryCollider->AddVertice({ 3980, 1925 });
		boundaryCollider->AddVertice({ 3917, 1995 });
		boundaryCollider->AddVertice({ 3835, 2148 });
		boundaryCollider->AddVertice({ 3795, 2327 });
		boundaryCollider->AddVertice({ 4800, 2327 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition({ -1440.f, -812 });
		PolygonCollider* boundaryCollider = new PolygonCollider;


		boundaryCollider->AddVertice({ 4800, 2327 });
		boundaryCollider->AddVertice({ 3795, 2327 });
		boundaryCollider->AddVertice({ 3513, 2384 });
		boundaryCollider->AddVertice({ 3410, 2425 });
		boundaryCollider->AddVertice({ 3294, 2704 });
		boundaryCollider->AddVertice({ 4800, 2704 });


		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	
#pragma endregion

#pragma region 외곽

	{
		// 위
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition(m_StartPoint + Vector2{0, -1402});
		BoxCollider* boundaryCollider = new BoxCollider({4800, 100});

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
	{
		//아래
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition(m_StartPoint + Vector2{ 0, 1402 });
		BoxCollider* boundaryCollider = new BoxCollider({ 4800, 100 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}

	{
		//오른쪽
		GameObject* boundary = new GameObject("Boundary1", OBJECT_TYPE::TREE);
		boundary->GetTransform()->SetLocalPosition(m_StartPoint + Vector2{ 2450, 0 });
		BoxCollider* boundaryCollider = new BoxCollider({ 100, 2704 });

		boundary->AddComponent(boundaryCollider);
		AddGameObject(boundary);
	}
#pragma endregion

	GameObject* bubblePopUI = new GameObject("BubblePopUI", OBJECT_TYPE::UI);
	BubblePopScript* bubblePopScript = new BubblePopScript;
	bubblePopScript->m_NPCBubble.push_back(NPC1TextBubbleAnimator);
	bubblePopScript->m_NPCBubble.push_back(NPC2TextBubbleAnimator);
	bubblePopScript->m_NPCBubble.push_back(NPC3TextBubbleAnimator);
	bubblePopScript->m_NPCBubble.push_back(NPC4TextBubbleAnimator);
	bubblePopScript->m_NPCBubble.push_back(NPC5TextBubbleAnimator);
	bubblePopScript->m_NPCBubble.push_back(NPC6TextBubbleAnimator);
	bubblePopScript->m_Camera = camera;
	bubblePopUI->AddComponent(bubblePopScript);
	AddGameObject(bubblePopUI);

	for (int i = 0; i < (int)bubblePopScript->m_NPCBubble.size(); ++i)
	{
		GameObject* bubblePopChildUI = new GameObject("BubblePopUI", OBJECT_TYPE::UI);
		Animator* bubbleAnim = new Animator(
			ResourceManager::GetInstance()->LoadResource<Image>(L"QU_mark", L"/Image/UI/QU_mark.png")->GetImage());
		bubblePopScript->m_BubbleUI.push_back(bubbleAnim);
		bubblePopChildUI->AddComponent(bubbleAnim);
		bubblePopUI->AddObjectChild(bubblePopChildUI);
	}

	


	/// 창도 스크립트 / 모든 치트키를 관리한다. :)
	GameObject* cdTest = new GameObject("ddd", OBJECT_TYPE::BUILDING);
	ChangdoScript* cdTestscript = new ChangdoScript;
	cdTest->AddComponent(cdTestscript);
	AddGameObject(cdTest);

	cdTestscript->m_GameManagerScript = gameManagerScript;

	/// Fade In Out
	BlackScreen* blackScreen = new BlackScreen();
	AddGameObject(blackScreen);
	gameManagerScript->m_BlackScreenScript = blackScreen->m_BlackScreenScript;
}