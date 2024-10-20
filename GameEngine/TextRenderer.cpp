/// [2023/8/13] 박연하
/// --------------------------
/// 텍스트를 출력하는 렌더러

#include "pch.h"
#include "TextRenderer.h"

TextRenderer::TextRenderer(Vector2 positionOffset, wstring text, IDWriteTextFormat* font, COLOR color)
	: m_PositionOffset(positionOffset)
	, m_Text(text)
	, m_Font(font)
	, m_TextColor(color)
{

}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Render()
{
	GraphicsEngine::GetInstance()->DrawText(
		(int)m_PositionOffset.x, (int)m_PositionOffset.y,
		m_Text,
		m_Font,
		m_TextColor
	);
}

void TextRenderer::SetTextAlignLeft()
{
	m_PositionOffset.x += GraphicsEngine::TEXTBOX_SIZE.x;
}

void TextRenderer::SetTextAlignMiddle()
{
	m_PositionOffset.x += -GraphicsEngine::TEXTBOX_SIZE.x / 2.f;
}

void TextRenderer::SetTextAlignRight()
{
	m_PositionOffset.x += -GraphicsEngine::TEXTBOX_SIZE.x;
}
