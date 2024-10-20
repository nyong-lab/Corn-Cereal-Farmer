#include "KeyHoleScript.h"
#include "Transform.h"
#include "Input.h"
#include "EventManager.h"

// Sound
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Sound.h"

KeyHoleScript::KeyHoleScript() :
	MonoBehaviour(typeid(this).name())
{
}

KeyHoleScript::~KeyHoleScript()
{
}

void KeyHoleScript::Start()
{
}

void KeyHoleScript::Update(float deltaTime)
{

	if (m_IsClicked && m_IsEnable)
	{
		const float PI = 3.141592f;
		Vector2 mousePos = Input::GetMousePos() -
			this->GetTransform()->GetWorldPosition();
		mousePos = mousePos.Normalize();
		int sign = 0;
		if (Vector2::Y().Cross(mousePos) >= 0)
			sign = 1;
		else
			sign = -1;
		float rot = acosf(Vector2::Y().Dot(mousePos));
		rot = sign * (rot / PI) * 180.f;
		if (rot < 0) {
			rot = 360.f + rot;
		}

		if (m_PrevRot < rot || rot - m_PrevRot > 350.f)
		{
			m_Inc += 90 * deltaTime;
		}
		m_PrevRot = rot;
		m_Transform->SetLocalRotation(m_Inc);

		OutputDebugString(std::to_wstring(m_Transform->GetLocalRotation()).c_str());
		OutputDebugString(L"\n");
		OutputDebugString(std::to_wstring(m_Transform->GetLocalRotation()).c_str());
		OutputDebugString(L"\n");
	}

	if (m_Inc >= 90.f && m_IsEnable)
	{
		if (!m_IsClear)
		{
			// SFX
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"OpenSFX", L"/Sound/SFX/MiniGame/Unlocked.mp3")->GetSound());
		}
		m_IsEnable = false;
		m_IsClear = true;
		EventManager::GetInstance()->SendEvent("CountDownStop", nullptr);
		EventManager::GetInstance()->SendEvent("WareHouseHelper", nullptr);
	}


	if (m_IsClear)
	{
		m_ElipseTime += deltaTime;
		if (m_ElipseTime >= DELAY_TIME)
		{
			// 사운드 타이밍 여기가 맞는듯
			if (!m_OpenDoorSound)
			{
				// SFX
				SoundManager::GetInstance()->PlaySoundSFX(
					ResourceManager::GetInstance()->LoadResource<Sound>(L"DoorSFX", L"/Sound/SFX/MiniGame/Door_Open.mp3")->GetSound());

				m_OpenDoorSound = true;
			}

			Vector2 pos = m_Transform->GetLocalPosition();
			pos += Vector2::Y() * 500 * deltaTime;
			m_Transform->SetLocalPosition(pos);
		}

	}
}

void KeyHoleScript::FixedUpdate(float deltaTime)
{
}

void KeyHoleScript::Finalize()
{
}
