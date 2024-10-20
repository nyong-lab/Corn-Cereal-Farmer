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
	// 매 프레임마다 로컬 및 월드 변환 행렬을 업데이트
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
		// 자식들의 뷰 행렬을 현재 행렬로 설정
		children->SetViewMatrix(m_ViewMatrix);
	}

	// 월드 및 뷰 변환 행렬을 곱해 MV 변환 행렬을 계산
	CalculateWVMatrix();

	// 그래픽 엔진에 MV 변환 행렬을 설정
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
	// SRT 공식  
	// 로컬값들을 차례대로 곱해주면 그게 바로 부모의 좌표계로 넘어갈 수 있는 변환행렬이다. 
	D2D1::Matrix3x2F matScale = D2D1::Matrix3x2F::Scale({ m_LocalScale.x, m_LocalScale.y });
	D2D1::Matrix3x2F matRotation = D2D1::Matrix3x2F::Rotation(m_LocalRotation);
	D2D1::Matrix3x2F matTranslation = D2D1::Matrix3x2F::Translation({ m_LocalPosition.x, m_LocalPosition.y });

	m_MatrixLocal = matScale * matRotation * matTranslation;

	// 이 부분이 월드변환 행렬을 구하는 식이된다.
	if (HasParent())
	{
		m_MatrixWorld = m_MatrixLocal * m_Parent->GetWorldMatrix();
	}

	// 부모가 없다면 SRT 공식으로 구해낸 부모 좌표계로 넘어가는 변환행렬이 월드 좌표계 라는 것.
	else
	{
		m_MatrixWorld = m_MatrixLocal;
	}
}

void Transform::CalculateWVMatrix()
{
	// 월드 변환 행렬과 뷰 변환 행렬을 곱하여 MV 변환 행렬을 계산
	m_MVMatrix = m_MatrixWorld * m_ViewMatrix;
}

void Transform::AddChild(Transform* child)
{
	// 자식을 리스트에 추가하고, 자식의 부모를 현재 Transform 으로 설정
	m_Children.push_back(child); 

	child->SetParent(this);
}