#pragma once
#include "MonoBehaviour.h"
class TextRenderer;
class ImageRenderer;

class CreditBubbleScript :
    public MonoBehaviour
{
public:
	CreditBubbleScript();
	~CreditBubbleScript();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

	void BtnCallBackFunc();

public:
	std::wstring m_Text;
	float m_StringSize = 0.f;
	bool m_IsPlaying = false;
	TextRenderer* m_TextRenderer = nullptr;
	ImageRenderer* m_SpeechBubble = nullptr;
	float m_TimePassed = 0.f;
};

