#pragma once

#include <MonoBehaviour.h>

class GameManagerScript;

class WildBoarScript : public MonoBehaviour
{
public:
	WildBoarScript();
	~WildBoarScript();

public:
	virtual void Start() override {};
	virtual void Update(float deltaTime) override ;
	virtual void FixedUpdate(float deltaTime) override {};
	virtual void Finalize() override {};

public:
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;

public:
	bool m_IsCollision;
	GameManagerScript* m_GameManager;
	bool m_IsClear;
	bool m_RightEnd;
	bool m_PauseUpdate;
};

