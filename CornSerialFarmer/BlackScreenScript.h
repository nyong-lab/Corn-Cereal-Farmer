#pragma once
#include "MonoBehaviour.h"

class TextRenderer;
class ImageRenderer;

class BlackScreenScript : public MonoBehaviour
{
public:
	BlackScreenScript();
	~BlackScreenScript();

public:
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	void PlayText(bool isDay, std::wstring eventText);
	void DisabledBlackScreen();

public:

	std::wstring m_Text;
	float m_StringSize = 0.f;
	bool m_IsPlaying = false;
	TextRenderer* m_EventText = nullptr;

	TextRenderer* m_DayText = nullptr;
	ImageRenderer* m_DayIcon = nullptr;

	ImageRenderer* m_BlackScreen = nullptr;


	bool m_IsDay = false;
};

