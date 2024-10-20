#include "BubblePopScript.h"
#include "GameObject.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "Transform.h"
#include "Bound.h"

BubblePopScript::BubblePopScript() :
	MonoBehaviour(typeid(this).name())
{

}

BubblePopScript::~BubblePopScript()
{
}

void BubblePopScript::Start()
{
	for (auto& bubble : m_BubbleUI)
	{
		bubble->CreateAnimation(L"Empty", {}, {}, { 0,0 }, { 0,0.f }, 1.f, 1);
		bubble->CreateAnimation(L"QMDown", {}, { 136.f, 120.f }, { 0,0 }, { 136.f,0.f }, 0.2f, 4);
		bubble->CreateAnimation(L"QMUp", {}, { 136.f, 120.f }, { 0.f,120.f }, { 136.f,0.f }, 0.2f, 4);
		bubble->CreateAnimation(L"QMLeft", {}, { 136.f, 120.f }, { 0.f,240.f }, { 136.f,0.f }, 0.2f, 4);
		bubble->CreateAnimation(L"QMRight", {}, { 136.f, 120.f }, { 0.f,360.f }, { 136.f,0.f }, 0.2f, 4);

	}

}

void BubblePopScript::Update(float deltaTime)
{
	Vector2 cameraPos = m_Camera->GetTransform()->GetWorldPosition();
	Bound cameraBound{ cameraPos.x, cameraPos.y, 1920.f, 1080.f };


	for (int i = 0; i < (int)m_NPCBubble.size(); ++i)
	{

		if (m_NPCBubble[i]->GetCurrentAnimation() && m_NPCBubble[i]->GetCurrentAnimation()->GetName() == L"QuestionMark")
		{
			Vector2 bubblePos = m_NPCBubble[i]->GetTransform()->GetWorldPosition() - Vector2::Y() * 120.f;
			Bound bubbleBound{ bubblePos.x, bubblePos.y, 128.f, 120.f };
			if (cameraBound.Intersects(bubbleBound))
			{
				m_BubbleUI[i]->Play(L"Empty", true);

				
				
			}
			else
			{
				Vector2 direction = bubblePos - cameraPos;
				Vector2 uiVector = direction;
				if (fabs(direction.x) > 960.f)
				{
					uiVector.x = direction.x / fabs(direction.x) * (960.f - 136.f);
				}
				if (fabs(direction.y) > 540.f)
				{
					uiVector.y = direction.y / fabs(direction.y) * (540.f - 120.f);
				}

				m_BubbleUI[i]->GetTransform()->SetLocalPosition(Vector2{ 960.f, 540.f } + uiVector);
				
				if (uiVector.y > 0 && fabs(direction.y) > 540.f)
				{
					m_BubbleUI[i]->Play(L"QMDown", true);
				}
				else if (uiVector.y < 0 && fabs(direction.y) > 540.f)
				{
					m_BubbleUI[i]->Play(L"QMUp", true);
				}
				
				if (uiVector.x > 0 && fabs(direction.x) > 960.f)
				{
					m_BubbleUI[i]->Play(L"QMRight", true);
				}
				else if (uiVector.x < 0 && fabs(direction.x) > 960.f)
				{
					m_BubbleUI[i]->Play(L"QMLeft", true);
				}
			}

		}
	}
	
}

void BubblePopScript::FixedUpdate(float deltaTime)
{

}

void BubblePopScript::Finalize()
{

}
