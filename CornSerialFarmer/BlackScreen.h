#pragma once

#include "GameObject.h"
#include "BlackScreenScript.h"

class BlackScreen : public GameObject
{
public:
	BlackScreen();
	~BlackScreen();

public:
	BlackScreenScript* m_BlackScreenScript;
	GameObject* m_DayIcon;
};

