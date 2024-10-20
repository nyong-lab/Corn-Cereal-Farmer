#pragma once
#include "MonoBehaviour.h"
/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// NPC1의 시야를 위한 스크립트
/// </summary>

class StateMachine;

class NPC1ViewScript
	:public MonoBehaviour
{
public:
	NPC1ViewScript();
	~NPC1ViewScript();

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

