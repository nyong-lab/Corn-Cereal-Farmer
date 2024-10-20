#pragma once

#include "GameObject.h"

class ImageRenderer;
class TextRenderer;

class TimeBar : public GameObject
{
public:
	TimeBar();
	~TimeBar();

public:
	// Getter & Setter
	ImageRenderer* GetTimeBarImage() { return m_TimeBarImage; }
	ImageRenderer* GetTimeIconImage() { return m_TimeBarIconImage; }
	TextRenderer* GetDateText() { return m_DateTextRenderer; }

private:
	ImageRenderer* m_TimeBarImage;
	ImageRenderer* m_TimeBarIconImage;
	TextRenderer* m_DateTextRenderer;
};

