#include "ChangdoScene.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Camera.h"
#include "CameraScript.h"
#include "BoxCollider.h"
#include "PrimitiveRenderer.h"
#include "ChangdoScript.h"
#include "Transform.h"
#include "TImeScript.h"
#include "TextRenderer.h"
#include "Panel.h"
#include "Random.h"
#include "PolygonCollider.h"
void ChangdoScene::Enter()
{
	EventManager::GetInstance()->CheckCollisionType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PLAYER);

	/// Camera
	GameObject* cameraObject = new GameObject("CameraObject", OBJECT_TYPE::CAMERA);
	Camera* camera = new Camera;
	cameraObject->GetTransform()->SetLocalPosition({ 1920.f * 0.5f, 1080.f * 0.5f });
	//CameraScript* cameraScript = new CameraScript;
	cameraObject->AddComponent(camera);
	//cameraObject->AddComponent(cameraScript);
	AddGameObject(cameraObject);

	/// Ã¢µµ UI
	GameObject* frameTextUI = new GameObject("FrameTextUI", OBJECT_TYPE::UI);
	Panel* panel = new Panel;
	frameTextUI->AddComponent(panel);
	TImeScript* timeScript = new TImeScript;
	frameTextUI->AddComponent(timeScript);
	TextRenderer* frameRender = new TextRenderer({ 0,0 }, L"");
	frameTextUI->AddComponent(frameRender);
	timeScript->m_TextRenderer = frameRender;
	AddGameObject(frameTextUI);

	// 	for (int i = 0; i < 100; ++i)
	// 	{
	// 		GameObject* gameObject = new GameObject("GameObejct", OBJECT_TYPE::PLAYER);
	// 		BoxCollider* box = new BoxCollider(Vector2(200, 200));
	// 		gameObject->AddComponent(box);
	// 		ChangdoScript* cd = new ChangdoScript;
	// 		gameObject->AddComponent(cd);
	// 		TextRenderer* test = new TextRenderer(Vector2(0, 0), L"");
	// 		gameObject->AddComponent(test);
	// 		cd->m_Collider = box;
	// 		cd->m_Render = test;
	// 		AddGameObject(gameObject);
	// 	}
	{
		GameObject* gameObject = new GameObject("GameObejct", OBJECT_TYPE::PLAYER);
		BoxCollider* box = new BoxCollider(Vector2(200, 200));
		gameObject->AddComponent(box);
		// 		ChangdoScript* cd = new ChangdoScript;
		// 		gameObject->AddComponent(cd);
		gameObject->GetTransform()->SetLocalPosition({ 600,600 });

		AddGameObject(gameObject);
	}
 
 	{
 		GameObject* gameObject = new GameObject("GameObejct", OBJECT_TYPE::PLAYER);
		gameObject->GetTransform()->SetLocalPosition({ 600,600 });
 		BoxCollider* box = new BoxCollider(Vector2(100, 200));
 		gameObject->AddComponent(box);
 		ChangdoScript* cd = new ChangdoScript;
 		gameObject->AddComponent(cd);
 		TextRenderer* test = new TextRenderer(Vector2(0, 0), L"");
 		gameObject->AddComponent(test);
 		cd->m_Collider = box;
 		cd->m_Render = test;
 		AddGameObject(gameObject);
 	}

	{
// 		GameObject* gameObject = new GameObject("GameObejct", OBJECT_TYPE::PLAYER);
// 		PolygonCollider* polygonCollider = new PolygonCollider;
// 		polygonCollider->AddVertice(Vector2(0.f, 250.f));
// 		polygonCollider->AddVertice(Vector2(-100.f, -20.f));
// 		polygonCollider->AddVertice(Vector2(220.f, -40.f));
// 		polygonCollider->AddVertice(Vector2(20.f, -80.f));
// 		polygonCollider->AddVertice(Vector2(-30.f, -90.f));
// 		gameObject->AddComponent(polygonCollider);
// 		ChangdoScript* cd = new ChangdoScript;
// 		gameObject->AddComponent(cd);
// 		TextRenderer* test = new TextRenderer(Vector2(0, 0), L"");
// 		gameObject->AddComponent(test);
// 		cd->m_Collider = polygonCollider;
// 		cd->m_Render = test;
// 		AddGameObject(gameObject);

	}
}
