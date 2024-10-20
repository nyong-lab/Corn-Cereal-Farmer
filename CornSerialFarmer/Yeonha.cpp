#include "Yeonha.h"

#include "EventManager.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

#include "CircleCollider.h"
#include "Image.h"
#include "Animator.h"

#include "../GraphicsEngine/GraphicsEngine.h"
#include "ImageRenderer.h"

// Prefab
#include "PauseButton.h"
#include "TimeBar.h"
#include "ItemSlot.h"
#include "QuestList.h"

#include "GameManagerScript.h"
#include "ItemManagerScript.h"
#include "CameraScript.h"

void Yeonha::Enter()
{
	// 배경
	GameObject* background = new GameObject("Background", OBJECT_TYPE::BACKGROUND);
	background->GetTransform()->SetLocalPosition(Vector2(952.f, 520.f));
	background->GetTransform()->SetSize({ 2400.f, 1350.f });
	ImageRenderer* backgroundRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"BackGround", L"/Image/floor/floor_test.png")->GetImage(),
		{ 0.f, 0.f }, { 0.f, 0.f }, { 2400.f, 1350.f }
	);
	background->AddComponent(backgroundRender);
	AddGameObject(background);

	// 카메라
	GameObject* cameraObject = new GameObject("CameraObject", OBJECT_TYPE::CAMERA);
	Camera* camera = new Camera;
	cameraObject->AddComponent(camera);
	AddGameObject(cameraObject);
	CameraScript* cameraScript = new CameraScript;
	cameraObject->AddComponent(cameraScript);

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

	/// ----------------------------------------------------------------------

	/// Game Manager
	GameObject* gameManaer = new GameObject("GameManager", OBJECT_TYPE::DEFAULT);
	gameManaer->SetScene(this);
	GameManagerScript* gameManagerScript = new GameManagerScript();
	gameManaer->AddComponent(gameManagerScript);

	gameManagerScript->m_TimeBar = (TimeBar*)timeBar;
	AddGameObject(gameManaer);

	/// Item Manager
	GameObject* itemManager = new GameObject("ItemManager", OBJECT_TYPE::DEFAULT);
	gameManaer->SetScene(this);
	ItemManagerScript* itemManagerScript = new ItemManagerScript();
	gameManaer->AddComponent(itemManagerScript);

	AddGameObject(itemManager);
	itemManagerScript->m_ItemSlot = (ItemSlot*)itemSlot;

	/// Quest Manager
}
