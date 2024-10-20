#include "pch.h"
#include "Transform.h"

#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"

Transform::Transform()
	: Component(typeid(this).name())
	, m_Children{}
{

}

Transform::~Transform()
{

}

void Transform::Start()
{

}

void Transform::Update(float deltaTime)
{
	// �� �����Ӹ��� ���� �� ���� ��ȯ ����� ������Ʈ
	UpdateTransform();
}

void Transform::FixedUpdate(float deltaTime)
{
	
}

void Transform::Render()
{
	UpdateTransform();
	for (auto& children : m_Children)
	{
		// �ڽĵ��� �� ����� ���� ��ķ� ����
		children->SetViewMatrix(m_ViewMatrix);
	}

	// ���� �� �� ��ȯ ����� ���� MV ��ȯ ����� ���
	CalculateWVMatrix();

	// �׷��� ������ MV ��ȯ ����� ����
	GraphicsEngine::GetInstance()->SetTransform(m_MVMatrix);
}

void Transform::DebugRender()
{
	Render();
}

void Transform::Finalize()
{

}


void Transform::UpdateTransform()
{
	// SRT ����  
	// ���ð����� ���ʴ�� �����ָ� �װ� �ٷ� �θ��� ��ǥ��� �Ѿ �� �ִ� ��ȯ����̴�. 
	D2D1::Matrix3x2F matScale = D2D1::Matrix3x2F::Scale({ m_LocalScale.x, m_LocalScale.y });
	D2D1::Matrix3x2F matRotation = D2D1::Matrix3x2F::Rotation(m_LocalRotation);
	D2D1::Matrix3x2F matTranslation = D2D1::Matrix3x2F::Translation({ m_LocalPosition.x, m_LocalPosition.y });

	m_MatrixLocal = matScale * matRotation * matTranslation;

	// �� �κ��� ���庯ȯ ����� ���ϴ� ���̵ȴ�.
	if (HasParent())
	{
		m_MatrixWorld = m_MatrixLocal * m_Parent->GetWorldMatrix();
	}

	// �θ� ���ٸ� SRT �������� ���س� �θ� ��ǥ��� �Ѿ�� ��ȯ����� ���� ��ǥ�� ��� ��.
	else
	{
		m_MatrixWorld = m_MatrixLocal;
	}
}

void Transform::CalculateWVMatrix()
{
	// ���� ��ȯ ��İ� �� ��ȯ ����� ���Ͽ� MV ��ȯ ����� ���
	m_MVMatrix = m_MatrixWorld * m_ViewMatrix;
}

void Transform::AddChild(Transform* child)
{
	// �ڽ��� ����Ʈ�� �߰��ϰ�, �ڽ��� �θ� ���� Transform ���� ����
	m_Children.push_back(child); 

	child->SetParent(this);
}