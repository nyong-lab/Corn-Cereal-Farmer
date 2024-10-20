#include "DongilScene.h"

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
#include "ItemManagerScript.h"
#include "QuestManagerScript.h"
#include "EffectManagerScript.h"
#include "FarmerScript.h"
#include "NPC1Script.h"
#include "NPC1ViewScript.h"
#include "NPC2Script.h"
#include "NPC2ViewScript.h"
#include "BlackCatScript.h"
#include "PoliceScript.h"
#include "PoliceViewScript.h"
#include "ObjectDataScript.h"
#include "FarmScript.h"
#include "WildBoarScript.h"

// 임시
#include <random>


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
// 고양이 : 9000
// 맷돼지 : 10000
// 

void DongilScene::Enter()
{
	/// 충돌 타입 체크 ----------------------------------------------------------
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BUILDING);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FARM);
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ANIMAL);

	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::ANIMAL, OBJECT_TYPE::BUILDING);

	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::NPC, OBJECT_TYPE::BUILDING);


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

	// -----------------------------------------------------------------------

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
	ObjectDataScript* warehouseADataScript = new ObjectDataScript(4000);

	warehouseA->AddComponent(warehouseADataScript);
	warehouseA->AddComponent(warehouseACollider);
	warehouseA->AddComponent(warehouseARender);

	AddGameObject(warehouseA);

	// 임시 소형 창고 말풍선
	GameObject* warehouseATextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* warehouseATextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleHouse", L"/Image/UI/die_mark_1.png")->GetImage());
	warehouseATextBubble->AddComponent(warehouseATextBubbleAnimator);
	warehouseATextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	warehouseATextBubbleAnimator->Play(L"DieMark", true);

	warehouseA->AddObjectChild(warehouseATextBubble);
	warehouseA->GetObjectChild("houseTextBubble")->SetActivate(false);

	// -----------------------------------------------------------------------

	// 고양이 집
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

	// -----------------------------------------------------------------------

	/// 트럭
	GameObject* truck = new GameObject("Truck", OBJECT_TYPE::BUILDING);
	truck->GetTransform()->SetLocalPosition(Vector2(-1230, 220) + m_StartPoint);
	truck->GetTransform()->SetSize({ 570.f, 300.f });
	ImageRenderer* truckRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Truck", L"/Image/House/Truck.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 570.f, 300.f }
	);
	Collider* truckCollider = new BoxCollider({ 570.f, 260.f });
	truckCollider->SetOffset({ 0.f, 0.f });
	ObjectDataScript* truckDataScript = new ObjectDataScript(0);
	truckDataScript->isDeadBodyHave = false;
	truck->AddComponent(truckDataScript);
	truck->AddComponent(truckCollider);
	truck->AddComponent(truckRender);
	AddGameObject(truck);

	//임시 트럭 말풍선
	GameObject* truckTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* truckTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleWarehHouse", L"/Image/UI/die_mark_1.png")->GetImage());
	truckTextBubble->AddComponent(truckTextBubbleAnimator);
	truckTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	truckTextBubbleAnimator->Play(L"DieMark", true);

	truck->AddObjectChild(truckTextBubble);
	truck->GetObjectChild("houseTextBubble")->SetActivate(false);

	// -----------------------------------------------------------------------

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
	ObjectDataScript* warehouseDataScript = new ObjectDataScript(1000);
	warehouseDataScript->isDeadBodyHave = true;

	warehouseC->AddComponent(warehouseDataScript);
	warehouseC->AddComponent(warehouseCCollider);
	warehouseC->AddComponent(warehouseCRender);

	AddGameObject(warehouseC);

	// -----------------------------------------------------------------------

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

	//임시 연못 말풍선
	GameObject* pondTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* pondTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleHouse", L"/Image/UI/die_mark_1.png")->GetImage());
	pondTextBubble->AddComponent(pondTextBubbleAnimator);
	pondTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
	pondTextBubbleAnimator->Play(L"DieMark", true);

	pond->AddObjectChild(pondTextBubble);
	pond->GetObjectChild("houseTextBubble")->SetActivate(false);

	// -----------------------------------------------------------------------

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

	// -----------------------------------------------------------------------

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

	// -----------------------------------------------------------------------

	// 밭1 
	float farmPosX = 500.f;
	float farmPosY = 290.f;

	GameObject* firstFarm[10] = {};

	for (int i = 1; i < 10; i++)
	{
		string farmName = "FirstFarm" + to_string(i);
		firstFarm[i] = new GameObject(farmName, OBJECT_TYPE::FARM);
		firstFarm[i]->GetTransform()->SetLocalPosition(Vector2(farmPosX, -farmPosY) + m_StartPoint);
		firstFarm[i]->GetTransform()->SetSize({ 125.f, 125.f });

		// 윤서 코드
		/*Collider* farmCollider = new BoxCollider(Vector2{ 125, 125 });
		farmCollider->SetOffset(Vector2{ 0.f, 0.f });*/

		// 동일 코드
		// 	Collider* farmCollider = new BoxCollider(Vector2{ 100, 100 });
		// 	farmCollider->SetOffset(Vector2{ 0.f, 0.f });
		// 	ObjectDataScript* farmDataScript = new ObjectDataScript(2000);
		// 	farm->AddComponent(farmDataScript);
		// 	farm->AddComponent(farmCollider);

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

		firstFarm[i]->AddComponent(farmAnimator);
		//farm->AddComponent(farmCollider);

		AddGameObject(firstFarm[i]);
		farmPosX -= 145;

		if (i % 3 == 0)
		{
			farmPosX = 500.f;
			farmPosY -= 145.f;
		}
	}

	// -----------------------------------------------------------------------

	// 밭 2
	farmPosX = 1125.f;
	farmPosY = 290.f;

	GameObject* secondFarm[10] = {};

	for (int i = 1; i < 10; i++)
	{
		string farmName = "SecondFarm" + to_string(i);
		secondFarm[i] = new GameObject(farmName, OBJECT_TYPE::FARM);
		secondFarm[i]->GetTransform()->SetLocalPosition(Vector2(farmPosX, -farmPosY) + m_StartPoint);
		secondFarm[i]->GetTransform()->SetSize({ 125.f, 125.f });

		/*Collider* farmCollider = new BoxCollider(Vector2{ 125, 125 });
		farmCollider->SetOffset(Vector2{ 0.f, 0.f });*/

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

		secondFarm[i]->AddComponent(farmAnimator);
		//farm->AddComponent(farmCollider);

		AddGameObject(secondFarm[i]);
		farmPosX -= 145;

		if (i % 3 == 0)
		{
			farmPosX = 1125.f;
			farmPosY -= 145.f;
		}
	}

	// 	FarmScript* farmScript = new FarmScript;
	// 	secondFarm[0]->AddComponent(farmScript);

		// -----------------------------------------------------------------------

		// 검은 고양이  ------------- (상호작용) --------------
	GameObject* blackCat = new GameObject("blackCat", OBJECT_TYPE::ANIMAL);

	Collider* blackCatCollider = new BoxCollider(Vector2{ 60.f, 100.f });
	blackCatCollider->SetOffset(Vector2{ 0.f, 10.f });
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

	GameObject* blackCatChild = new GameObject("blackCatChild", OBJECT_TYPE::ANIMAL);
	Collider* blackCatChildCollider = new BoxCollider({ 60.f, 100.f });
	ObjectDataScript* blackCatChildDataScript = new ObjectDataScript(6000);
	blackCatChild->AddComponent(blackCatChildDataScript);
	blackCatChild->AddComponent(blackCatChildCollider);

	blackCat->AddObjectChild(blackCatChild);

	/// Test Resources ----------------------------------------------------

	// 나무  ------------- (상호작용) --------------
	GameObject* tree = new GameObject("Tree", OBJECT_TYPE::BUILDING);
	tree->GetTransform()->SetLocalPosition(Vector2(-1000.f, 0.f) + m_StartPoint);
	tree->GetTransform()->SetSize({ 271.f, 150.f });
	ImageRenderer* treeRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"Tree", L"/Image/Test/TestTree.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 271.f, 150.f }
	);
	Collider* treeColliedr = new BoxCollider({ 300.f, 170.f });
	ObjectDataScript* treeDataScript = new ObjectDataScript(5000);
	tree->AddComponent(treeDataScript);
	tree->AddComponent(treeColliedr);
	tree->AddComponent(treeRender);
	AddGameObject(tree);

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

	/// Effect Manager
	GameObject* effectManager = new GameObject("EffectManager", OBJECT_TYPE::DEFAULT);
	effectManager->SetScene(this);
	EffectManagerScript* effectManagerScript = new EffectManagerScript();
	effectManager->AddComponent(effectManagerScript);
	AddGameObject(effectManager);

	// Brightness Effect
	GameObject* brightnessEffect = new GameObject("BrightnessEffect", OBJECT_TYPE::EFFECT);
	brightnessEffect->GetTransform()->SetLocalPosition(m_StartPoint);
	brightnessEffect->GetTransform()->SetSize({ 4800.f, 2704.f });
	ImageRenderer* brightnessRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"BrightnessRender", L"/Effect/Brightness.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 4800.f, 2704.f }
	);
	brightnessRender->SetOpacity(0.f);
	brightnessEffect->AddComponent(brightnessRender);
	AddGameObject(brightnessEffect);

	// 게임 매니저에 매니저 스크립트들 추가
	gameManagerScript->m_ItemManager = itemManagerScript;
	gameManagerScript->m_QuestManager = questManagerScript;
	gameManagerScript->m_EffectManager = effectManagerScript;

	// 퀘스트 관련 오브젝트들을 넣어줌 
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(house);     // 집
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(warehouseA); // 창고
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(pond);      // 연못
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(secondFarm[0]);      // 밭 - 이거 일단 인덱스로 넣어둘게용
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(tree);      // 나무

	// 윤서
	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(truck);		// 트럭

	/// 플레이어 --------------------------------------------------------------
	GameObject* farmer = new GameObject("farmer", OBJECT_TYPE::PLAYER);
	Collider* testCollider4 = new BoxCollider(Vector2{ 60,120 });
	testCollider4->SetOffset(Vector2{ 0.f,20.f });
	farmer->AddComponent(testCollider4);
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
	// 	ObjectDataScript* farmerData = new ObjectDataScript(1000);
	// 	farmer->AddComponent(farmerData);
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

	farmer->AddObjectChild(farmerTextBubble);
	farmer->GetObjectChild("farmerTextBubble")->SetActivate(false);

	// 플레이어에 게임 매니저 넣어줌....
	farmerScript->manager = gameManagerScript;

	/// NPC1 ------------------------------------------------------------------------
	GameObject* NPC1 = new GameObject("npc1", OBJECT_TYPE::NPC);
	Collider* NPC1Collider = new BoxCollider(Vector2{ 60, 120 });
	NPC1->AddComponent(NPC1Collider);
	NPC1Collider->SetOffset(Vector2{ 0.f, 20.f });
	PrimitiveRenderer* npc1Renderer = new PrimitiveRenderer;

	Animator* NPC1Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC1Image", L"/Image/Animation/npc/npc_1.png")->GetImage());
	NPC1->AddComponent(NPC1Animator);
	NPC1Animator->CreateAnimation(L"npc1IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1MoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1MoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1MoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->CreateAnimation(L"npc1MoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	NPC1Animator->Play(L"npc1IdleFront", true);

	NPC1Script* npc1Script = new NPC1Script;
	NPC1->AddComponent(npc1Script);

	// NPC1에게 게임 매니저 넣어줌....
	npc1Script->m_NPC1Manager = gameManagerScript;

	AddGameObject(NPC1);

	////NPC1 시야
	GameObject* NPC1View = new GameObject("npc1View", OBJECT_TYPE::NPCVIEW);

	Collider* NPC1ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC1ViewCollider->SetOffset(Vector2{ 120.f, 20.f });
	NPC1View->AddComponent(NPC1ViewCollider);

	NPC1ViewScript* npc1ViewScript = new NPC1ViewScript;
	NPC1View->AddComponent(npc1ViewScript);

	NPC1->AddObjectChild(NPC1View);

	////NPC1 말풍선
	GameObject* NPC1TextBubble = new GameObject("npc1TextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC1TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble", L"/UI/speechBubble.png")->GetImage());
	NPC1TextBubble->AddComponent(NPC1TextBubbleAnimator);
	NPC1TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC1TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC1TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	NPC1->AddObjectChild(NPC1TextBubble);
	NPC1->GetObjectChild("npc1TextBubble")->SetActivate(false);


	/// NPC2 ------------------------------------------------------------------------
	GameObject* NPC2 = new GameObject("npc2", OBJECT_TYPE::NPC);

	Collider* NPC2Collider = new BoxCollider(Vector2{ 60,120 });
	NPC2Collider->SetOffset(Vector2{ 0.f, 20.f });
	NPC2->AddComponent(NPC2Collider);

	Animator* NPC2Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC2Image", L"/Image/Animation/npc/npc_2.png")->GetImage());
	NPC2->AddComponent(NPC2Animator);
	NPC2Animator->CreateAnimation(L"NPC2IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2WalkFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2WalkLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2WalkRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
	NPC2Animator->CreateAnimation(L"NPC2WalkBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
	//NPC2Animator->Play(L"NPC2IdleFront", true);

	NPC2Script* npc2Script = new NPC2Script;
	NPC2->AddComponent(npc2Script);

	// NPC2에게 게임 매니저 넣어줌....
	npc2Script->m_NPC2Manager = gameManagerScript;

	AddGameObject(NPC2);

	////NPC2 시야
	GameObject* NPC2View = new GameObject("npc2View", OBJECT_TYPE::NPCVIEW);
	//Collider* NPC1ViewCollider = new CircleCollider(100.f);
	Collider* NPC2ViewCollider = new BoxCollider(Vector2{ 300,100 });
	NPC2View->AddComponent(NPC2ViewCollider);

	NPC2ViewScript* npc2ViewScript = new NPC2ViewScript;
	NPC2View->AddComponent(npc2ViewScript);

	NPC2->AddObjectChild(NPC2View);
	NPC2ViewCollider->SetOffset(Vector2{ 120.f, 20.f });

	////NPC2 말풍선
	GameObject* NPC2TextBubble = new GameObject("npc2TextBubble", OBJECT_TYPE::TEXTBUBBLE);

	Animator* NPC2TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble2", L"/UI/speechBubble.png")->GetImage());
	NPC2TextBubble->AddComponent(NPC2TextBubbleAnimator);
	NPC2TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
	NPC2TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
	NPC2TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);

	NPC2->AddObjectChild(NPC2TextBubble);
	NPC2->GetObjectChild("npc2TextBubble")->SetActivate(false);

	///Police1 -----------------------------------------------------------------------
	GameObject* police1 = new GameObject("police", OBJECT_TYPE::NPC);

	Collider* police1Collider = new BoxCollider(Vector2{ 60, 120 });
	police1Collider->SetOffset(Vector2{ 0.f, 20.f });
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

	//PoliceScript* police1Script = new PoliceScript;
	//police1->AddComponent(police1Script);

	// 경찰에게 게임 매니저 넣어줌....
	//police1Script->m_Policemanager = gameManagerScript;

	AddGameObject(police1);

	////Police1 시야
	GameObject* police1View = new GameObject("police1View", OBJECT_TYPE::POLICEVIEW);
	police1View->GetTransform()->SetSize(Vector2(140.f, 480.f));

	Collider* police1ViewCollider = new BoxCollider(Vector2{ 110.f, 460.f });
	police1ViewCollider->SetOffset(Vector2{ 0.f, 200.f });
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

	police1->AddObjectChild(police1TextBubble);
	police1->GetObjectChild("police1TextBubble")->SetActivate(false);
}

