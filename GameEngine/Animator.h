/// [2023/08/07] �ڿ���
/// --------------------------
/// �ִϸ��̼��� �����ϴ� ������Ʈ

#pragma once

#include "Component.h"
#include <string>
#include <map>
using std::wstring;
using std::map;

class Animation;

class Animator : public Component
{
public:
	Animator(ID2D1Bitmap* spriteSheet);
	virtual ~Animator();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

public:

	/// <summary>
	/// �ִϸ��̼� ����
	/// </summary>
	/// <param name="name"> �ִϸ��̼� �̸� </param>
	/// <param name="offset"> ������ ��ġ </param>
	/// <param name="frameSize"> ��������Ʈ �� �������� ũ�� </param>
	/// <param name="startSlicePos"> �ڸ��� ������ ��ġ </param>
	/// <param name="sliceSize"> ��������Ʈ�� ��������� �ڸ����� </param>
	/// <param name="duration"> �� �����Ӵ� ��� �ð� </param>
	/// <param name="frameCount"> �� ������������ </param>
	void CreateAnimation(
		const wstring& name,
		Vector2 offset,
		Vector2 frameSize,
		Vector2 startSlicePos,
		Vector2 sliceSize,
		float duration,
		int frameCount
	);
	Animation* FindAnimation(const wstring& name);
	Animation* GetCurrentAnimation() { return m_CurrentAnimation; }
	void Play(const wstring& name, bool isRepeat);

public:
	ID2D1Bitmap* GetSpriteSheet() { return m_SpriteSheet; }

private:
	// �ִϸ����Ͱ� ��������Ʈ ��Ʈ �����ְ� �ϱ�
	ID2D1Bitmap* m_SpriteSheet;			// ����
	// �ִϸ����Ͱ� ������ �ִ� ��� �ִϸ��̼�
	map<std::wstring, Animation*> m_AnimationBox;
	// ���� ������� �ִϸ��̼�
	Animation* m_CurrentAnimation;
	// �ݺ���� ����
	bool m_IsRepeat;


};

