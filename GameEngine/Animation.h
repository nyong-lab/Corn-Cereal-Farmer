#pragma once
#include <string>
#include <vector>
using std::vector;
using std::wstring;

class Animator;

struct AnimationFrame
{
	Vector2 animationOffset;
	Vector2 size;
	Vector2 sliceStartposition;
	float duration;
};

class Animation
{
public:
	Animation();
	~Animation();

public:
	void Update(float deltaTime);
	void Render();

public:
	void CreateAnimation(
		Vector2 offset,
		Vector2 frameSize,
		Vector2 startSlicePos,
		Vector2 sliceSize,
		float duration,
		int frameCount
	);

public:
	Animator* GetOwner() const { return m_Owner; }
	void SetOwner(Animator* owner) { m_Owner = owner; }
	void SetName(const wstring& name) { m_Name = name; }
	void SetFrame(int frameIndex);
	void SetFinish(bool value) { m_IsFinished = value; }

	int GetCurrentAnimationIndex() { return m_CurrentFrame; }

	void SetFrameFixed(int frameIndex);
	void ReleaseFrameFixed();

	const wstring& GetName() { return m_Name; }
	bool IsAnimationFinished() { return m_IsFinished; }

private:
	Animator* m_Owner;
	wstring m_Name;
	vector<AnimationFrame> m_Framebox;
	int m_CurrentFrame;
	double m_TimePassed;
	bool m_IsFinished;
	bool m_FrameFixed;
};

