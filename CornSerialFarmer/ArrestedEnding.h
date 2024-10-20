#pragma once
#include "Scene.h"
class ArrestedEnding :
    public Scene
{
	using Scene::Scene;
	virtual void Enter() override;
};

