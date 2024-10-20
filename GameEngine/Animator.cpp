#include "pch.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator(ID2D1Bitmap* spriteSheet)
	: m_AnimationBox{}
	, m_CurrentAnimation(nullptr)
	, m_IsRepeat(false)
	, m_SpriteSheet(spriteSheet)
{

}

Animator::~Animator()
{

}

void Animator::Start()
{

}

void Animator::Update(float deltaTime)
{
	if (m_CurrentAnimation == nullptr) return;

	m_CurrentAnimation->Update(deltaTime);
	if (m_IsRepeat && m_CurrentAnimation->IsAnimationFinished())
		m_CurrentAnimation->SetFrame(0);
}

void Animator::FixedUpdate(float deltaTime)
{

}

void Animator::Render()
{
	if (m_CurrentAnimation == nullptr) return;
	m_CurrentAnimation->Render();
}

void Animator::Finalize()
{
	for (auto& iter : m_AnimationBox) {
		if (iter.second != nullptr)
		{
			delete iter.second;
		}
	}
}

void Animator::CreateAnimation(
	const wstring& name,
	Vector2 offset,
	Vector2 frameSize,
	Vector2 startSlicePos,
	Vector2 sliceSize,
	float duration,
	int frameCount)
{
	if (FindAnimation(name) != nullptr) return;
	Animation* animation = new Animation();
	animation->SetOwner(this);
	animation->SetName(name);
	animation->CreateAnimation(offset, frameSize, startSlicePos, sliceSize, duration, frameCount);
	m_AnimationBox.insert(make_pair(name, animation));
}

Animation* Animator::FindAnimation(const wstring& name)
{
	// 애니메이션 찾기
	map<wstring, Animation*>::iterator iter = m_AnimationBox.find(name);

	if (iter == m_AnimationBox.end())
		return nullptr;

	return iter->second;
}

void Animator::Play(const wstring& name, bool isRepeat)
{
	m_CurrentAnimation = FindAnimation(name);
	m_CurrentAnimation->SetFinish(false);
	m_IsRepeat = isRepeat;
}

