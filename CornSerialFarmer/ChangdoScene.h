#pragma once

#include "Scene.h"


class ChangdoScene :
    public Scene
{
public:
	using Scene::Scene;
	virtual void Enter() override;
};

