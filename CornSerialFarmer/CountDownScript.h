#pragma once
#include "MonoBehaviour.h"

class Animator;

class CountDownScript :
    public MonoBehaviour
{
public:
	CountDownScript();
	~CountDownScript();
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

	void CountDownStop(std::any);
public:
	Animator* m_Animator  = nullptr;
};

