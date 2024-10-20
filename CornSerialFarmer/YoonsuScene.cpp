#include "YoonsuScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "BoxCollider.h"
#include "Animation.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Camera.h"
#include "EventManager.h"
#include "ImageRenderer.h"

//스크립트
#include "FarmerScript.h"
#include "NPC1Script.h"
#include "NPC1ViewScript.h"
#include "DeadBodyScript.h"
#include "CameraScript.h"
#include "NPC2Script.h"
#include "NPC2ViewScript.h"
#include "CameraScript.h"
#include "BlackCatScript.h"
#include "FarmScript.h"
#include "PoliceScript.h"
#include "PoliceViewScript.h"
#include "GameManagerScript.h"


void YoonsuScene::Enter()
{
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FARM);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DEADBODY);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BUILDING);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::POLICEVIEW);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::POLICEVIEW, OBJECT_TYPE::BUILDING);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::NPC, OBJECT_TYPE::DEADBODY);
//	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::NPCVIEW, OBJECT_TYPE::DEADBODY);
//	
//	/// Game Manager ---------------------------------------------------------
//	GameObject* gameManager = new GameObject("GameManager", OBJECT_TYPE::DEFAULT);
//	gameManager->SetScene(this);
//	GameManagerScript* gameManagerScript = new GameManagerScript();
//	gameManager->AddComponent(gameManagerScript);
//
//	GameObject* cameraObject = new GameObject("CameraObject", OBJECT_TYPE::CAMERA);
//	Camera* camera = new Camera;
//	//CameraScript* cameraScript = new CameraScript;
//	cameraObject->AddComponent(camera);
//	//cameraObject->AddComponent(cameraScript);
//	AddGameObject(cameraObject);
//
//
//	// 배경
//	GameObject* background = new GameObject("Background", OBJECT_TYPE::BACKGROUND);
//	background->GetTransform()->SetLocalPosition(Vector2(952.f, 520.f));
//	background->GetTransform()->SetSize({ 2400.f, 1350.f });
//	ImageRenderer* backgroundRender = new ImageRenderer(
//		ResourceManager::GetInstance()->LoadResource<Image>(L"BackGround", L"/Image/floor/floor_test.png")->GetImage(),
//		{ 0.f, 0.f }, { 0.f, 0.f }, { 2400.f, 1350.f }
//	);
//	background->AddComponent(backgroundRender);
//	AddGameObject(background);
//
//	// FSM 테스트용 
//	GameObject* farmer = new GameObject("farmer", OBJECT_TYPE::PLAYER);
//	
//	Collider* testCollider4 = new BoxCollider(Vector2{ 60,120 });
//	testCollider4->SetOffset(Vector2{ 0.f,20.f });
//	farmer->AddComponent(testCollider4);
//	PrimitiveRenderer* farmerRenderer = new PrimitiveRenderer;
//	//farmerRenderer->SetType("Circle");
//	//farmer->AddComponent(farmerRenderer);
//
//	Animator* animator2 = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"FarmerImage", L"/Image/Animation/farmer/farmer.png")->GetImage());
//	farmer->AddComponent(animator2);
//	animator2->CreateAnimation(L"farmerIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0),   Vector2(140, 0), 0.2f, 4);
//	animator2->CreateAnimation(L"farmerIdleLeft",  Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
//	animator2->CreateAnimation(L"farmerIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
//	animator2->CreateAnimation(L"farmerIdleBack",  Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
//	animator2->CreateAnimation(L"farmerWalkFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
//	animator2->CreateAnimation(L"farmerWalkLeft",  Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
//	animator2->CreateAnimation(L"farmerWalkRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
//	animator2->CreateAnimation(L"farmerWalkBack",  Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
//	animator2->CreateAnimation(L"farmerHarvest",   Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.1f, 8);
//	animator2->CreateAnimation(L"farmerWatering",  Vector2(0, 0), Vector2(140, 160), Vector2(0, 1440), Vector2(140, 0), 0.1f, 7);
//	animator2->CreateAnimation(L"farmerInterection",  Vector2(0, 0), Vector2(140, 160), Vector2(0, 1600), Vector2(140, 0), 0.1f, 7);
//	animator2->CreateAnimation(L"farmerMoveBodyLeft",  Vector2(0, 0), Vector2(244, 160), Vector2(0, 1760), Vector2(244, 0), 0.1f, 5);
//	animator2->CreateAnimation(L"farmerMoveBodyRight",  Vector2(0, 0), Vector2(244, 160), Vector2(0, 1920), Vector2(244, 0), 0.1f, 5);
//
//	//animator2->Play(L"farmerWalkFront", true);
//
//	FarmerScript* farmerScript = new FarmerScript;
//	farmer->AddComponent(farmerScript);
//
//	AddGameObject(farmer);
//	//camera->SetTargetObject(farmer);
//	
//	// 말풍선
//	GameObject* farmerTextBubble = new GameObject("farmerTextBubble", OBJECT_TYPE::TEXTBUBBLE);
//
//	Animator* farmerTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble", L"/UI/speechBubble.png")->GetImage());
//	farmerTextBubble->AddComponent(farmerTextBubbleAnimator);
//	farmerTextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
//	farmerTextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
//	farmerTextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
//
//	farmer->AddObjectChild(farmerTextBubble);
//	farmer->GetObjectChild("farmerTextBubble")->SetActivate(false);
//	
//	// 발자국 
//	
//
//// NPC1 테스트용
//
//	GameObject* NPC1 = new GameObject("npc1", OBJECT_TYPE::NPC);
//	Collider* NPC1Collider = new BoxCollider(Vector2{ 60, 120 });
//	NPC1->AddComponent(NPC1Collider);
//	NPC1Collider->SetOffset(Vector2{ 0.f, 20.f });
//	PrimitiveRenderer* npc1Renderer = new PrimitiveRenderer;
//
//	Animator* NPC1Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC1Image", L"/Image/Animation/npc/npc_1.png")->GetImage());
//	NPC1->AddComponent(NPC1Animator);
//	NPC1Animator->CreateAnimation(L"npc1IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1MoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1MoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1MoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->CreateAnimation(L"npc1MoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
//	NPC1Animator->Play(L"npc1IdleFront", true);
//
//	NPC1Script* npc1Script = new NPC1Script;
//	NPC1->AddComponent(npc1Script);
//
//	// NPC1에게 게임 매니저 넣어줌....
//	npc1Script->m_NPC1Manager = gameManagerScript;
//
//	AddGameObject(NPC1);
//
//	////NPC1 시야
// 	GameObject* NPC1View = new GameObject("npc1View", OBJECT_TYPE::NPCVIEW);
// 	//Collider* NPC1ViewCollider = new CircleCollider(100.f);
// 	Collider* NPC1ViewCollider = new BoxCollider(Vector2{ 300,100 });
//	NPC1ViewCollider->SetOffset(Vector2{ 120.f, 20.f });
//	NPC1View->AddComponent(NPC1ViewCollider);
// 
// 	NPC1ViewScript* npc1ViewScript = new NPC1ViewScript;
// 	NPC1View->AddComponent(npc1ViewScript);
// 
// 	NPC1->AddObjectChild(NPC1View);
// 	
//	////NPC1 말풍선
//	GameObject* NPC1TextBubble = new GameObject("npc1TextBubble", OBJECT_TYPE::TEXTBUBBLE);
//
//	Animator* NPC1TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble", L"/UI/speechBubble.png")->GetImage());
//	NPC1TextBubble->AddComponent(NPC1TextBubbleAnimator);
//	NPC1TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
//	NPC1TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
//	NPC1TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
//	
//	NPC1->AddObjectChild(NPC1TextBubble);
//	NPC1->GetObjectChild("npc1TextBubble")->SetActivate(false);
//
//	//시체
//	GameObject* deadBody = new GameObject("deadBody", OBJECT_TYPE::DEADBODY);
//	Collider* deadBodyCollider = new BoxCollider(Vector2{ 120, 60 });
//	deadBodyCollider->SetOffset(Vector2{ 0.f, 20.f });
//	deadBody->AddComponent(deadBodyCollider);
//
//	Animator* deadBodyAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"DeadBody", L"/Image/Animation/corpse.png")->GetImage());
//	deadBody->AddComponent(deadBodyAnimator);
//	deadBodyAnimator->CreateAnimation(L"DeadBody", Vector2(0, 0), Vector2(172, 104), Vector2(0, 0), Vector2(172, 0), 0.2f, 4);
//	deadBodyAnimator->Play(L"DeadBody", true);
//
//	DeadBodyScript* deadBodyScript = new DeadBodyScript;
//	deadBody->AddComponent(deadBodyScript);
//
//	AddGameObject(deadBody);
//
//	//NPC2
//	GameObject* NPC2 = new GameObject("npc2", OBJECT_TYPE::NPC);
//	
//	Collider* NPC2Collider = new BoxCollider(Vector2{ 60,120 });
//	NPC2Collider->SetOffset(Vector2{ 0.f, 20.f });
//	NPC2->AddComponent(NPC2Collider);
//
//	Animator* NPC2Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC2Image", L"/Image/Animation/npc/npc_2.png")->GetImage());
//	NPC2->AddComponent(NPC2Animator);
//	NPC2Animator->CreateAnimation(L"NPC2IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
//	//NPC2Animator->Play(L"NPC2IdleFront", true);
//
//	NPC2Script* npc2Script = new NPC2Script;
//	NPC2->AddComponent(npc2Script);
//
//	// NPC2에게 게임 매니저 넣어줌....
//	npc2Script->m_NPC2Manager = gameManagerScript;
//
//	AddGameObject(NPC2);
//
//	////NPC2 시야
//	GameObject* NPC2View = new GameObject("npc2View", OBJECT_TYPE::NPCVIEW);
//	//Collider* NPC1ViewCollider = new CircleCollider(100.f);
//	Collider* NPC2ViewCollider = new BoxCollider(Vector2{ 300,100 });
//	NPC2View->AddComponent(NPC2ViewCollider);
//
//	NPC2ViewScript* npc2ViewScript = new NPC2ViewScript;
//	NPC2View->AddComponent(npc2ViewScript);
//
//	NPC2->AddObjectChild(NPC2View);
//	NPC2ViewCollider->SetOffset(Vector2{ 120.f, 20.f });
//
//	////NPC2 말풍선
//	GameObject* NPC2TextBubble = new GameObject("npc2TextBubble", OBJECT_TYPE::TEXTBUBBLE);
//
//	Animator* NPC2TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble2", L"/UI/speechBubble.png")->GetImage());
//	NPC2TextBubble->AddComponent(NPC2TextBubbleAnimator);
//	NPC2TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
//	NPC2TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
//	NPC2TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
//
//	NPC2->AddObjectChild(NPC2TextBubble);
//	NPC2->GetObjectChild("npc2TextBubble")->SetActivate(false);
//
//	//NPC2
//	GameObject* NPC2 = new GameObject("npc2", OBJECT_TYPE::NPC);
//	
//	Collider* NPC2Collider = new BoxCollider(Vector2{ 60,120 });
//	NPC2Collider->SetOffset(Vector2{ 0.f, 20.f });
//	NPC2->AddComponent(NPC2Collider);
//
//	Animator* NPC2Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPC2Image", L"/Image/Animation/npc/npc_2.png")->GetImage());
//	NPC2->AddComponent(NPC2Animator);
//	NPC2Animator->CreateAnimation(L"NPC2IdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2IdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2IdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2IdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
//	NPC2Animator->CreateAnimation(L"NPC2WalkBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.1f, 4);
//	//NPC2Animator->Play(L"NPC2IdleFront", true);
//
//	NPC2Script* npc2Script = new NPC2Script;
//	NPC2->AddComponent(npc2Script);
//
//	// NPC2에게 게임 매니저 넣어줌....
//	npc2Script->m_NPC2Manager = gameManagerScript;
//
//	AddGameObject(NPC2);
//
//	////NPC2 시야
//	GameObject* NPC2View = new GameObject("npc2View", OBJECT_TYPE::NPCVIEW);
//	//Collider* NPC1ViewCollider = new CircleCollider(100.f);
//	Collider* NPC2ViewCollider = new BoxCollider(Vector2{ 300,100 });
//	NPC2View->AddComponent(NPC2ViewCollider);
//
//	NPC2ViewScript* npc2ViewScript = new NPC2ViewScript;
//	NPC2View->AddComponent(npc2ViewScript);
//
//	NPC2->AddObjectChild(NPC2View);
//	NPC2ViewCollider->SetOffset(Vector2{ 120.f, 20.f });
//
//	////NPC2 말풍선
//	GameObject* NPC2TextBubble = new GameObject("npc2TextBubble", OBJECT_TYPE::TEXTBUBBLE);
//
//	Animator* NPC2TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubble2", L"/UI/speechBubble.png")->GetImage());
//	NPC2TextBubble->AddComponent(NPC2TextBubbleAnimator);
//	NPC2TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
//	NPC2TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
//	NPC2TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
//
//	NPC2->AddObjectChild(NPC2TextBubble);
//	NPC2->GetObjectChild("npc2TextBubble")->SetActivate(false);
//
//	//고양이
//	GameObject* blackCat = new GameObject("blackCat", OBJECT_TYPE::ANIMAL);
//	
//	Collider* blackCatCollider = new BoxCollider(Vector2{ 60, 100 });
//	blackCatCollider->SetOffset(Vector2{ 0.f, 10.f });
//	blackCat->AddComponent(blackCatCollider);
//
//	Animator* blackCatAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"blackCat", L"/Image/Animation/cat/cat.png")->GetImage());
//	blackCat->AddComponent(blackCatAnimator);
//	blackCatAnimator->CreateAnimation(L"blackCatIdleFront", Vector2(0, 0), Vector2(136, 120), Vector2(0, 0), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatIdleLeft", Vector2(0, 0), Vector2(136, 120), Vector2(0, 120), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatIdleRight", Vector2(0, 0), Vector2(136, 120), Vector2(0, 240), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatIdleBack", Vector2(0, 0), Vector2(136, 120), Vector2(0, 360), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatMoveFront", Vector2(0, 0), Vector2(136, 120), Vector2(0, 480), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatMoveLeft", Vector2(0, 0), Vector2(136, 120), Vector2(0, 600), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatMoveRight", Vector2(0, 0), Vector2(136, 120), Vector2(0,720), Vector2(136, 0), 0.2f, 4);
//	blackCatAnimator->CreateAnimation(L"blackCatMoveBack", Vector2(0, 0), Vector2(136, 120), Vector2(0, 840), Vector2(136, 0), 0.2f, 4);
//	//blackCatAnimator->Play(L"blackCatWalkLeft", true);
//
//	BlackCatScript* blackCatScript = new BlackCatScript;
//	blackCat->AddComponent(blackCatScript);
//
//	AddGameObject(blackCat);
//
//	//밭
//	GameObject* farm = new GameObject("farm", OBJECT_TYPE::FARM);
//	
//	Collider* farmCollider = new BoxCollider(Vector2{ 100, 100 });
//	farmCollider->SetOffset(Vector2{ 0.f, 0.f });
//	farm->AddComponent(farmCollider);
//	
//	Animator* farmAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"corn", L"/Image/corn/corn_sheet.png")->GetImage());
//	farm->AddComponent(farmAnimator);
//	farmAnimator->CreateAnimation(L"farmNoSeed", Vector2(0, 0), Vector2(100, 100), Vector2(0, 44), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmSeed", Vector2(0, 0), Vector2(100, 100), Vector2(100, 44), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmFirst", Vector2(0, 0), Vector2(100, 100), Vector2(200, 44), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmSecond", Vector2(0, -1), Vector2(100, 102), Vector2(300, 42), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmThird", Vector2(0, -22), Vector2(100, 144), Vector2(400, 0), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmNoSeedWater", Vector2(0, 0), Vector2(100, 100), Vector2(0, 188), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmSeedWater", Vector2(0, 0), Vector2(100, 100), Vector2(100, 188), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmFirstWater", Vector2(0, 0), Vector2(100, 100), Vector2(200, 188), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmSecondWater", Vector2(0, -1), Vector2(100, 102), Vector2(300, 186), Vector2(0, 0), 0.1f, 1);
//	farmAnimator->CreateAnimation(L"farmThirdWater", Vector2(0, -22), Vector2(100, 144), Vector2(400, 144), Vector2(0, 0), 0.1f, 1);
//	
//	FarmScript* farmScript = new FarmScript;
//	farm->AddComponent(farmScript);
//
//	AddGameObject(farm);
//	
//	//경찰
//	GameObject* police1 = new GameObject("police", OBJECT_TYPE::NPC);
//
//	Collider* police1Collider = new BoxCollider(Vector2{ 60, 120 });
//	police1Collider->SetOffset(Vector2{ 0.f, 20.f });
//	police1->AddComponent(police1Collider);
//
//	Animator* police1Animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"Police1", L"/Image/Animation/police/police_1.png")->GetImage());
//	police1->AddComponent(police1Animator);
//	police1Animator->CreateAnimation(L"PoliceIdleFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceIdleLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceIdleRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceIdleBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceMoveFront", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceMoveLeft", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceMoveRight", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceMoveBack", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1120), Vector2(140, 0), 0.2f, 4);
//	police1Animator->CreateAnimation(L"PoliceFind", Vector2(0, 0), Vector2(140, 160), Vector2(0, 1280), Vector2(140, 0), 0.2f, 4);
//
//	PoliceScript* police1Script = new PoliceScript;
//	police1->AddComponent(police1Script);
//	
//	// 경찰에게 게임 매니저 넣어줌....
//	police1Script->m_Policemanager = gameManagerScript;
//
//	AddGameObject(police1);
//
//	////Police1 시야
//	GameObject* police1View = new GameObject("police1View", OBJECT_TYPE::POLICEVIEW);
//	police1View->GetTransform()->SetSize(Vector2(140.f, 480.f));
//
//	Collider* police1ViewCollider = new BoxCollider(Vector2{ 110.f, 460.f });
//	police1ViewCollider->SetOffset(Vector2{ 0.f, 200.f });
//	police1View->AddComponent(police1ViewCollider);
//	
//	ImageRenderer* policeViewRender = new ImageRenderer(ResourceManager::GetInstance()->LoadResource<Image>(L"View", L"/Image/UI/eye_box.png")->GetImage(),
//		{ 0.f, 200.f }, { 0.f, 0.f }, { 140.f, 480.f });
//	police1View->AddComponent(policeViewRender);
//
//	PoliceViewScript* police1ViewScript = new PoliceViewScript;
//	police1View->AddComponent(police1ViewScript);
//
//	police1->AddObjectChild(police1View);
//
//	//Police1 말풍선
//	GameObject* police1TextBubble = new GameObject("police1TextBubble", OBJECT_TYPE::TEXTBUBBLE);
//	
//	Animator* police1TextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubblePolice", L"/UI/speechBubble.png")->GetImage());
//	police1TextBubble->AddComponent(police1TextBubbleAnimator);
//	police1TextBubbleAnimator->CreateAnimation(L"QuestionMark", Vector2(0, -120), Vector2(128, 120), Vector2(0, 0), Vector2(128, 0), 0.2f, 4);
//	police1TextBubbleAnimator->CreateAnimation(L"ExclamationMark", Vector2(0, -120), Vector2(128, 110), Vector2(0, 128), Vector2(0, 0), 0.1f, 1);
//	police1TextBubbleAnimator->CreateAnimation(L"TextBubble", Vector2(0, -120), Vector2(112, 108), Vector2(0, 240), Vector2(0, 0), 0.2f, 1);
//
//	police1->AddObjectChild(police1TextBubble);
//	police1->GetObjectChild("police1TextBubble")->SetActivate(false);
//
//
//	//임시 집
//	GameObject* house = new GameObject("House", OBJECT_TYPE::BUILDING);
//	house->GetTransform()->SetLocalPosition(Vector2{600, 350});
//	house->GetTransform()->SetSize({ 420.f, 410.f });
//	ImageRenderer* houseRender = new ImageRenderer(
//		ResourceManager::GetInstance()->LoadResource<Image>(L"House", L"/Image/House/House.png")->GetImage(),
//		{ 0.f, 0.f }, { 0.f, 0.f }, { 420.f, 410.f }
//	);
//	Collider* houseCollider = new BoxCollider({ 420.f, 410 });
//	house->AddComponent(houseCollider);
//	house->AddComponent(houseRender);
//	AddGameObject(house);
//
//	//임시 집 말풍선
//	GameObject* houseTextBubble = new GameObject("houseTextBubble", OBJECT_TYPE::TEXTBUBBLE);
//
//	Animator* houseTextBubbleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TextBubbleHouse", L"/Image/UI/die_mark_1.png")->GetImage());
//	houseTextBubble->AddComponent(houseTextBubbleAnimator);
//	houseTextBubbleAnimator->CreateAnimation(L"DieMark", Vector2(0, -250), Vector2(112, 108), Vector2(0, 0), Vector2(112, 0), 0.2f, 4);
//	houseTextBubbleAnimator->Play(L"DieMark", true);
//
//	house->AddObjectChild(houseTextBubble);
//	house->GetObjectChild("houseTextBubble")->SetActivate(false);
}
