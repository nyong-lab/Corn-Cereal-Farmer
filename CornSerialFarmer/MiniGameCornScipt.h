#pragma once
#include "MonoBehaviour.h"
#include "Vector2.h"
#include "Bound.h"

class ImageRenderer;
class MiniGameCornScipt :
    public MonoBehaviour
{
public:
	MiniGameCornScipt();
	~MiniGameCornScipt();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	const Bound BASKETBOUND = { 1280.f, 740.f, 220.f, 280.f };
	bool m_IsSelected;
	Vector2 m_ClickOffset;

	bool m_IsComplete = false;

	ImageRenderer* m_Renderer = nullptr;
};

