#pragma once
#include "Scene.h"
class GameOver :
    public Scene
{
	using Scene::Scene;
	virtual void Enter() override;
};

