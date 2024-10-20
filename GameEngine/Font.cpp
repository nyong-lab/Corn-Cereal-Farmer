#include "pch.h"
#include "Resource.h"
#include "PathManager.h"
#include "Font.h"
#include "GraphicsEngine.h"

using namespace Path;

Font::Font()
	: Resource()
	, m_Font()
	, m_FontName()
	, m_FontSize()
{

}

Font::~Font()
{

}

bool Font::Load(wstring filePath, wstring fileName, FLOAT size)
{
	SetFilePath(MakeFilePath(filePath));

	GraphicsEngine::GetInstance()->CreateCustomFont(
		&m_Font,
		GetFilePath().c_str(),
		fileName,
		size
	);

	return true;
}

void Font::UnLoad()
{
	if (m_Font != nullptr)
	{
		m_Font->Release();
		m_Font = nullptr;
	}
}

void Font::SetVerticalAlign(DWRITE_TEXT_ALIGNMENT dta)
{
	m_Font->SetTextAlignment(dta);
}

void Font::SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT dpa)
{
	m_Font->SetParagraphAlignment(dpa);
}
