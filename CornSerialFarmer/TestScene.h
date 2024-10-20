#pragma once

#include "Scene.h"


class TestScene :
    public Scene
{
public:
    using Scene::Scene;
    virtual void Enter() override;

};

