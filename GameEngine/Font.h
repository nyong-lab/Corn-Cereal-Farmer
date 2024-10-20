/// [2023/8/1] �ڿ���
/// --------------------------
/// ���ҽ��� ��ӹ��� ��Ʈ Ŭ����

#pragma once
#include "Resource.h"
#include <dwrite_3.h>

struct IDWriteTextFormat;

class Font : public Resource
{
public:
	Font();
	virtual ~Font();

public:
	virtual bool Load(wstring filePath, wstring fileName, FLOAT size) override;
	virtual void UnLoad() override;

public:
	void SetVerticalAlign(DWRITE_TEXT_ALIGNMENT dta);
	void SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT dpa);

public:
	void SetFont(IDWriteTextFormat* font) { m_Font = font; }
	IDWriteTextFormat* Getfont() { return m_Font; }

private:
	IDWriteTextFormat* m_Font;
	wstring m_FontName;
	FLOAT m_FontSize;
};

