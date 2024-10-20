#pragma once

#include <MonoBehaviour.h>


class CameraScript : public MonoBehaviour
{
public:
	CameraScript();
	~CameraScript();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override {};
	virtual void Finalize() override {};


public:
	void CheatMode(float deltaTime);

public:
	GameObject* m_Target;

	bool m_SmoothMoveToTarget;
	bool m_TargetOn;
	bool m_MoveCamera;
};