#include "pch.h"
#include "UI.h"
#include "Input.h"
#include "GameObject.h"
#include "Transform.h"

UI::UI()
	: m_parentUI(nullptr)
	, m_MouseOn(false)
	, m_LeftButtonDown(false)
{

}

UI::~UI()
{

}

void UI::Start()
{
	if (GetGameObject()->GetObjectParent())
		m_parentUI = GetGameObject()->GetObjectParent()->GetComponent<UI>();
}

void UI::Update(float deltaTime)
{

}

void UI::FixedUpdate(float deltaTime)
{
	// Mouse Check
	MouseOnCheck();
}

void UI::Render()
{

}

void UI::Finalize()
{

}

void UI::MouseOn()
{

}

void UI::MouseLeftButtonDown()
{

}

void UI::MouseLeftButtonUp()
{

}

void UI::MouseLeftButtonClick()
{

}

void UI::MouseOnCheck()
{
	/// 마우스 범위와 매칭시키기 위해 Position 계산 필요
	// 자기가 갖고있는 Transform의 LocalPosition을 받아온다
	m_FinalPosition = GetTransform()->GetLocalPosition();

	// 부모가 있으면 부모의 위치를 더해주기
	bool hasParent = GetTransform()->HasParent();
	if (hasParent)
	{
		D2D1_MATRIX_3X2_F worldMatrix = GetTransform()->GetParent()->GetWorldMatrix();
		m_FinalPosition += {worldMatrix.dx, worldMatrix.dy};
	}

	Vector2 mousePosition = Input::GetMousePos();
	Vector2 size = GetTransform()->GetSize();

	// 마우스가 UI의 범위 내에 있어야만 MouseOn true처리
	// 우리 엔진에서는 그림이 원점을 가운데로 그려짐
	if (((m_FinalPosition.x - size.x / 2) <= mousePosition.x) &&
		((m_FinalPosition.y - size.y / 2) <= mousePosition.y) &&
		(mousePosition.x <= (m_FinalPosition.x + size.x / 2)) &&
		(mousePosition.y <= (m_FinalPosition.y + size.y / 2)))
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
}