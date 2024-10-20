#pragma once
#include "MonoBehaviour.h"

class TextRenderer;

class TImeScript :
    public MonoBehaviour
{
public:
	TImeScript();
	~TImeScript();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	float m_DeltaTime;
	float m_FPS;

	TextRenderer* m_TextRenderer;

};

