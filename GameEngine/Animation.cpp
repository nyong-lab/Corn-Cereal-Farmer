#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"

Animation::Animation()
	: m_Owner(nullptr)
	, m_Name(L"")
	, m_Framebox{}
	, m_CurrentFrame(0)
	, m_TimePassed(0.0f)
	, m_IsFinished(false)
{

}

Animation::~Animation()
{

}

void Animation::Update(float deltaTime)
{
	if (m_IsFinished) return;
	if (m_FrameFixed) return;

	m_TimePassed += deltaTime;
	if (m_TimePassed > m_Framebox[m_CurrentFrame].duration)
	{
		m_CurrentFrame++;
		int size = m_Framebox.size();
		if (size <= m_CurrentFrame)
		{
			m_CurrentFrame = -1;
			m_IsFinished = true;
			m_TimePassed = 0.f;
			return;
		}
		m_TimePassed -= m_Framebox[m_CurrentFrame].duration;
	}
}

void Animation::Render()
{
	if (m_IsFinished) return;

	if (GetOwner()->GetGameObject()->GetActivate())
	{
		ID2D1Bitmap* d = m_Owner->GetSpriteSheet();
		GraphicsEngine::GetInstance()->ShowImage(
			m_Owner->GetSpriteSheet(),
			m_Framebox[m_CurrentFrame].animationOffset,
			m_Framebox[m_CurrentFrame].size,
			m_Framebox[m_CurrentFrame].sliceStartposition,
			m_Framebox[m_CurrentFrame].size
		);
	}
}

void Animation::CreateAnimation(
	Vector2 offset,
	Vector2 frameSize,
	Vector2 startSlicePos,
	Vector2 sliceSize,
	float duration,
	int frameCount)
{
	AnimationFrame frame = {};
	for (int i = 0; i < frameCount; i++)
	{
		frame.duration = duration;
		frame.size = frameSize;
		frame.sliceStartposition.x = startSlicePos.x + sliceSize.x * i;
		frame.sliceStartposition.y = startSlicePos.y + sliceSize.y * i;
		frame.animationOffset = offset;
		m_Framebox.push_back(frame);
	}
}

void Animation::SetFrame(int frameIndex)
{
	m_IsFinished = false;
	m_CurrentFrame = frameIndex;
	m_TimePassed = 0.f;
}

void Animation::SetFrameFixed(int frameIndex)
{
	m_FrameFixed = true;
	SetFrame(frameIndex);
}

void Animation::ReleaseFrameFixed()
{
	m_FrameFixed = false;
	SetFrame(0);
}
