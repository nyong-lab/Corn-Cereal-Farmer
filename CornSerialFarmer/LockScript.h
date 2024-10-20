#pragma once
#include "MonoBehaviour.h"
class LockScript :
    public MonoBehaviour
{
public:
	LockScript();
	~LockScript();
	void WareHouseHelper(std::any);
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	const float DELAY_TIME = 1.f;
	float m_ElipseTime = 0.f;

	bool m_IsClear = false;
};

