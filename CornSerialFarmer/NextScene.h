#pragma once
#include "Scene.h"

class NextScene :
    public Scene
{

public:
	using Scene::Scene;
	virtual void Enter() override;

};

