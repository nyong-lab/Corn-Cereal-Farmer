#pragma once
#include "MonoBehaviour.h"

class ImageRenderer;

class WareHouseDoorScript :
	public MonoBehaviour
{
public:
	WareHouseDoorScript();
	~WareHouseDoorScript();
public:
	virtual void Start() override;
	void WareHouseHelper(std::any);
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	const float DELAY_TIME = .5f;
	float m_ElipseTime = 0.f;

	ImageRenderer* m_DoorRenderer = nullptr;
	bool m_IsClear = false;
};

