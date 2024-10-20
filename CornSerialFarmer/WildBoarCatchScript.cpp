#include "WildBoarCatchScript.h"
#include "Transform.h"
#include "Animator.h"
#include "Input.h"
#include "Bound.h"
#include "GameObject.h"
// Sound
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Sound.h"

#include "EventManager.h"
#include "GameplayStatics.h"
#include "Animator.h"
#include "Image.h"

WildBoarCatchScript::WildBoarCatchScript() :
	MonoBehaviour(typeid(this).name())
{
}

WildBoarCatchScript::~WildBoarCatchScript()
{
}

void WildBoarCatchScript::Start()
{
	GameplayStatics::PauseGame();

	Vector2 pos = m_Transform->GetLocalPosition();
	pos.x = -700.f;
	m_Transform->SetLocalPosition(pos);
	EventManager::GetInstance()->RegisterClient("CountDownEnd", MakeCallInfo(&WildBoarCatchScript::CountDownEnd));
}

void WildBoarCatchScript::CountDownEnd(std::any)
{
	GameplayStatics::ResumeGame();

	EventManager::GetInstance()->SendEvent("WildBoarFail", nullptr);
	GameplayStatics::DestroyObject(this->GetGameObject()->GetObjectParent());
}

void WildBoarCatchScript::Update(float deltaTime)
{

	Transform* parentTransform = m_Transform->GetParent();
	Vector2 motherPos = parentTransform->GetWorldPosition();
	Vector2 motherSize = parentTransform->GetSize();
	float motherLowerX = motherPos.x - motherSize.x / 2.f;
	float motherUpperX = motherPos.x + motherSize.x / 2.f;
	
	Vector2 lowerBound = m_Transform->GetWorldPosition() - m_Transform->GetSize() / 2.f;
	Vector2 upperBound = m_Transform->GetWorldPosition() + m_Transform->GetSize() / 2.f;
	float m_LowerX = lowerBound.x;
	float m_UpperX = upperBound.x;


	if (m_LowerX <= motherLowerX && m_HP > 0) m_Sign = 1;
	if (m_UpperX >= motherUpperX && m_HP > 0) m_Sign = -1;
	Vector2 pos = m_Transform->GetLocalPosition();
	pos += static_cast<float>(m_Sign) * Vector2::X() * 300 * deltaTime * static_cast<float>(4 - m_HP);
	m_Transform->SetLocalPosition(pos);

	if (pos.y < -70.f)
	{
		m_IsJump = false;
	}
	if (pos.y < 0.f && m_IsJump == false)
	{

		pos.y += 600 * deltaTime;
		m_Transform->SetLocalPosition(pos);
	}

	if (m_Sign > 0)
	{
		m_Anim->Play(L"BoarRight", true);
	}
	else
	{
		m_Anim->Play(L"BoarLeft", true);
	}




	if (Input::GetKeyDown(KEY::LBTN))
	{
		Bound clickBound{ lowerBound, upperBound };
		if (clickBound.Contains(Input::GetMousePos()) && m_HP > 0 && !m_IsHit)
		{
			m_HitAnim->GetTransform()->SetLocalPosition(Input::GetMousePos() -
				m_HitAnim->GetGameObject()->GetObjectParent()->GetTransform()->GetLocalPosition());

			// Animation
			m_HitAnim->Play(L"HitEffect", false);

			// SFX
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"PunchSFX", L"/Sound/SFX/MiniGame/Hit_Punch.mp3")->GetSound());

			m_HP--;
			m_Sign = -m_Sign;
			m_IsHit = true;
			m_IsJump = true;
		}
	}
	if (m_IsHit)
	{
		m_ElipseTime += deltaTime;
		if (m_ElipseTime > 1.f)
		{
			m_IsHit = false;
			m_ElipseTime = 0.f;
		}
	}

	if (m_HP == 0)
	{
		if (!m_IsClear)
		{
			EventManager::GetInstance()->SendEvent("CountDownStop", nullptr);

			// SFX
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"HogSFX", L"/Sound/SFX/MiniGame/hog_squeak.mp3")->GetSound());
		}
		
		m_IsClear = true;
		if (fabs(m_Transform->GetLocalPosition().x) > 1500.f)
		{
			GameplayStatics::ResumeGame();
			EventManager::GetInstance()->SendEvent("WildBoarClear", nullptr);
			GameplayStatics::DestroyObject(this->GetGameObject()->GetObjectParent());
		}
	}
	
	if (m_IsJump)
	{
		Vector2 pos = m_Transform->GetLocalPosition();
		pos.y -= 600 * deltaTime;
		m_Transform->SetLocalPosition(pos);
	}

	
}

void WildBoarCatchScript::FixedUpdate(float deltaTime)
{
}

void WildBoarCatchScript::Finalize()
{
}
