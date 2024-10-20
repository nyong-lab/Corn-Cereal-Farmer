#pragma once
#include "MonoBehaviour.h"

class DeadBodyScript
	:public MonoBehaviour
{
public:
	DeadBodyScript();
	~DeadBodyScript();

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

