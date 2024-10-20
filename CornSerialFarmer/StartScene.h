#pragma once

#include "Scene.h"

class StartScene :
    public Scene
{
private:
	using Scene::Scene;
	virtual void Enter() override;
};

