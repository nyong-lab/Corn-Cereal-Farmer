#pragma once

#include "GameObject.h"
#include "PopupWindowBackground.h"

class PauseWindow : public GameObject
{
public:
	PauseWindow();
	~PauseWindow();

public:
	PopupWindowBackground* m_Background = nullptr;
};

