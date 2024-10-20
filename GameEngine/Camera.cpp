#include "pch.h"
#include "Camera.h"

#include "GameObject.h"
#include "Transform.h"
#include "Input.h"


#include "Scene.h"
#include <algorithm>
#pragma comment(lib, "d2d1.lib")
Camera::Camera()
	: Component(typeid(this).name())
{
	m_ViewSize = Vector2{ 1, 1 };
}

Camera::~Camera()
{

}

void Camera::Start()
{
	if (!m_Scene)
	{
		m_Scene = GetGameObject()->GetScene();
	}
}

void Camera::Update(float deltaTime)
{

}

void Camera::Render()
{
#pragma region 나중에 할거..?
	const vector<GameObject*>& gameObjects = m_Scene->GetGameObjects();
	vector<GameObject*> founds;

	size_t rIndex = 0;

	for (auto& motherObject : gameObjects)
	{
		if (motherObject->GetObjectType() >= OBJECT_TYPE::UI) continue;
		founds.push_back(motherObject);
		// bst
		while (founds.size() > rIndex)
		{
			vector<GameObject*>& rChild = founds[rIndex]->GetObjectChildren();
			founds.insert(founds.end(), rChild.begin(), rChild.end());
			rIndex++;
		}

	}


	std::sort(founds.begin(), founds.end(),
		[](GameObject* first, GameObject* second)->bool
		{
			return first->GetObjectType() < second->GetObjectType();
		}
	);

	auto iterStart = founds.begin();
	for (; iterStart != founds.end(); ++iterStart)
	{
		if ((*iterStart)->GetObjectType() == OBJECT_TYPE::ANIMAL)
		{
			break;
		}
	}

	auto iterEnd = founds.begin();
	for (; iterEnd != founds.end(); ++iterEnd)
	{
		if ((*iterEnd)->GetObjectType() == OBJECT_TYPE::TEXTBUBBLE)
		{
			break;
		}
	}
	
	std::sort(iterStart, iterEnd,
		[](GameObject* first, GameObject* second)->bool
		{
			return first->GetTransform()->GetWorldPosition().y < second->GetTransform()->GetWorldPosition().y;
		}
	);

	for (auto& gameObject : founds)
	{
		// 카메라의 월드 변환 행렬을 가져온다.
		D2D1::Matrix3x2F cameraMatrix = GetTransform()->GetWorldMatrix();

		// 월드 변환 행렬을 뒤집어서 화면의 원점 (0, 0)으로 옮기고
		// 카메라의 위치를 화면의 중심으로 보기 때문에 화면의 원점을 중앙으로 옮김
		D2D1InvertMatrix(&cameraMatrix);
		cameraMatrix.dx += static_cast<float>(GraphicsEngine::GetInstance()->GetClientSize().width) / 2;
		cameraMatrix.dy += static_cast<float>(GraphicsEngine::GetInstance()->GetClientSize().height) / 2;

		// 오브젝트의 뷰 행렬을 설정
		gameObject->GetTransform()->SetViewMatrix(cameraMatrix);

		// 오브젝트 렌더링
		gameObject->Render();
	}
#pragma endregion


#pragma region  원래 렌더
// 	for (auto& gameObject : m_Scene->GetGameObjects())
// 	{
// 		for (int i = 0; i < static_cast<int>(OBJECT_TYPE::UI); ++i)
// 		{
// 			if (gameObject->GetObjectType() == static_cast<OBJECT_TYPE>(i))
// 			{
// 				// 카메라의 월드 변환 행렬을 가져온다.
// 				D2D1::Matrix3x2F cameraMatrix = GetTransform()->GetWorldMatrix();
// 
// 				// 월드 변환 행렬을 뒤집어서 화면의 원점 (0, 0)으로 옮기고
// 				// 카메라의 위치를 화면의 중심으로 보기 때문에 화면의 원점을 중앙으로 옮김
// 				D2D1InvertMatrix(&cameraMatrix);
// 				cameraMatrix.dx += static_cast<float>(GraphicsEngine::GetInstance()->GetClientSize().width) / 2;
// 				cameraMatrix.dy += static_cast<float>(GraphicsEngine::GetInstance()->GetClientSize().height) / 2;
// 
// 				// 오브젝트의 뷰 행렬을 설정
// 				gameObject->GetTransform()->SetViewMatrix(cameraMatrix);
// 
// 				// 오브젝트 렌더링
// 				gameObject->Render();
// 			}
// 		}
// 	}
#pragma endregion

}

void Camera::DebugRender()
{
	const vector<GameObject*>& gameObjects = m_Scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetObjectType() >= OBJECT_TYPE::UI) continue;

		gameObject->DebugRender();

	}

}
