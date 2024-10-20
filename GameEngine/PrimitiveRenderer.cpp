#include "pch.h"
#include "PrimitiveRenderer.h"
#include "Transform.h"

PrimitiveRenderer::PrimitiveRenderer()
{
}

PrimitiveRenderer::PrimitiveRenderer(string name) :
	Renderer(typeid(this).name())
{
}


PrimitiveRenderer::~PrimitiveRenderer()
{
}

void PrimitiveRenderer::Start()
{
}

void PrimitiveRenderer::Update(float deltaTime)
{
}

void PrimitiveRenderer::FixedUpdate(float deltaTime)
{
}

void PrimitiveRenderer::Render()
{
	Vector2 size = m_Transform->GetSize();
	if (!m_PrimitiveType.compare("Circle"))
	{
		GraphicsEngine::GetInstance()->DrawEllipse(Vector2(0, 0), size, COLOR::WHITE);
	}
	else if (!m_PrimitiveType.compare("Rectangle"))
	{
		GraphicsEngine::GetInstance()->DrawRectangle(Vector2(0, 0), size, COLOR::WHITE);
	}
	else if (!m_PrimitiveType.compare("FillRectangle"))
	{
		GraphicsEngine::GetInstance()->DrawRectangle(Vector2(0, 0), size, COLOR::BABYBLUE, 1.0f, true);
	}
}

void PrimitiveRenderer::Finalize()
{
}
