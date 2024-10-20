#pragma once
#include "Component.h"


class Renderer : public Component
{
public:
	Renderer();
	Renderer(string name);
	virtual ~Renderer();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

};