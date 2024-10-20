#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// MPC2의 시야를 담당하는 Script
/// </summary>

class NPC2ViewScript :
    public MonoBehaviour
{

public:
    NPC2ViewScript();
    ~NPC2ViewScript();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;
};

