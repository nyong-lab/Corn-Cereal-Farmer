#include "FarmerAim.h"

#include "GameObject.h"
#include "Input.h"
#include "Collider.h"
#include "FarmScript.h"
#include "Transform.h"

#include "Define.h"
#include <string>
using std::string;

#include "GameManagerScript.h"
#include "ObjectDataScript.h"
#include "BlackCatScript.h"
#include "QuestManagerScript.h"


FarmerAim::FarmerAim()
	: MonoBehaviour(typeid(this).name())
	, m_GameManagerScript(nullptr)
{

}

FarmerAim::~FarmerAim()
{

}

void FarmerAim::Start()
{

}

void FarmerAim::Update(float deltaTime)
{
	/*if (Input::GetKey(KEY::RIGHT))
	{
		GetGameObject()->GetComponent<Collider>()->GetTransform()->SetLocalPosition({ 30.f, 30.f });
	}
	if (Input::GetKey(KEY::LEFT))
	{
		GetGameObject()->GetComponent<Collider>()->GetTransform()->SetLocalPosition({ -30.f, 30.f });
	}
	if (Input::GetKey(KEY::UP))
	{
		GetGameObject()->GetComponent<Collider>()->GetTransform()->SetLocalPosition({ 0.f, -50.f });
	}
	if (Input::GetKey(KEY::DOWN))
	{
		GetGameObject()->GetComponent<Collider>()->GetTransform()->SetLocalPosition({ 0.f, 80.f });
	}*/
}

void FarmerAim::FixedUpdate(float deltaTime)
{

}

void FarmerAim::Finalize()
{

}

void FarmerAim::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::FARM)
	{
		if (collision.otherObject->GetObjectParent())
		{
			int nameIndex = dynamic_cast<FarmScript*>(collision.otherObject->GetObjectParent()->GetComponent<MonoBehaviour>())->farmNumber;
			if (collision.otherObject->GetObjectParent()->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectParent()->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex))->SetActivate(true);
			}
			else if (collision.otherObject->GetObjectParent()->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectParent()->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex))->SetActivate(true);
			}
		}
		else
		{
			int nameIndex = dynamic_cast<FarmScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->farmNumber;
			if (collision.otherObject->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex))->SetActivate(false);
			}
			else if (collision.otherObject->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex))->SetActivate(false);
			}
		}
	}
}

void FarmerAim::OnCollisionStay(const Manifold& collision)
{
	if (Input::GetKeyDown(KEY::SPACE))
	{
		if (collision.otherObject->GetObjectType() == OBJECT_TYPE::FARM)
		{
			// ¹ç Äù½ºÆ® °ü·Ã
			for (auto& iter : m_GameManagerScript->m_QuestManager->m_QuestObjects)
			{
				if (iter == collision.otherObject)
				{
					m_GameManagerScript->Interaction(collision.otherObject);

					break;
				}
			}
		}
	}
}

void FarmerAim::OnCollisionExit(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::FARM)
	{
		if (collision.otherObject->GetObjectParent())
		{
			int nameIndex = dynamic_cast<FarmScript*>(collision.otherObject->GetObjectParent()->GetComponent<MonoBehaviour>())->farmNumber;
			if (collision.otherObject->GetObjectParent()->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectParent()->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex))->SetActivate(false);
			}
			else if (collision.otherObject->GetObjectParent()->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectParent()->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex))->SetActivate(false);
			}
		}
		else
		{
			int nameIndex = dynamic_cast<FarmScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->farmNumber;
			if (collision.otherObject->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectChild("FirstFarmChildSelect" + std::to_string(nameIndex))->SetActivate(false);
			}
			else if (collision.otherObject->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex)))
			{
				collision.otherObject->GetObjectChild("SecondFarmChildSelect" + std::to_string(nameIndex))->SetActivate(false);
			}
		}
	}


}
