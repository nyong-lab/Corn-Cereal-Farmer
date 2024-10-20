#pragma once
#include "MonoBehaviour.h"

class ImageRenderer;

enum class BUTTON_FOCUS
{
	START,
	CLOSE,
};

class StartSceneScript : public MonoBehaviour
{
public:
	StartSceneScript();
	~StartSceneScript();

public:
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	void SetFocus(BUTTON_FOCUS button) { m_FocusButton = button; }

public:
	void FindButtonFocus();
	void SetButtonImage();

private:
	BUTTON_FOCUS m_FocusButton;

public:
	ImageRenderer* m_StartButtonImage;
	ImageRenderer* m_CloseButtonImage;
};

