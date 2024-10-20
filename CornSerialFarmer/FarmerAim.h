#pragma once

#include <MonoBehaviour.h>

class GameManagerScript;

class FarmerAim : public MonoBehaviour
{
public:
	FarmerAim();
	~FarmerAim();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;

public:
	GameManagerScript* m_GameManagerScript;
};

