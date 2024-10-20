/// [2023/08/07] 박연하
/// --------------------------
/// 애니메이션을 관리하는 컴포넌트

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
	/// 애니메이션 생성
	/// </summary>
	/// <param name="name"> 애니메이션 이름 </param>
	/// <param name="offset"> 오프셋 위치 </param>
	/// <param name="frameSize"> 스프라이트 한 프레임의 크기 </param>
	/// <param name="startSlicePos"> 자르기 시작할 위치 </param>
	/// <param name="sliceSize"> 스프라이트를 어느정도로 자를건지 </param>
	/// <param name="duration"> 한 프레임당 재생 시간 </param>
	/// <param name="frameCount"> 총 몇프레임인지 </param>
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
	// 애니메이터가 스프라이트 시트 갖고있게 하기
	ID2D1Bitmap* m_SpriteSheet;			// 원본
	// 애니메이터가 가지고 있는 모든 애니메이션
	map<std::wstring, Animation*> m_AnimationBox;
	// 현재 재생중인 애니메이션
	Animation* m_CurrentAnimation;
	// 반복재생 여부
	bool m_IsRepeat;


};

