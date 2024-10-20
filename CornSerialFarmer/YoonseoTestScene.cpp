#include "YoonseoTestScene.h"

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

// Manager
#include "EventManager.h"
#include "ResourceManager.h"

// Prefab
#include "PauseButton.h"
#include "TimeBar.h"
#include "ItemSlot.h"
#include "QuestList.h"

// Script
#include "GameManagerScript.h"
#include "FarmerScript.h"
#include "ObjectDataScript.h"

void YoonseoTestScene::Enter()
{
	Vector2 m_StartPoint{ 960.f, 540.f };
	Vector2 m_CorrectionVector{ 470.f, 402.f };

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

	/// Game Manager ---------------------------------------------------------
	GameObject* gameManager = new GameObject("GameManager", OBJECT_TYPE::DEFAULT);
	gameManager->SetScene(this);
	GameManagerScript* gameManagerScript = new GameManagerScript();
	gameManager->AddComponent(gameManagerScript);

	/// 플레이어 --------------------------------------------------------------
	GameObject* farmer = new GameObject("farmer", OBJECT_TYPE::PLAYER);
	Collider* farmerCollider = new BoxCollider(Vector2{ 60,120 });
	farmerCollider->SetOffset(Vector2{ 0.f,20.f });
	farmer->AddComponent(farmerCollider);
	PrimitiveRenderer* farmerRenderer = new PrimitiveRenderer;

	Animator* animator2 = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"FarmerImage", L"/Image/Animation/farmer/farmer.png")->GetImage());
	farmer->AddComponent(animator2);
	animator2->CreateAnimation(L"farmerIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	animator2->CreateAnimation(L"farmerIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	animator2->CreateAnimation(L"farmerIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	animator2->CreateAnimation(L"farmerIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	animator2->CreateAnimation(L"farmerWalkFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	animator2->CreateAnimation(L"farmerWalkLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	animator2->CreateAnimation(L"farmerWalkRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	animator2->CreateAnimation(L"farmerWalkBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	animator2->CreateAnimation(L"farmerHarvest", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.1f, 8);
	animator2->CreateAnimation(L"farmerWatering", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1440), Vector2(140, 0), 0.1f, 7);
	animator2->CreateAnimation(L"farmerInterection", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1600), Vector2(140, 0), 0.1f, 7);
	animator2->CreateAnimation(L"farmerMoveBodyLeft", Vector2(0, 0), Vector2(244, 160), Vector2(0, 1760), Vector2(244, 0), 0.1f, 5);
	animator2->CreateAnimation(L"farmerMoveBodyRight", Vector2(0, 0), Vector2(244, 160), Vector2(0, 1920), Vector2(244, 0), 0.1f, 5);
	//animator2->Play(L"farmerWalkFront", true);

	FarmerScript* farmerScript = new FarmerScript;
	farmer->AddComponent(farmerScript);
	AddGameObject(farmer);

	// 플레이어 말풍선
	GameObject* farmerTextBubble = new GameObject("farmerTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* farmerTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble", L"/UI/speechBubble.png")->GetImage());
	farmerTextBubble->AddComponent(farmerTextBubbleAnimator);
	farmerTextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	farmerTextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	farmerTextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	farmer->AddObjectChild(farmerTextBubble);
	farmer->GetObjectChild("farmerTextBubble")->SetActivate(false);

	cameraScript->m_Target = farmer;
	farmerScript->manager = gameManagerScript;

	/// NPC3 
	GameObject* NPC3 = new GameObject("npc3", OBJECT_TYPE::NPC);
	NPC3->GetTransform()->SetLocalPosition(Vector2(-1000, -300) + m_StartPoint);
	NPC3->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC3Collider = new BoxCollider(Vector2{ 60, 120 });
	NPC3Collider->SetOffset(Vector2{ 0.f, 20.f });

	Animator* NPC3Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC3Image", L"/Image/Animation/npc/npc_3.png")->GetImage());
	NPC3Animator->CreateAnimation(L"npc3IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3MoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3MoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3MoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->CreateAnimation(L"npc3MoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	NPC3Animator->Play(L"npc3IdleFront", true);

	NPC3->AddComponent(NPC3Animator);
	NPC3->AddComponent(NPC3Collider);

	AddGameObject(NPC3);

	/// NPC4
	GameObject* NPC4 = new GameObject("npc4", OBJECT_TYPE::NPC);
	NPC4->GetTransform()->SetLocalPosition(Vector2(-800, -300) + m_StartPoint);
	NPC4->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC4Collider = new BoxCollider(Vector2{ 60, 120 });
	NPC4Collider->SetOffset(Vector2{ 0.f, 20.f });

	Animator* NPC4Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC4Image", L"/Image/Animation/npc/npc_4.png")->GetImage());
	NPC4Animator->CreateAnimation(L"npc4IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4MoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4MoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4MoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->CreateAnimation(L"npc4MoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	NPC4Animator->Play(L"npc4IdleFront", true);

	NPC4->AddComponent(NPC4Animator);
	NPC4->AddComponent(NPC4Collider);

	AddGameObject(NPC4);

	/// NPC5
	GameObject* NPC5 = new GameObject("npc5", OBJECT_TYPE::NPC);
	NPC5->GetTransform()->SetLocalPosition(Vector2(-600, -300) + m_StartPoint);
	NPC5->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC5Collider = new BoxCollider(Vector2{ 60, 120 });
	NPC5Collider->SetOffset(Vector2{ 0.f, 20.f });

	Animator* NPC5Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC5Image", L"/Image/Animation/npc/npc_5.png")->GetImage());
	NPC5Animator->CreateAnimation(L"npc5IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5MoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5MoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5MoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->CreateAnimation(L"npc5MoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	NPC5Animator->Play(L"npc5IdleFront", true);

	NPC5->AddComponent(NPC5Animator);
	NPC5->AddComponent(NPC5Collider);

	AddGameObject(NPC5);

	/// NPC6
	GameObject* NPC6 = new GameObject("npc6", OBJECT_TYPE::NPC);
	NPC6->GetTransform()->SetLocalPosition(Vector2(-400, -300) + m_StartPoint);
	NPC6->GetTransform()->SetSize({ 60.f, 120.f });

	Collider* NPC6Collider = new BoxCollider(Vector2{ 60, 120 });
	NPC6Collider->SetOffset(Vector2{ 0.f, 20.f });

	Animator* NPC6Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC6Image", L"/Image/Animation/npc/npc_6.png")->GetImage());
	NPC6Animator->CreateAnimation(L"npc6IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6MoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6MoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6MoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->CreateAnimation(L"npc6MoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	NPC6Animator->Play(L"npc6IdleFront", true);

	NPC6->AddComponent(NPC6Animator);
	NPC6->AddComponent(NPC6Collider);

	AddGameObject(NPC6);

	/// Resources ------------------------------------------------------------

	// 집 옆 소형 창고
	GameObject* warehouseA = new GameObject("WareHouseA", OBJECT_TYPE::BUILDING);
	warehouseA->GetTransform()->SetLocalPosition(Vector2(-1300, -530) + m_StartPoint);
	warehouseA->GetTransform()->SetSize({ 510.f, 420.f });
	ImageRenderer* warehouseARender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseA", L"/Image/House/Warehouse_A.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 510.f, 420.f }
	);
	Collider* warehouseACollider = new BoxCollider({ 510.f, 420.f });
	warehouseACollider->SetOffset({ 0.f,20.f });

	warehouseA->AddComponent(warehouseACollider);
	warehouseA->AddComponent(warehouseARender);

	AddGameObject(warehouseA);

	// 집
	GameObject* house = new GameObject("House", OBJECT_TYPE::BUILDING);
	house->GetTransform()->SetLocalPosition(Vector2(-600, -590) + m_StartPoint);
	house->GetTransform()->SetSize({ 636.f, 516.f });
	ImageRenderer* houseRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"House", L"/Image/House/House.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 636.f, 516.f }
	);
	Collider* houseCollider = new BoxCollider({ 636.f, 516.f });
	houseCollider->SetOffset({ 0.f,20.f });

	ObjectDataScript* houseDataScript = new ObjectDataScript(3000);

	house->AddComponent(houseDataScript);
	house->AddComponent(houseCollider);
	house->AddComponent(houseRender);

	AddGameObject(house);

	//고양이 집
	GameObject* catHouse = new GameObject("CatHouse", OBJECT_TYPE::BUILDING);
	catHouse->GetTransform()->SetLocalPosition(Vector2(-1030, -1000) + m_StartPoint);
	catHouse->GetTransform()->SetSize({ 300.f, 325.f });
	ImageRenderer* catHouseRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CatHouse", L"/Image/House/cat_house.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 300.f, 325.f }
	);
	Collider* catHouseCollider = new BoxCollider({ 300.f, 325.f });
	catHouseCollider->SetOffset({ 0.f,20.f });

	catHouse->AddComponent(catHouseCollider);
	catHouse->AddComponent(catHouseRender);

	AddGameObject(catHouse);

	//고양이 밥
	GameObject* catBowl = new GameObject("CatBowl", OBJECT_TYPE::BUILDING);
	catBowl->GetTransform()->SetLocalPosition(Vector2(-840, -870) + m_StartPoint);
	catBowl->GetTransform()->SetSize({ 76.f, 72.f });
	Animator* catBowlAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"CatBowl", L"/Image/House/pet_bowl.png")->GetImage());
	catBowlAnimator->CreateAnimation(L"catBowlFull", Vector2(0, 0), Vector2(76, 72), Vector2(0, 0), Vector2(0, 0), 0.1f, 1);
	catBowlAnimator->CreateAnimation(L"catBowlEmpty", Vector2(0, 0), Vector2(76, 72), Vector2(76, 0), Vector2(0, 0), 0.1f, 1);
	catBowlAnimator->Play(L"catBowlEmpty", true);

	Collider* catBowlCollider = new BoxCollider({ 76.f, 72.f });
	catBowlCollider->SetOffset({ 0.f,20.f });

	catBowl->AddComponent(catBowlCollider);
	catBowl->AddComponent(catBowlAnimator);

	AddGameObject(catBowl);

	//트럭
	GameObject* truck = new GameObject("Truck", OBJECT_TYPE::BUILDING);
	truck->GetTransform()->SetLocalPosition(Vector2(-1230, 220) + m_StartPoint);
	truck->GetTransform()->SetSize({ 570.f, 300.f });
	ImageRenderer* truckRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Truck", L"/Image/House/Truck.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 570.f, 300.f }
	);
	Collider* truckCollider = new BoxCollider({ 570.f, 260.f });
	truckCollider->SetOffset({ 0.f,0.f });

	truck->AddComponent(truckCollider);
	truck->AddComponent(truckRender);

	AddGameObject(truck);

	//트럭 아래 창고
	GameObject* warehouseC = new GameObject("WarehouseC", OBJECT_TYPE::BUILDING);
	warehouseC->GetTransform()->SetLocalPosition(Vector2(-1110, 570) + m_StartPoint);
	warehouseC->GetTransform()->SetSize({ 876.f, 402.f });
	ImageRenderer* warehouseCRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseC", L"/Image/House/Warehouse_C.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 876.f, 402.f }
	);
	Collider* warehouseCCollider = new BoxCollider({ 876.f, 402.f });
	warehouseCCollider->SetOffset({ 0.f,20.f });

	warehouseC->AddComponent(warehouseCCollider);
	warehouseC->AddComponent(warehouseCRender);

	AddGameObject(warehouseC);


	//연못
	GameObject* pond = new GameObject("Pond", OBJECT_TYPE::BUILDING);
	pond->GetTransform()->SetLocalPosition(Vector2(-150, 440) + m_StartPoint);
	pond->GetTransform()->SetSize({ 492.f, 492.f });
	
	Animator* pondAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Pond", L"/Image/House/Pond_Sheet.png")->GetImage());
	pondAnimator->CreateAnimation(L"pond", Vector2(0, 0), Vector2(492, 492), Vector2(0, 0), Vector2(492, 0), 0.2f, 4);
	pondAnimator->Play(L"pond", true);

	Collider* pondCollider = new BoxCollider({ 492.f, 492.f });
	pondCollider->SetOffset({ 0.f,20.f });

	ObjectDataScript* pondDataScript = new ObjectDataScript(4000);

	pond->AddComponent(pondDataScript);
	pond->AddComponent(pondCollider);
	pond->AddComponent(pondAnimator);

	AddGameObject(pond);

	//연못 옆 창고
	GameObject* warehouseB = new GameObject("WarehouseB", OBJECT_TYPE::BUILDING);
	warehouseB->GetTransform()->SetLocalPosition(Vector2(660, 540) + m_StartPoint);
	warehouseB->GetTransform()->SetSize({ 510.f, 420.f });
	ImageRenderer* warehouseBRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseB", L"/Image/House/Warehouse_B.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 510.f, 420.f }
	);
	Collider* warehouseBCollider = new BoxCollider({ 510.f, 420.f });
	warehouseBCollider->SetOffset({ 0.f,20.f });

	warehouseB->AddComponent(warehouseBCollider);
	warehouseB->AddComponent(warehouseBRender);

	AddGameObject(warehouseB);

	//오른쪽 창고
	GameObject* warehouseD = new GameObject("WarehouseD", OBJECT_TYPE::BUILDING);
	warehouseD->GetTransform()->SetLocalPosition(Vector2(2080, 0) + m_StartPoint);
	warehouseD->GetTransform()->SetSize({ 600.f, 700.f });
	ImageRenderer* warehouseDRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WarehouseD", L"/Image/House/Warehouse_D.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 600.f, 700.f }
	);
	Collider* warehouseDCollider = new BoxCollider({ 600.f, 700.f });
	warehouseDCollider->SetOffset({ 0.f,20.f });

	warehouseD->AddComponent(warehouseDCollider);
	warehouseD->AddComponent(warehouseDRender);

	AddGameObject(warehouseD);


	///밭 1 ----------------------------------------------------------
	float farmPosX = 500.f;
	float farmPosY = 290.f;

	for (int i = 1; i < 10; i++)
	{
		GameObject* farm = new GameObject("Farm", OBJECT_TYPE::FARM);
		farm->GetTransform()->SetLocalPosition(Vector2(farmPosX, -farmPosY) + m_StartPoint);
		farm->GetTransform()->SetSize({ 125.f, 125.f });

		Collider* farmCollider = new BoxCollider(Vector2{ 125, 125 });
		farmCollider->SetOffset(Vector2{ 0.f, 0.f });

		Animator* farmAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"corn", L"/Image/corn/corn_sheet.png")->GetImage());
		farmAnimator->CreateAnimation(L"farmNoSeed", Vector2(0, 0), Vector2(125, 125), Vector2(0, 55), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSeed", Vector2(0, 0), Vector2(125, 125), Vector2(125, 55), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmFirst", Vector2(0, 0), Vector2(125, 125), Vector2(250, 55), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSecond", Vector2(0, -3), Vector2(125, 128), Vector2(375, 52), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmThird", Vector2(0, -25), Vector2(125, 180), Vector2(500, 0), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmNoSeedWater", Vector2(0, 0), Vector2(125, 125), Vector2(0, 235), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSeedWater", Vector2(0, 0), Vector2(125, 125), Vector2(125, 235), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmFirstWater", Vector2(0, 0), Vector2(125, 125), Vector2(250, 235), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSecondWater", Vector2(0, -3), Vector2(125, 128), Vector2(375, 232), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmThirdWater", Vector2(0, -25), Vector2(125, 180), Vector2(500, 180), Vector2(0, 0), 0.1f, 1);
		farmAnimator->Play(L"farmThirdWater", true);

		farm->AddComponent(farmAnimator);
		farm->AddComponent(farmCollider);

		AddGameObject(farm);
		farmPosX -= 145;
		
		if (i % 3 == 0)
		{
			farmPosX = 500.f;
			farmPosY -= 145.f;
		}
	}

	///밭 2 ----------------------------------------------------------
	farmPosX = 1125.f;
	farmPosY = 290.f;

	for (int i = 1; i < 10; i++)
	{
		GameObject* farm = new GameObject("Farm", OBJECT_TYPE::FARM);
		farm->GetTransform()->SetLocalPosition(Vector2(farmPosX, -farmPosY) + m_StartPoint);
		farm->GetTransform()->SetSize({ 125.f, 125.f });

		Collider* farmCollider = new BoxCollider(Vector2{ 125, 125 });
		farmCollider->SetOffset(Vector2{ 0.f, 0.f });

		Animator* farmAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"corn", L"/Image/corn/corn_sheet.png")->GetImage());
		farmAnimator->CreateAnimation(L"farmNoSeed", Vector2(0, 0), Vector2(125, 125), Vector2(0, 55), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSeed", Vector2(0, 0), Vector2(125, 125), Vector2(125, 55), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmFirst", Vector2(0, 0), Vector2(125, 125), Vector2(250, 55), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSecond", Vector2(0, -3), Vector2(125, 128), Vector2(375, 52), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmThird", Vector2(0, -25), Vector2(125, 180), Vector2(500, 0), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmNoSeedWater", Vector2(0, 0), Vector2(125, 125), Vector2(0, 235), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSeedWater", Vector2(0, 0), Vector2(125, 125), Vector2(125, 235), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmFirstWater", Vector2(0, 0), Vector2(125, 125), Vector2(250, 235), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmSecondWater", Vector2(0, -3), Vector2(125, 128), Vector2(375, 232), Vector2(0, 0), 0.1f, 1);
		farmAnimator->CreateAnimation(L"farmThirdWater", Vector2(0, -25), Vector2(125, 180), Vector2(500, 180), Vector2(0, 0), 0.1f, 1);
		farmAnimator->Play(L"farmThirdWater", true);

		farm->AddComponent(farmAnimator);
		farm->AddComponent(farmCollider);

		AddGameObject(farm);
		farmPosX -= 145;

		if (i % 3 == 0)
		{
			farmPosX = 1125.f;
			farmPosY -= 145.f;
		}
	}

}
