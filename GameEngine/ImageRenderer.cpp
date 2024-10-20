#include "pch.h"
#include "ImageRenderer.h"
#include "GameObject.h"
#include "Transform.h"

ImageRenderer::ImageRenderer(
	ID2D1Bitmap* image,
	Vector2 positionOffset,
	Vector2 sliceStartPos,
	Vector2 sliceSize)
	: m_Image(image)
	, m_PositionOffset(positionOffset)
	, m_SliceStartPos(sliceStartPos)
	, m_SliceSize(sliceSize)
	, m_AdditionalOffset{}
	, m_ActiveFadeIn(false)
	, m_ActiveFadeOut(false)
	, m_TimePassed(0.f)
	, m_FadeValue(0.f)
	, m_Opacity(1.f)
	, m_IsActivate(true)
{

}

ImageRenderer::~ImageRenderer()
{

}

void ImageRenderer::Start()
{
	m_Size = GetGameObject()->GetTransform()->GetSize();
}

void ImageRenderer::Update(float deltaTime)
{
	ApplyFadeInOut(deltaTime);
}

void ImageRenderer::FixedUpdate(float deltaTime)
{

}

void ImageRenderer::Render()
{
	if (!GetGameObject()->GetActivate()) return;
	if (!m_IsActivate) return;

	GraphicsEngine::GetInstance()->ShowImage(
		m_Image,
		Vector2(m_PositionOffset.x, m_PositionOffset.y),
		Vector2(m_Size.x, m_Size.y),
		Vector2(m_SliceStartPos.x, m_SliceStartPos.y),
		Vector2(m_SliceSize.x, m_SliceSize.y),
		m_AdditionalOffset,
		m_Opacity
	);

}

void ImageRenderer::Finalize()
{

}

void ImageRenderer::FadeIn(float outputTime)
{
	m_Opacity = 0.f;
	m_ActiveFadeIn = true;
	m_FadeValue = 1.f / outputTime;
}

void ImageRenderer::FadeOut(float outputTime)
{
	m_Opacity = 1.f;
	m_ActiveFadeOut = true;
	m_FadeValue = 1.f / outputTime ;
}

void ImageRenderer::ApplyFadeInOut(float deltaTime)
{
	if (!m_ActiveFadeIn && !m_ActiveFadeOut) return;

	m_TimePassed += deltaTime;

	if (m_TimePassed >= 0.1f)
	{
		// Pade In
		if (m_ActiveFadeIn)
		{
			m_Opacity += m_FadeValue * m_TimePassed;
			if (m_Opacity >= 1.f)
			{
				m_ActiveFadeIn = false;
				m_Opacity = 1.f;
			}
		}

		// Pade Out
		else if (m_ActiveFadeOut)
		{
			m_Opacity -= m_FadeValue * m_TimePassed;
			if (m_Opacity <= 0.f)
			{
				m_ActiveFadeOut = false;
				m_Opacity = 0.f;
			}
		}

		m_TimePassed = 0.f;
	}
}