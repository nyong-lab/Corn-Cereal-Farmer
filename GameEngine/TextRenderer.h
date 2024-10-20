#pragma once
#include "Renderer.h"
#include "../GraphicsEngine/GraphicsEngine.h"

class TextRenderer : public Renderer
{
public:
	TextRenderer(
		Vector2 positionOffset,
		wstring text,
		IDWriteTextFormat* font = nullptr,
		COLOR color = COLOR::NOW
	);
	virtual ~TextRenderer();

public:
	virtual void Render() override;

public:
	// Getter & Setter
	void SetText(wstring text) { m_Text = text; }
	void SetPositionOffset(Vector2 positonOffset) { m_PositionOffset = positonOffset;}
	void SetFont(IDWriteTextFormat* font) { m_Font = font; }
	void SetTextColor(COLOR color) { m_TextColor = color; }
	
	void SetTextAlignLeft();
	void SetTextAlignMiddle();
	void SetTextAlignRight();
private:
	Vector2 m_PositionOffset;
	wstring m_Text;

	IDWriteTextFormat* m_Font;
	COLOR m_TextColor;
};

