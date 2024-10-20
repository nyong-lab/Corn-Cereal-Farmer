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
	/// ���콺 ������ ��Ī��Ű�� ���� Position ��� �ʿ�
	// �ڱⰡ �����ִ� Transform�� LocalPosition�� �޾ƿ´�
	m_FinalPosition = GetTransform()->GetLocalPosition();

	// �θ� ������ �θ��� ��ġ�� �����ֱ�
	bool hasParent = GetTransform()->HasParent();
	if (hasParent)
	{
		D2D1_MATRIX_3X2_F worldMatrix = GetTransform()->GetParent()->GetWorldMatrix();
		m_FinalPosition += {worldMatrix.dx, worldMatrix.dy};
	}

	Vector2 mousePosition = Input::GetMousePos();
	Vector2 size = GetTransform()->GetSize();

	// ���콺�� UI�� ���� ���� �־�߸� MouseOn trueó��
	// �츮 ���������� �׸��� ������ ����� �׷���
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