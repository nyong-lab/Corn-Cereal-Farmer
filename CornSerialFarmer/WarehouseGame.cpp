#include "WarehouseGame.h"
#include "Panel.h"
#include "Define.h"
#include "../Math/Vector2.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "MonoBehaviour.h"
#include "Button.h"
#include "KeyHoleScript.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Image.h"
#include "LockScript.h"
#include "WareHouseGameScript.h"
#include "WareHouseDoorScript.h"
#include "CountDown.h"
#include "Animator.h"

WarehouseGame::WarehouseGame() : 
	GameObject("WareHouseGame", OBJECT_TYPE::UI)
{
	GetTransform()->SetLocalPosition(Vector2{ 1920.f * 0.5f, 1080.f * 0.5f });

	/// <summary>
	/// ∏ﬁ¿Œ
	/// </summary>
	GetTransform()->SetSize(Vector2{ 900, 700 });
	UI* panel = new Panel;
	AddComponent(panel);
	ImageRenderer* wareHouseImageRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WareHouseImage", L"/Minigame/mini_game_1.png")->GetImage(),
		{}, {}, GetTransform()->GetSize());
	WareHouseGameScript* whScript = new WareHouseGameScript;
	AddComponent(whScript);

	AddComponent(wareHouseImageRender);

	{
		GameObject* door = new GameObject("WareHouseDoor", OBJECT_TYPE::UI);
		door->GetTransform()->SetSize({ 900, 700 });
		UI* panel = new Panel;
		ImageRenderer* wareHouseDoorRenderer = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"WareHouseDoor", L"/Minigame/mini_game_door_Sheet.png")->GetImage(),
			{}, { 0,0 }, GetTransform()->GetSize());
		WareHouseDoorScript* doorScript = new WareHouseDoorScript;
		doorScript->m_DoorRenderer = wareHouseDoorRenderer;
		door->AddComponent(panel);
		door->AddComponent(wareHouseDoorRenderer);
		door->AddComponent(doorScript);
		AddObjectChild(door);
	}


	/// <summary>
	/// ¿⁄π∞ºË
	/// </summary>
	GameObject* lock = new GameObject("lock", OBJECT_TYPE::DEFAULT);
	lock->GetTransform()->SetLocalPosition(Vector2{ 0.f, 50.f });
	lock->GetTransform()->SetSize(Vector2{ 150.f, 125.f });
	ImageRenderer* lockImageRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"LockImage", L"/Minigame/mini_game_Lock.png")->GetImage(),
		{}, {}, GetTransform()->GetSize());
	LockScript* lockScript = new LockScript;
	lock->AddComponent(lockScript);
	lock->AddComponent(lockImageRender);
	AddObjectChild(lock);


	/// <summary>
	/// ø≠ºË»§¿∫ ø≠ºË±∏∏€
	/// </summary>
	GameObject* keyHole = new GameObject("KeyHole", OBJECT_TYPE::UI);
	keyHole->GetTransform()->SetLocalPosition(Vector2{ 0.f, 70.f });
	keyHole->GetTransform()->SetSize(Vector2{ 96.f, 96.f });
	ImageRenderer* keyImageRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"KeyImage", L"/MiniGame/mini_game_key_Sheet.png")->GetImage(),
		{}, {}, GetTransform()->GetSize());
	keyImageRender->SetOpacity(0.f);
	KeyHoleScript* khScript = new KeyHoleScript;
	Button* holeButton = new Button([khScript, keyImageRender](BUTTON_EVENT event)->void
		{
			if (event == BUTTON_EVENT::CLICK) {
				if (khScript->m_IsClicked == false)
				{
					keyImageRender->FadeIn(.5f);
					khScript->m_IsClicked = true;
				}
			}
		}
	);
	keyHole->AddComponent(keyImageRender);
	keyHole->AddComponent(khScript);
	keyHole->AddComponent(holeButton);
	AddObjectChild(keyHole);


	CountDown* countDown = new CountDown;
	countDown->GetTransform()->SetLocalPosition({ 0.f, -450.f });
	AddObjectChild(countDown);


	/// Explain Text
	GameObject* explainWareHouseGameText = new GameObject("ExplainWareHouseGameText", OBJECT_TYPE::UI);
	explainWareHouseGameText->GetTransform()->SetLocalPosition(Vector2(0.f, -20.f));
	explainWareHouseGameText->GetTransform()->SetSize(Vector2(900, 700));
	// Image
	ImageRenderer* WareHouseGameText = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainWareHouseGameText", L"/Minigame/mini_game_Text2.png")->GetImage());
	explainWareHouseGameText->AddComponent(WareHouseGameText);
	// Add Object
	AddObjectChild(explainWareHouseGameText);


	/// Explain Animation
	GameObject* explainWareHouseGame = new GameObject("ExplainWareHouseGame", OBJECT_TYPE::UI);
	explainWareHouseGame->GetTransform()->SetLocalPosition(Vector2(140.f, -40.f));
	explainWareHouseGame->GetTransform()->SetSize(Vector2(136.f, 124.f));
	// Image
	ImageRenderer* WareHouseGameImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainWareHouseGame", L"/Minigame/mini_game_A1.png")->GetImage());
	explainWareHouseGame->AddComponent(WareHouseGameImage);
	// Add Object
	AddObjectChild(explainWareHouseGame);


}

WarehouseGame::~WarehouseGame()
{

}