// 밤 퀘스트 : 멧돼지 쫒아내기
// 퀘스트 발생시 씬에 멧돼지를 추가시킨다.
void DongilScene::CreateWildBoar(GameManagerScript* gameManagerScript)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 2);
	int randomNumber = dis(gen);

	GameObject* wildBoar = new GameObject("wildBoar", OBJECT_TYPE::ANIMAL);
	wildBoar->GetTransform()->SetSize(Vector2(271.f, 150.f));

	// 생성 위치는 총 두 곳
	// 랜덤하 위치에 SetPosition
	if (randomNumber == 1)
	{
		wildBoar->GetTransform()->SetLocalPosition({ 0.f,0.f });
	}
	else
	{
		wildBoar->GetTransform()->SetLocalPosition({ 0.f,0.f });
	}

	Collider* wildBoarCollider = new BoxCollider(Vector2{ 300.f, 200.f });
	wildBoarCollider->SetOffset(Vector2{ 0.f, 0.f });
	wildBoar->AddComponent(wildBoarCollider);

	// 임시 테스트이미지 추후에 애니메이션으로 변경
	ImageRenderer* treeRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WildBoar", L"/Image/Test/TestWildBoar.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 271.f, 150.f }
	);

	//Animator* wildBoarAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WildBoar", /*L"/Image/Animation/police/police_1.png"*/)->GetImage());
	//wildBoar->AddComponent(wildBoarAnimator);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.2f, 4);
	//wildBoarAnimator->CreateAnimation(L"", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.2f, 4);

	WildBoarScript* wildBoarScript = new WildBoarScript;
	wildBoar->AddComponent(wildBoarScript);

	ObjectDataScript* wildBoarDataScript = new ObjectDataScript(10000);
	wildBoar->AddComponent(wildBoarDataScript);

	gameManagerScript->m_QuestManager->m_QuestObjects.push_back(wildBoar);  // 맷돼지

	AddGameObject(wildBoar);
}
