#pragma once

#include "MonoBehaviour.h"

class TextRenderer;
class ImageRenderer;

class ExplainWindowScript : public MonoBehaviour
{
public:
	ExplainWindowScript();
	~ExplainWindowScript();

public:
	// Getter & Setter
	void SetTextRenderer(TextRenderer* textRenderer) { m_Text = textRenderer; }
	void SetImageRenderer(ImageRenderer* imageRenderer) { m_TextBox = imageRenderer; }

public:
	virtual void Start() override;
	void SetText(std::any);

private:
	std::wstring m_TextData;

	TextRenderer* m_Text;
	ImageRenderer* m_TextBox;
};

