#pragma once
#include "MonoBehaviour.h"

class Animator;

class WildBoarCatchScript :
    public MonoBehaviour
{
public:
	WildBoarCatchScript();
	~WildBoarCatchScript();
public:
	virtual void Start() override;
	void CountDownEnd(std::any);
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	int m_HP = 3;

	int m_Sign = 1;

	Animator* m_Anim = nullptr;

	Animator* m_HitAnim = nullptr;

	bool m_IsClear = false;

	bool m_IsHit = false;

	float m_ElipseTime = 0.f;

	bool m_IsJump = false;
};

