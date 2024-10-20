#pragma once

#include "Component.h"


class Rigidbody : public Component
{
public:
	Rigidbody();
	~Rigidbody();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

public:
	void SetVelocity(Vector2 velocity) { m_Velocity = velocity; }
	Vector2 GetVelocity() { return m_Velocity; }

	float GetMass() { return m_Mass; }
	void ApplyForce(const Vector2& force);


	void ApplyDamping();



private:
	const Vector2 GRAVITY = Vector2(0.0f, 9.81f);

	Vector2 m_Force{};
	Vector2 m_Velocity{};
	Vector2 m_AngularVelocity{};

	float m_Torque = 0.f;
	float m_Orient = 0.f;

	float m_Mass = 1.f;

	bool m_IsGravity = false;
	const float linearDamping = 0.01f;
};