#include "CameraScript.h"


#include "Define.h"
#include "ZicoMath.h"
#include "Transform.h"
#include "Input.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "GameObject.h"
#include "Mathf.h"
#include "Scene.h"
#include "SoundManager.h"
#include "Sound.h"
#include "ResourceManager.h"


CameraScript::CameraScript() 
	: MonoBehaviour(typeid(this).name())
	, m_SmoothMoveToTarget(false)
	, m_Target(nullptr)
	, m_TargetOn(true)
	, m_MoveCamera(false)
{

}

CameraScript::~CameraScript()
{

}

void CameraScript::Start()
{

}

void CameraScript::Update(float deltaTime)
{
	/// 개발자 카메라 
	CheatMode(deltaTime);

	Vector2 scale = m_Transform->GetLocalScale();
	Vector2 pos = m_Transform->GetLocalPosition();
	Vector2 targetPosition = m_Target->GetTransform()->GetLocalPosition();

	float move = 1000.f;

	static bool xEnd = false;
	static bool yEnd = false;
	static int xCount = 0;
	static int yCount = 0;
	static int endCount = 0;
	static bool isSound = true;

	

	if (m_SmoothMoveToTarget)
	{
		/*if (scale.x < 1.1f && scale.y < 1.1f)
		{
			scale += {deltaTime * 0.25f, deltaTime * 0.25f };
		}*/

		if (!xEnd)
		{
			if (pos.x > targetPosition.x)
			{
				pos.x -= move * deltaTime;
			}
			else if (pos.x < targetPosition.x)
			{
				pos.x += move * deltaTime;
			}
		}
		
		if (!yEnd)
		{
			if (pos.y > targetPosition.y)
			{
				pos.y -= move * deltaTime;
			}
			else if (pos.y < targetPosition.y)
			{
				pos.y += move * deltaTime;
			}
		}

		/*if (fabs(pos.x - targetPosition.x) < 10 && fabs(pos.y - targetPosition.y) < 10)
		{
			m_MoveCamera = true;
			m_SmoothMoveToTarget = false;
			m_TargetOn = true;
		}*/


		if (fabs(pos.x - targetPosition.x) < 5)
		{
			xEnd = true;
			xCount = 1;
		}
		if (fabs(pos.y - targetPosition.y) < 5)
		{
			yEnd = true;
			yCount = 1;	
		}

		if (xCount == 1 && yCount == 1)
		{
			m_MoveCamera = true;
			m_SmoothMoveToTarget = false;
			m_TargetOn = true;
		}
	} 

	if (m_MoveCamera)
	{
		if (scale.x > 0.7f && scale.y > 0.7f)
		{
			scale -= {deltaTime * 0.4f, deltaTime * 0.4f };
		}
		
		static float time = 0;
		time += deltaTime;

		if (time > 0.6f)
		{
			if (isSound)
			{
				isSound = false;

				if (m_Target->GetName() == "wildBoar")
				{
					SoundManager::GetInstance()->PlaySoundSFX(
						ResourceManager::GetInstance()->LoadResource<Sound>(L"HogSFX", L"/Sound/SFX/MiniGame/hog_squeak.mp3")->GetSound());
				}
				else
				{
					SoundManager::GetInstance()->PlaySoundSFX(
						ResourceManager::GetInstance()->LoadResource<Sound>(L"CatMeowSFX", L"/Sound/SFX/Interaction/Cat_Meow.mp3")->GetSound());
				}
				
			}
		}

		if (time > 2.f)
		{
			m_MoveCamera = false;

			scale = Vector2{ 1.f,1.f };
			time = 0;

			xEnd = false;
			yEnd = false;
			xCount = 0;
			yCount = 0;
			endCount = 0;
			isSound = true;

			for (auto& object : GetGameObject()->GetScene()->GetGameObjects())
			{
				if (object->GetName() == "farmer")
				{
					m_Target = object;
				}
			}
		}
	}

	if (m_TargetOn)
	{
		pos = m_Target->GetTransform()->GetLocalPosition();
	}



	float lx = 4800.f * 0.5f - 1920.f * 0.5f;
	float ly = 2704.f * 0.5f - 1080.f * 0.5f;

	float clampX = Mathf::Clamp(pos.x, -lx + 1920.f * 0.5f, lx + 1920.f * 0.5f);
	float clampY = Mathf::Clamp(pos.y, -ly + 1080.f * 0.5f, ly + 1080.f * 0.5f);

	m_Transform->SetLocalPosition(Vector2(clampX, clampY));
	m_Transform->SetLocalScale(scale);
}

void CameraScript::CheatMode(float deltaTime)
{
	/// 줌 인 : Q 
	/// 줌 아웃 : E
	/// 리셋 : R
	/// 시점 고정 : H 

	Vector2 scale = m_Transform->GetLocalScale();
	Vector2 scaleValue = { deltaTime, deltaTime };
	Vector2 pos = m_Transform->GetLocalPosition();
	Vector2 mouseScreenPos = Input::GetMousePos();
	Vector2 direction = Vector2{ 0.f,0.f };

	/// 카메라 줌 인/아웃
	if (Input::GetKey(KEY::Q))
	{
		scale += scaleValue;
	}

	if (Input::GetKey(KEY::E))
	{
		scale -= scaleValue;
	}

	/// 카메라 리셋
	if (Input::GetKey(KEY::R))
	{
		scale = Vector2{ 1.f,1.f };
		pos = m_Target->GetTransform()->GetLocalPosition();
	}

	///// 마우스로 카메라 이동
	//// 상단 이동
	//if (mouseScreenPos.y <= 50.f)
	//{
	//	direction.y -= 300;
	//}
	//// 하단 이동
	//if (mouseScreenPos.y >= GraphicsEngine::GetInstance()->GetClientSize().height - 50.f)
	//{
	//	direction.y += 300;
	//}
	//// 좌 이동
	//if (mouseScreenPos.x <= 50.f)
	//{
	//	direction.x -= 300;
	//}
	//// 우 이동
	//if (mouseScreenPos.x >= GraphicsEngine::GetInstance()->GetClientSize().width - 50.f)
	//{
	//	direction.x += 300;
	//}

	///// 마우스 보정값 
	//direction.Normalize();
	//pos += direction * 1000.f * deltaTime;

	/// 최종 연산
	m_Transform->SetLocalScale(scale);
	m_Transform->SetLocalPosition(pos);
}
