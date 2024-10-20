#pragma once
#include <MonoBehaviour.h>
class KeyHoleScript :
    public MonoBehaviour
{
public:
	KeyHoleScript();
	~KeyHoleScript();
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	bool m_IsEnable = true;
	bool m_IsClicked = false;
	float m_PrevRot = 0.f;
	float m_Inc = 0.f;


public:
	const float DELAY_TIME = 1.f;
	float m_ElipseTime = 0.f;

	bool m_IsClear = false;
	bool m_OpenDoorSound = false;

};

