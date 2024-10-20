#pragma once
#include "Scene.h"
class OpeningScene :
    public Scene
{
public:
	using Scene::Scene;
	virtual void Enter() override;
};

