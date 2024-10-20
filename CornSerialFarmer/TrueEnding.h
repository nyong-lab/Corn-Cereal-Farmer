#pragma once
#include "Scene.h"

class TrueEnding :
    public Scene
{
	using Scene::Scene;
	virtual void Enter() override;
};

