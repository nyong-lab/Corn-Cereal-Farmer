#pragma once
#include "Renderer.h"


class PrimitiveRenderer :
    public Renderer
{
public:
	PrimitiveRenderer();
	PrimitiveRenderer(string name);
	virtual ~PrimitiveRenderer();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

	void SetType(const string& type) { m_PrimitiveType = type; }

private:
	string m_PrimitiveType;
};

