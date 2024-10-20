#pragma once
#include "MonoBehaviour.h"
#include "Bound.h"

class ImageRenderer;

class CornGameManagerScript :
    public MonoBehaviour
{
public:
	CornGameManagerScript();
	~CornGameManagerScript();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	void CompleteCorn(std::any);
	void CountDownEnd(std::any);

public:
	const float DELAY_TIME = 3.f;
	float m_ElipseTime = 0.f;

	int m_CornInBoxCount;
	ImageRenderer* m_Renderer = nullptr;
};

